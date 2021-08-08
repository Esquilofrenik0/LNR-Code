#pragma once
#include "CoreMinimal.h"
#include "Slot.h"
#include "Item.h"
#include "Recipe.generated.h"

UCLASS() 
class LNR_API URecipe : public UItem
{
	GENERATED_BODY()
public:
	URecipe();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TSubclassOf<UItem> Result;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FSlot> Cost;
	virtual FString PrintItemData() override;
	virtual void UseItem(class AHero* hero) override;
	UFUNCTION(BlueprintCallable) bool CanCreate(class AHero* hero);
	UFUNCTION(BlueprintCallable) void CreateItem(class AHero* hero);
};
