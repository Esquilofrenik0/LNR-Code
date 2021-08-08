#include "Armor.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/Equipment.h"
#include "LNR/Component/Inventory.h"

UArmor::UArmor()
{
	Defense = 0.0f;
}

void UArmor::UseItem(AHero* hero)
{
	hero->Equipment->EquipArmor(this);
	hero->Inventory->RemoveItem(this);
}

FString UArmor::PrintItemData()
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Armor\r";
	data += "Description: " + Description + "\r";
	data += "Defense: " + FString::SanitizeFloat(Defense) + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	return data;
}

