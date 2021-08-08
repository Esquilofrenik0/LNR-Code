#include "Equipment.h"
#include "Attributes.h"
#include "LNR/Item/Armor.h"
#include "LNR/Item/Weapon.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Hero.h"
#include "Components/SkeletalMeshComponent.h"
#include "LNR/Component/Inventory.h"
#include "LNR/Item/WeaponComponent.h"
#include "Net/UnrealNetwork.h"

void UEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UEquipment, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEquipment, Weapon, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEquipment, CombatStance, COND_None, REPNOTIFY_Always);
}

void UEquipment::OnRep_Armor(TArray<UArmor*> oldArmor)
{
	oldArmor = Armor;
	for (int i = 0; i < Armor.Num(); i++) DressArmor(i, Armor[i]);
	if (Body == nullptr) Body = Cast<ABody>(GetOwner());
	Body->RefreshAttributes();
}

void UEquipment::OnRep_Weapon(TArray<UWeapon*> oldWeapon)
{
	oldWeapon = Weapon;
	for (int i = 0; i < Weapon.Num(); i++) DressWeapon(i, Weapon[i]);
	if (Body == nullptr) Body = Cast<ABody>(GetOwner());
	Body->RefreshAttributes();
}

void UEquipment::OnRep_CombatStance(bool oldCombatStance)
{
	oldCombatStance = CombatStance;
	for (int i = 0; i < Weapon.Num(); i++) DressWeapon(i, Weapon[i]);
}

UArmor* UEquipment::GetArmor(int index)
{
	return Armor[index];
}

void UEquipment::DressArmor(int index, UArmor* nArmor)
{
	if (nArmor != nullptr)
	{
		ArmorSlot[index]->SetSkeletalMesh(nArmor->SkeletalMesh);
		ArmorSlot[index]->SetMasterPoseComponent(Mesh);
	}
	else ArmorSlot[index]->SetSkeletalMesh(nullptr);
}

void UEquipment::SetArmor(int index, UArmor* nArmor)
{
	if (Body == nullptr) Body = Cast<ABody>(GetOwner());
	if (GetOwnerRole() == ROLE_Authority)
	{
		Armor[index] = nArmor;
		DressArmor(index, nArmor);
		Body->RefreshAttributes();
	}
	else ServerSetArmor(index, nArmor);
}

void UEquipment::ServerSetArmor_Implementation(int index, UArmor* nArmor)
{
	SetArmor(index, nArmor);
}

void UEquipment::EquipArmor(UArmor* nArmor)
{
	if (Armor[nArmor->Type] != nullptr) UnEquipArmor(nArmor->Type);
	SetArmor(nArmor->Type, nArmor);
}

void UEquipment::UnEquipArmor(int index)
{
	if (Armor[index] != nullptr)
	{
		if (AHero* owner = Cast<AHero>(GetOwner())) owner->Inventory->AddItem(Armor[index]);
		SetArmor(index, nullptr);
	}
}

UWeapon* UEquipment::GetWeapon(int index)
{
	return Weapon[index];
}

int UEquipment::GetWeaponSlot(UWeapon* nWeapon)
{
	int slot = 0;
	if (nWeapon->slot == EWeaponSlot::RightHand) slot = 0;
	else if (nWeapon->slot == EWeaponSlot::TwoHand) slot = 0;
	else if (nWeapon->slot == EWeaponSlot::AnyHand) slot = 0;
	else if (nWeapon->slot == EWeaponSlot::LeftHand) slot = 1;
	return slot;
}

void UEquipment::DressWeapon(int index, UWeapon* nWeapon)
{
	if (nWeapon != nullptr)
	{
		if (CombatStance && index < 2)
		{
			WeaponSlot[index]->SetupAttachments(nWeapon);
			HolsterSlot[index]->SetupAttachments(nullptr);
		}
		else
		{
			HolsterSlot[index]->SetupAttachments(nWeapon);
			if (index < 2) WeaponSlot[index]->SetupAttachments(nullptr);
		}
	}
	else
	{
		if (index < 2) WeaponSlot[index]->SetupAttachments(nullptr);
		HolsterSlot[index]->SetupAttachments(nullptr);
	}
}

void UEquipment::SetWeapon(int index, UWeapon* nWeapon)
{
	if (Body == nullptr) Body = Cast<ABody>(GetOwner());
	if (GetOwnerRole() == ROLE_Authority)
	{
		Weapon[index] = nWeapon;
		DressWeapon(index, nWeapon);
		Body->RefreshAttributes();
	}
	else ServerSetWeapon(index, nWeapon);
}

void UEquipment::ServerSetWeapon_Implementation(int index, UWeapon* nWeapon)
{
	SetWeapon(index, nWeapon);
}

void UEquipment::EquipWeapon(UWeapon* nWeapon)
{
	if (nWeapon != nullptr)
	{
		int slot = GetWeaponSlot(nWeapon);
		if (Weapon[slot]) UnEquipWeapon(slot);
		
		if(slot == 0 && Weapon[1] && nWeapon->slot == EWeaponSlot::TwoHand) UnEquipWeapon(1);
		else if(slot == 1 && Weapon[0] && Weapon[0]->slot == EWeaponSlot::TwoHand) UnEquipWeapon(0);
		
		SetWeapon(slot, nWeapon);
	}
}

void UEquipment::UnEquipWeapon(int index)
{
	if (Weapon[index] != nullptr)
	{
		if (AHero* owner = Cast<AHero>(GetOwner())) owner->Inventory->AddItem(Weapon[index]);
		SetWeapon(index, nullptr);
	}
}

void UEquipment::SortArmor()
{
	TArray<UArmor*> toEquip;
	for (int i = 0; i < Armor.Num(); i++)
	{
		if (Armor[i] != nullptr)
		{
			toEquip.Add(Armor[i]);
			Armor[i] = nullptr;
		}
	}
	for (int i = 0; i < toEquip.Num(); i++) EquipArmor(toEquip[i]);
}

void UEquipment::SortWeapon()
{
	TArray<UWeapon*> toEquip;
	for (int i = 0; i < Weapon.Num(); i++)
	{
		if (Weapon[i] != nullptr)
		{
			toEquip.Add(Weapon[i]);
			Weapon[i] = nullptr;
		}
	}
	for (int i = 0; i < toEquip.Num(); i++) EquipWeapon(toEquip[i]);
}

void UEquipment::WeaponSwap()
{
	TArray<UWeapon*> oldWeapon;
	oldWeapon.Init(nullptr, 4);
	for (int i = 0; i < 4; i++) oldWeapon[i] = Weapon[i];
	Weapon[0] = oldWeapon[2];
	Weapon[1] = oldWeapon[3];
	Weapon[2] = oldWeapon[0];
	Weapon[3] = oldWeapon[1];
	OnRep_Weapon(Weapon);
}
