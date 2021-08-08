#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Resource.generated.h"

UCLASS()
class LNR_API UResource : public UItem
{
	GENERATED_BODY()
public:
	UResource();
	virtual FString PrintItemData() override;
};
