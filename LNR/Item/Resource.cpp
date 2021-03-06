#include "Resource.h"

UResource::UResource()
{
	Stack = 100;
}

FString UResource::PrintItemData()
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Resource\r";
	data += "Description: " + Description + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	return data;
}
