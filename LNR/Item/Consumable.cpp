#include "Consumable.h"
#include "LNR/Body/Hero.h"
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
		Print("Used Consumable");
		// if (healHealth != 0) { hero->Status->ChangeHealth(healHealth); }
		// if (healStamina != 0) { hero->Status->ChangeStamina(healStamina); }
		// if (healHunger != 0) { hero->Status->ChangeHunger(healHunger); }
		hero->Inventory->RemoveItem(this);
	}
}

FString UConsumable::PrintItemData()
{
	FString data = Name + "\r";
	data += "Health: " + FString::FromInt(healHealth) + "\r";
	data += "Stamina: " + FString::FromInt(healStamina) + "\r";
	data += "Hunger: " + FString::FromInt(healHunger) + "\r";
	data += "Price: " + FString::FromInt(Price) + "\r";
	data += "Weight: " + FString::FromInt(Weight) + "\r";
	return data;
}
