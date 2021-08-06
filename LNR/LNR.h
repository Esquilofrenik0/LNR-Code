#pragma once
#include "CoreMinimal.h"
#include "../../Plugins/FactionsExtension/Source/Factions/Public/FactionsModule.h"
#include "../../Plugins/FactionsExtension/Source/Factions/Public/FactionsLibrary.h"

UENUM(BlueprintType)
enum EState
{
	Dead, Idle, Attack, Block, Dodge, Climbing
};

UENUM(BlueprintType)
enum EFaction
{
	None, Survivor, Inquisitor, BioHacker, Plagued, Feral, Critter
};

void Print(FString print);
void Print(int print);
void Print(float print);