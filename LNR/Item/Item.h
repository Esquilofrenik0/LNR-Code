#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, CollapseCategories)
class LNR_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPickable;

	virtual void UseItem(class AHero* hero);

	UFUNCTION(BlueprintCallable)
	bool Compare(UItem* item);

	UFUNCTION(BlueprintCallable)
	virtual FString PrintItemData();
};
