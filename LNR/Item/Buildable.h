#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Buildable.generated.h"

UCLASS()
class LNR_API UBuildable : public UItem
{
	GENERATED_BODY()
public:
	UBuildable();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FName Id;
	virtual void UseItem(AHero* hero) override;
	virtual FString PrintItemData() override;	
};
