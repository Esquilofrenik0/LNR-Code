#include "Body.h"
#include "Npc.h"
#include "LNR/Component/Trace.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "LNR/Item/SkSpawn.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Component/Action.h"
#include "AbilitySystemComponent.h"
#include "LNR/Ability/Ability.h"
#include "LNR/Component/Attributes.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "LNR/Network/Playor.h"
#include "LNR/Component/Inventory.h"
#include "LNR/Item/Dropable.h"
#include "LNR/Item/Slot.h"
#include "LNR/Object/Container.h"

ABody::ABody()
{
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	Attributes = CreateDefaultSubobject<UAttributes>("Attributes");
	Action = CreateDefaultSubobject<UAction>("Action");
	Action->SetIsReplicated(true);
	Action->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	Ability.SetNum(32);

	Trace = CreateDefaultSubobject<UTrace>("Trace");
	GetCapsuleComponent()->InitCapsuleSize(30.f, 85.0f);
	WalkSpeed = 300;
	RunSpeed = 500;
	SprintSpeed = 800;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	Attributes->State = EState::Idle;
}

UAbilitySystemComponent* ABody::GetAbilitySystemComponent() const
{
	return Action;
}

void ABody::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABody, IsAiming);
	DOREPLIFETIME(ABody, IsShooting);
	DOREPLIFETIME(ABody, LootBag);
	DOREPLIFETIME(ABody, LastHandTransform);
	DOREPLIFETIME_CONDITION_NOTIFY(ABody, Ability, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABody, Passive, COND_None, REPNOTIFY_Always);
}

void ABody::InitializeAttributes()
{
	if (DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = Action->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = Action->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = Action->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ABody::GiveAbilities()
{
	for (TSubclassOf<UAbility>& ability : DefaultAbilities)
	{
		FGameplayAbilitySpecHandle handle = Action->GiveAbility(FGameplayAbilitySpec(ability,
			1, (uint8)ability.GetDefaultObject()->AbilityInput));

		if (ability.GetDefaultObject()->AbilityInput == EAbilityInput::Passive)
		{
			Passive.Add(handle);
			Action->TryActivateAbility(handle);
		}
		else Ability.Insert(handle, (uint8)ability.GetDefaultObject()->AbilityInput);
	}
}

void ABody::OnRep_Ability(TArray<FGameplayAbilitySpecHandle> oldAbility)
{
	oldAbility = Ability;
}

void ABody::OnRep_Passive(TArray<FGameplayAbilitySpecHandle> oldPassive)
{
	oldPassive = Passive;
}

void ABody::ServerSetIsAiming_Implementation(bool value)
{
	IsAiming = value;
}

void ABody::PossessedBy(AController* NewController)
{
	//SERVER
	Super::PossessedBy(NewController);
	Controller = NewController;
	Action->InitAbilityActorInfo(this, this);
	InitializeAttributes();
	GiveAbilities();
	Npc = Cast<ANpc>(NewController);
	Player = Cast<APlayor>(NewController);
	Attributes->MaxCombo = UnarmedMontage.Num();
}

FFaction ABody::GetFaction() const
{
	return Attributes->Faction;
}

void ABody::SetFaction(const FFaction& InFaction)
{
	Attributes->Faction = InFaction;
}

void ABody::BeginPlay()
{
	Super::BeginPlay();
	// Animator = GetMesh()->GetAnimInstance();
	Respawn();
}

void ABody::OnRep_PlayerState()
{
	//CLIENT
	Super::OnRep_PlayerState();
	Action->InitAbilityActorInfo(this, this);
	InitializeAttributes();
	for (int i = 0; i < Passive.Num(); i++)
	{
		Action->TryActivateAbility(Passive[i]);
	}
}

void ABody::RefreshAttributes()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		Attributes->Combo = 0;
		Attributes->MaxCombo = UnarmedMontage.Num();
		Attributes->Damage = Attributes->BaseDamage;
		Attributes->Defense = Attributes->BaseDefense;
	}
	else ServerRefreshAttributes();
}

void ABody::ServerRefreshAttributes_Implementation()
{
	RefreshAttributes();
}

void ABody::Die()
{
	Attributes->State = EState::Dead;
	if (Npc) Npc->UnPossess();
	StartRagdoll();
	GetMesh()->SetSimulatePhysics(true);
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &ABody::DestroyCorpse, Attributes->RespawnTime, false);
	DropBag();
}

void ABody::DestroyCorpse()
{
	GetWorldTimerManager().ClearTimer(RespawnHandle);
	Destroy();
}

void ABody::Respawn()
{
	InitializeAttributes();
	RefreshAttributes();
}

