#include "Attack.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/LNR.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Hero.h"
#include "LNR/Body/Human.h"
#include "LNR/Component/Attributes.h"
#include "LNR/Component/Equipment.h"
#include "LNR/Item/Weapon.h"

UAttack::UAttack()
{
	AbilityInput = EAbilityInput::Attack;
}

void UAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo,
                              const FGameplayEventData* TriggerEventData)
{
	if (ABody* body = Cast<ABody>(ActorInfo->AvatarActor))
	{
		Body = body;
		Body->Holster(true);

		Body->GetWorldTimerManager().ClearTimer(Body->ResetComboHandle);
		Body->Attributes->Combo %= Body->Attributes->MaxCombo;

		UAnimMontage* MontageToPlay = Body->GetCombatMontage();
		Body->Attributes->State = EState::Attack;

		USkeletalMeshComponent* Mesh = Body->GetMesh();
		MultiPlayMontage(Mesh, MontageToPlay);

		UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
		AnimInstance->Montage_Play(MontageToPlay);

		FOnMontageEnded BlendOutDelegate;
		BlendOutDelegate.BindUObject(this, &UAttack::OnAnimationBlendOut);
		AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, MontageToPlay);

		if (AHuman* human = Cast<AHuman>(Body))
		{
			Human = human;
			if (UGun* gun = Cast<UGun>(Human->Equipment->Weapon[0]))
			{
				Human->IsShooting = true;
				Human->Shoot();
				return;
			}
		}
		Body->Attributes->Combo += 1;
		Body->Attributes->Combo %= Body->Attributes->MaxCombo;
	}
}

void UAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                         const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                         bool bWasCancelled)
{
	if(Human) Human->IsShooting = false;
	if (Body->Attributes->Attacking == false)
	{
		Body->Attributes->State = EState::Idle;
		if (Body->Attributes->Blocking) Body->Block();
	}
	else ActivateAbility(GetCurrentAbilitySpecHandle(), ActorInfo, CurrentActivationInfo, &CurrentEventData);
}

void UAttack::MultiPlayMontage_Implementation(USkeletalMeshComponent* Mesh, UAnimMontage* montage)
{
	Mesh->GetAnimInstance()->Montage_Play(montage);
}

void UAttack::OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	Body->GetWorldTimerManager().SetTimer(Body->ResetComboHandle, Body, &ABody::ResetCombo, 2.0f, false);
	K2_EndAbility();
}
