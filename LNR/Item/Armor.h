#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Armor.generated.h"

UENUM()
enum ArmorSlot
{
	Head = 0 UMETA(DisplayName = "Head"),
	Back = 1 UMETA(DisplayName = "Back"),
	Chest = 2 UMETA(DisplayName = "Chest"),
	Legs = 3 UMETA(DisplayName = "Legs"),
	Feet = 4 UMETA(DisplayName = "Feet")
};

UCLASS()
class LNR_API UArmor : public UItem
{
	GENERATED_BODY()
public:
	UArmor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ArmorSlot> type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;

	virtual void UseItem(AHero* hero) override;
	virtual FString PrintItemData() override;
};
