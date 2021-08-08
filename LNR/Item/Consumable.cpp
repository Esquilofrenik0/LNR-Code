#include "Consumable.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/Attributes.h"
#include "LNR/Component/Inventory.h"

UConsumable::UConsumable()
{
	healHealth = 0.0f;
	healStamina = 0.0f;
	healHunger = 0.0f;
}

void UConsumable::UseItem(AHero* hero)
{
	Super::UseItem(hero);
	if (hero != nullptr)
	{
		if (healHealth != 0) { hero->Attributes->ChangeHealth(healHealth); }
		if (healStamina != 0) { hero->Attributes->ChangeStamina(healStamina); }
		if (healHunger != 0) { hero->Attributes->ChangeHunger(healHunger); }
		hero->Inventory->RemoveItem(this);
	}
}

FString UConsumable::PrintItemData()
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Consumable\r";
	data += "Description: " + Description + "\r";
	data += "Health: " + FString::SanitizeFloat(healHealth) + "\r";
	data += "Stamina: " + FString::SanitizeFloat(healStamina) + "\r";
	data += "Hunger: " + FString::SanitizeFloat(healHunger) + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	return data;
}
