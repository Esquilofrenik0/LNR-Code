#include "Item.h"
#include "LNR/Body/Hero.h"

UItem::UItem()
{
	Name = "Item";
	Description = "Description";
	Price = 0.01f;
	Weight = 0.01f;
	Stack = 1;
	bPickable = true;
}

void UItem::UseItem(AHero* hero)
{
	Print(Name.ToString() + " used");
}

bool UItem::Compare(UItem* item)
{
	if(item == nullptr) return false;
	if(item->Name == Name) return true;
	else return false;
}

FString UItem::PrintItemData()
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Description: " + Description + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	return data;
}
