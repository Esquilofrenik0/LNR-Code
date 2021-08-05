#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EState
{
	Dead = 0 UMETA(DisplayName = "Dead"),
	Idle = 1 UMETA(DisplayName = "Idle"),
	Attack = 2 UMETA(DisplayName = "Attack"),
	Block = 3 UMETA(DisplayName = "Block"),
	Dodge = 4 UMETA(DisplayName = "Dodge"),
	Climbing = 5 UMETA(DisplayName = "Climbing"),
};

UENUM(BlueprintType)
enum EFaction
{
	Loner = 0 UMETA(DisplayName = "Loner"),
	Survivor = 1 UMETA(DisplayName = "Survivor"),
	Inquisitor = 2 UMETA(DisplayName = "Inquisitor"),
	G8 = 3 UMETA(DisplayName = "G8"),
	Animus = 4 UMETA(DisplayName = "Animus"),
	Plagued = 5 UMETA(DisplayName = "Plagued"),
	Feral = 6 UMETA(DisplayName = "Feral"),
	Critter = 7 UMETA(DisplayName = "Critter"),
};

void Print(FString print);
void Print(int print);
void Print(float print);