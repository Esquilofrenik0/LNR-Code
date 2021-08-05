#include "Armor.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/Equipment.h"
#include "LNR/Component/Inventory.h"

UArmor::UArmor()
{
	defense = 0.0f;
}

void UArmor::UseItem(AHero* hero)
{
	hero->Equipment->EquipArmor(this);
	hero->Inventory->RemoveItem(this);
}

FString UArmor::PrintItemData()
{
	FString data = Name + "\r";
	data += "Defense: " + FString::FromInt(defense) + "\r";
	data += "Price: " + FString::FromInt(Price) + "\r";
	data += "Weight: " + FString::FromInt(Weight) + "\r";
	return data;
}

