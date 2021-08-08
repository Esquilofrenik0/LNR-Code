#pragma once
#include "Item.h"
#include "CoreMinimal.h"
#include "Slot.generated.h"

USTRUCT(BlueprintType)
struct FSlot
{
	GENERATED_USTRUCT_BODY()

	FSlot() : Item(nullptr), Amount(1)
	{
	}

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite) UItem* Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int Amount;
};
