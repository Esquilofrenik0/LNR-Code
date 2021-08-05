#include "Block.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Hero.h"
#include "LNR/Body/Human.h"
#include "LNR/Component/Attributes.h"
#include "LNR/Item/Gun.h"
#include "LNR/Component/Equipment.h"
#include "LNR/Item/Shield.h"

class AHuman;

UBlock::UBlock()
{
	AbilityInput = EAbilityInput::Block;
}

void UBlock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                             const FGameplayAbilityActivationInfo ActivationInfo,
                             const FGameplayEventData* TriggerEventData)
{
	if (ABody* body = Cast<ABody>(ActorInfo->AvatarActor))
	{
		Body = body;
		Body->Holster(true);

		Move = Body->GetCharacterMovement();
		Move->MaxWalkSpeed = Body->WalkSpeed;
		ClientSetSpeed(Body->WalkSpeed, Move);
		Body->Attributes->State = EState::Block;

		Hero = Cast<AHero>(Body);
		if (Cast<UGun>(Hero->Equipment->Weapon[0]) && !Cast<UShield>(Hero->Equipment->Weapon[1]))
		{
			Hero->EnterAim();
			// ClientSetCamera(Hero, false);
		}

		Body->GetWorldTimerManager().ClearTimer(BlockTimer);
		Body->GetWorldTimerManager().SetTimer(BlockTimer, this, &UBlock::TickBlock, 0.1, true);
	}
}

void UBlock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                        bool bWasCancelled)
{
	Body->GetWorldTimerManager().ClearTimer(BlockTimer);
	Move->MaxWalkSpeed = Body->RunSpeed;
	ClientSetSpeed(Body->RunSpeed, Move);
	Body->Attributes->State = EState::Idle;

	if (Hero) Hero->ExitAim();
}

void UBlock::TickBlock()
{
	if (!Body->Attributes->Blocking) K2_EndAbility();
}

void UBlock::ClientSetSpeed_Implementation(float Speed, UCharacterMovementComponent* CharacterMovement)
{
	CharacterMovement->MaxWalkSpeed = Speed;
}

void UBlock::ClientSetCamera_Implementation(AHero* nHero, bool reset)
{
	if (reset) nHero->TPCamera->FieldOfView = 90;
	else nHero->TPCamera->FieldOfView = 30;
}
