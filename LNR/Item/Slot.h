#pragma once
#include "Item.h"
#include "CoreMinimal.h"
#include "Slot.generated.h"

USTRUCT(BlueprintType)
struct FSlot
{
	GENERATED_USTRUCT_BODY()

	FSlot() : item(nullptr), amount(1)
	{
	}

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	UItem* item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount;
};
