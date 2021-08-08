#include "Recipe.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/Inventory.h"

URecipe::URecipe()
{
	Stack = 100;
}

FString URecipe::PrintItemData()
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Recipe\r";
	for (int i = 0; i < Cost.Num(); i++)
	{
		data += "Cost" + FString::FromInt(i) + ": " + Cost[i].Item->Name.ToString() + " x" + FString::FromInt(
				Cost[i].Amount) +
			"\r";
	}
	data += "Description: " + Description + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	return data;
}

void URecipe::UseItem(AHero* hero)
{
	if (!hero->Recipes.Contains(this))
	{
		hero->Recipes.Add(this);
		hero->Inventory->RemoveItem(this);
	}
}

bool URecipe::CanCreate(AHero* hero)
{
	TArray<bool> canPayCost;
	canPayCost.Init(false, Cost.Num());
	for (FSlot slot : hero->Inventory->Slots)
	{
		for (int i = 0; i < Cost.Num(); i++)
		{
			canPayCost[i] = hero->Inventory->HasItem(Cost[i].Item->Name, Cost[i].Amount);
		}
	}
	if (canPayCost.Contains(false)) return false;
	return true;
}

void URecipe::CreateItem(AHero* hero)
{
	if (CanCreate(hero))
	{
		Print("Can Create is True");
		for (int i = 0; i < Cost.Num(); i++) hero->Inventory->RemoveItem(Cost[i].Item, Cost[i].Amount);
		hero->Inventory->AddItem(Result.GetDefaultObject());
	}
	else Print("Couldn't pay crafting cost");
}
