#include "Buildable.h"
#include "LNR/Body/Hero.h"

UBuildable::UBuildable()
{
	Stack = 100;
}

void UBuildable::UseItem(AHero* hero)
{
	hero->StartBuild(this);
}

FString UBuildable::PrintItemData()
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Buildable\r";
	data += "Description: " + Description + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	return data;
}

