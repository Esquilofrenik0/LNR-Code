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
	Print(Name + " used as hero");
}

bool UItem::Compare(UItem* item)
{
	if (item->Name != Name) return false;
	else return true;
}

FString UItem::PrintItemData()
{
	FString data = Name + "\r";
	data += "Price: " + FString::FromInt(Price) + "\r";
	data += "Weight: " + FString::FromInt(Weight) + "\r";
	return data;
}
