#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "SkSpawn.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum EWeaponType
{
	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
	Pistol = 1 UMETA(DisplayName = "Pistol"),
	Rifle = 2 UMETA(DisplayName = "Rifle"),
	Sword = 3 UMETA(DisplayName = "Sword"),
	Axe = 4 UMETA(DisplayName = "Axe"),
	GreatSword = 5 UMETA(DisplayName = "GreatSword"),
	GreatAxe = 6 UMETA(DisplayName = "GreatAxe"),
	Bow = 7 UMETA(DisplayName = "Bow"),
	Shield = 8 UMETA(DisplayName = "Shield")
};

UENUM(BlueprintType)
enum EWeaponSlot
{
	RightHand = 0 UMETA(DisplayName = "RightHand"),
	LeftHand = 1 UMETA(DisplayName = "LeftHand"),
	TwoHand = 2 UMETA(DisplayName = "TwoHand"),
	AnyHand = 3 UMETA(DisplayName = "AnyHand")
};

UCLASS()
class LNR_API UWeapon : public UItem
{
	GENERATED_BODY()
public:
	UWeapon();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWeaponType> type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWeaponSlot> slot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> CombatMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> Attachments;
	
	virtual void UseItem(AHero* hero) override;
	virtual FString PrintItemData() override;
};
