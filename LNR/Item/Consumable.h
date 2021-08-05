#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Consumable.generated.h"

UCLASS()
class LNR_API UConsumable : public UItem
{
	GENERATED_BODY()
public:
	UConsumable();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere)
	float healHealth;
	UPROPERTY(EditAnywhere)
	float healStamina;
	UPROPERTY(EditAnywhere)
	float healHunger;

	virtual void UseItem(AHero* hero) override;
	virtual FString PrintItemData() override;
};