void ABody::ResetCombo()
{
	GetWorldTimerManager().ClearTimer(ResetComboHandle);
	Attributes->Combo = 0;
}

void ABody::Attack()
{
	if (Attributes->State == EState::Idle || Attributes->State == EState::Block)
	{
		Action->TryActivateAbility(Ability[(uint8)EAbilityInput::Attack]);
	}
}

void ABody::Sprint()
{
	if (Attributes->State == EState::Idle)
	{
		Action->TryActivateAbility(Ability[(uint8)EAbilityInput::Sprint]);
	}
}

void ABody::Dodge()
{
	if (Attributes->State == EState::Idle)
	{
		Action->TryActivateAbility(Ability[(uint8)EAbilityInput::Dodge]);
	}
}

void ABody::Block()
{
	if (Attributes->State == EState::Idle)
	{
		Action->TryActivateAbility(Ability[(uint8)EAbilityInput::Block]);
	}
}

void ABody::Holster(bool value)
{
	// if (GetLocalRole() == ROLE_Authority) Attributes->CombatStance = Value;
	// else ServerHolster(Value);
}

void ABody::ServerHolster_Implementation(bool Value)
{
	Holster(Value);
}

void ABody::ResetMelee()
{
	MeleeHits.Reset();
}

ABody* ABody::TraceMelee()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FHitResult hit = Trace->Circle(GetMesh()->GetSocketLocation("Melee"), 50, 1, false);
		if (AActor* hitActor = hit.GetActor())
		{
			if (!MeleeHits.Contains(hitActor))
			{
				MeleeHits.Add(hitActor);
				if (ABody* hitBody = Cast<ABody>(hitActor))
				{
					UGameplayStatics::ApplyDamage(hitBody, Attributes->Damage, GetController(), this, nullptr);
					return hitBody;
				}
			}
		}
	}
	return nullptr;
}

ABody* ABody::Shoot()
{
	return nullptr;
}

UAnimMontage* ABody::GetCombatMontage()
{
	return UnarmedMontage[Attributes->Combo];
}

void ABody::DropInventory()
{
	FVector Location = GetActorLocation();
	Location.Z = Location.Z - GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FRotator Rotation = GetActorRotation();
	FActorSpawnParameters SpawnInfo;
	LootBag = GetWorld()->SpawnActor<AContainer>(Location, Rotation, SpawnInfo);
	LootBag->Container->SetStaticMesh(LootBagMesh);
	LootBag->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	for (FDropable drop : Dropables)
	{
		int rand = FMath::RandRange(0, 100);
		if (drop.chance >= rand)
		{
			LootBag->Inventory->AddItem(drop.item, drop.amount);
			Print(drop.item->Name + " Dropped");
		}
	}
}

void ABody::DropBag()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		DropInventory();
		MultiDropBag();
	}
	else ServerDropBag();
}

void ABody::PlayMontage(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		MultiPlayMontage(nMesh, nMontage);
		UAnimInstance* AnimInstance = nMesh->GetAnimInstance();
		AnimInstance->Montage_Play(nMontage);
		FOnMontageEnded BlendOutDelegate;
		BlendOutDelegate.BindUObject(this, &ABody::OnAnimationBlendOut);
		AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, nMontage);
	}
	else ServerPlayMontage(nMesh, nMontage);
}

void ABody::ServerPlayMontage_Implementation(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage)
{
	PlayMontage(nMesh, nMontage);
}

void ABody::MultiPlayMontage_Implementation(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage)
{
	nMesh->GetAnimInstance()->Montage_Play(nMontage);
}

void ABody::OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	if (Attributes->State != EState::Dead) Attributes->State = EState::Idle;
}

void ABody::ServerDropBag_Implementation()
{
	DropBag();
}

void ABody::MultiDropBag_Implementation()
{
	DropInventory();
}

void ABody::ServerSetLastHandTransform_Implementation(FTransform value)
{
	LastHandTransform = value;
}

float ABody::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                        AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Attributes->State == EState::Block)
	{
		if (ABody* instigator = Cast<ABody>(DamageCauser))
		{
			instigator->PlayMontage(instigator->GetMesh(), instigator->TakeDamageMontage);
			instigator->Attributes->State = EState::Attack;
		}
		Attributes->Stamina -= DamageAmount;
	}
	else
	{
		PlayMontage(GetMesh(), TakeDamageMontage);
		Attributes->Combo = 0;
		Attributes->State = EState::Attack;
		Attributes->Health -= DamageAmount;
	}
	if (Attributes->Health <= 0) Die();
	return DamageAmount;
}
