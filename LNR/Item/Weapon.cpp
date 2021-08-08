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
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Weapon\r";
	data += "Description: " + Description + "\r";
	data += "Damage: " + FString::SanitizeFloat(damage) + "\r";
	data += "Defense: " + FString::SanitizeFloat(defense) + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	return data;
}
