#pragma once
#include "Item.h"
#include "CoreMinimal.h"
#include "Dropable.generated.h"

USTRUCT(BlueprintType)
struct FDropable
{
	GENERATED_USTRUCT_BODY()

	FDropable() : item(nullptr), amount(1), chance(100)
	{
	}

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	UItem* item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float chance;
};
