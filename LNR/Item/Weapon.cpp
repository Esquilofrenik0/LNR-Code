#include "Weapon.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/Equipment.h"
#include "LNR/Component/Inventory.h"

UWeapon::UWeapon()
{
	damage = 0.1f;
	defense = 0.0f;
}

void UWeapon::UseItem(AHero* hero)
{
	hero->Equipment->EquipWeapon(this);
	hero->Inventory->RemoveItem(this);
}

FString UWeapon::PrintItemData()
{
	FString data = Name + "\r";
	data += "Damage: " + FString::FromInt(damage) + "\r";
	data += "Defense: " + FString::FromInt(defense) + "\r";
	data += "Price: " + FString::FromInt(Price) + "\r";
	data += "Weight: " + FString::FromInt(Weight) + "\r";
	return data;
}
