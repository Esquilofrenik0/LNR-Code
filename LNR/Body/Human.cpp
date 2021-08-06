#include "Human.h"
#include "LNR/Component/Trace.h"
#include "LNR/Component/Equipment.h"
#include "LNR/Item/Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Component/Action.h"
#include "LNR/Component/Attributes.h"
#include "LNR/Item/Armor.h"
#include "LNR/Item/WeaponComponent.h"

AHuman::AHuman()
{
	Equipment = CreateDefaultSubobject<UEquipment>("Equipment");
	Equipment->SetIsReplicated(true);
	Equipment->Mesh = GetMesh();

	Head = CreateDefaultSubobject<USkeletalMeshComponent>("Head");
	Head->SetupAttachment(GetMesh());
	Back = CreateDefaultSubobject<USkeletalMeshComponent>("Back");
	Back->SetupAttachment(GetMesh());
	Chest = CreateDefaultSubobject<USkeletalMeshComponent>("Chest");
	Chest->SetupAttachment(GetMesh());
	Legs = CreateDefaultSubobject<USkeletalMeshComponent>("Legs");
	Legs->SetupAttachment(GetMesh());
	Feet = CreateDefaultSubobject<USkeletalMeshComponent>("Feet");
	Feet->SetupAttachment(GetMesh());
	Equipment->ArmorSlot.Reset();
	Equipment->ArmorSlot.Add(Head);
	Equipment->ArmorSlot.Add(Back);
	Equipment->ArmorSlot.Add(Chest);
	Equipment->ArmorSlot.Add(Legs);
	Equipment->ArmorSlot.Add(Feet);
	Equipment->Armor.Init(nullptr, 5);

	RightHand = CreateDefaultSubobject<UWeaponComponent>("RightHand");
	RightHand->SetupAttachment(GetMesh());
	RightHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightHand");
	LeftHand = CreateDefaultSubobject<UWeaponComponent>("LeftHand");
	LeftHand->SetupAttachment(GetMesh());
	LeftHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "LeftHand");
	Equipment->WeaponSlot.Reset();
	Equipment->WeaponSlot.Add(RightHand);
	Equipment->WeaponSlot.Add(LeftHand);
	Equipment->Weapon.Init(nullptr, 4);

	RightBack = CreateDefaultSubobject<UWeaponComponent>("RightBack");
	RightBack->SetupAttachment(GetMesh());
	RightBack->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightBack");
	LeftBack = CreateDefaultSubobject<UWeaponComponent>("LeftBack");
	LeftBack->SetupAttachment(GetMesh());
	LeftBack->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "LeftBack");

	RightHolster = CreateDefaultSubobject<UWeaponComponent>("RightHolster");
	RightHolster->SetupAttachment(GetMesh());
	RightHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightHolster");
	LeftHolster = CreateDefaultSubobject<UWeaponComponent>("LeftHolster");
	LeftHolster->SetupAttachment(GetMesh());
	LeftHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "LeftHolster");

	Equipment->HolsterSlot.Reset();
	Equipment->HolsterSlot.Add(RightHolster);
	Equipment->HolsterSlot.Add(LeftHolster);
	Equipment->HolsterSlot.Add(RightBack);
	Equipment->HolsterSlot.Add(LeftBack);
}

void AHuman::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Equipment->SortArmor();
	Equipment->SortWeapon();
}

void AHuman::Holster(bool value)
{
	if (GetLocalRole() == ROLE_Authority) Equipment->CombatStance = value;
	else ServerHolster(value);
	Equipment->OnRep_CombatStance(Equipment->CombatStance);
}

void AHuman::RefreshAttributes()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		Attributes->Combo = 0;
		if (Equipment->Weapon[0]) Attributes->MaxCombo = Equipment->Weapon[0]->CombatMontage.Num();
		else Attributes->MaxCombo = UnarmedMontage.Num();

		Attributes->Damage = Attributes->BaseDamage;
		Attributes->Defense = Attributes->BaseDefense;
		for (int i = 0; i < Equipment->Weapon.Num(); i++)
		{
			UWeapon* weapon = Equipment->Weapon[i];
			if (weapon != nullptr)
			{
				Attributes->Damage += weapon->damage;
				Attributes->Defense += weapon->defense;
			}
		}
		for (UArmor* armor : Equipment->Armor)
		{
			if (armor != nullptr) Attributes->Defense += armor->defense;
		}
	}
	else ServerRefreshAttributes();
}

void AHuman::WeaponSwap()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		Attributes->Combo = 0;
		Equipment->WeaponSwap();
	}
	else ServerWeaponSwap();
}

void AHuman::ServerWeaponSwap_Implementation()
{
	WeaponSwap();
}

void AHuman::TraceMelee()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (Equipment->Weapon[0] != nullptr)
		{
			FVector start = Equipment->WeaponSlot[0]->GetSocketLocation("TraceStart");
			FVector end = Equipment->WeaponSlot[0]->GetSocketLocation("TraceFinish");
			FHitResult hit = Trace->Line(start, end, 1, false);

			if (AActor* hitActor = hit.GetActor())
			{
				if (!MeleeHits.Contains(hitActor))
				{
					MeleeHits.Add(hitActor);
					UGameplayStatics::ApplyPointDamage(hitActor, Attributes->Damage, GetActorLocation(), hit, GetController(), this, MeleeDamageType);
				}
			}
		}
		else
		{
			FHitResult hit = Trace->Circle(GetMesh()->GetSocketLocation("RightHand"), 20, 1, false);
			if (AActor* hitActor = hit.GetActor())
			{
				if (!MeleeHits.Contains(hitActor))
				{
					MeleeHits.Add(hitActor);
					UGameplayStatics::ApplyPointDamage(hitActor, Attributes->Damage, GetActorLocation(), hit, GetController(), this, MeleeDamageType);
				}
			}
		}
	}
}

UAnimMontage* AHuman::GetCombatMontage()
{
	if (UWeapon* weapon = Equipment->GetWeapon(0)) return weapon->CombatMontage[Attributes->Combo];
	else return UnarmedMontage[Attributes->Combo];
}
