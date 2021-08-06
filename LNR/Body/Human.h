#pragma once
#include "CoreMinimal.h"
#include "Body.h"
#include "Human.generated.h"

UCLASS()
class LNR_API AHuman : public ABody
{
	GENERATED_BODY()
public:
	AHuman();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEquipment* Equipment;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Head;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Back;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Chest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Legs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Feet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponComponent* RightHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponComponent* LeftHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponComponent* RightHolster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponComponent* LeftHolster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponComponent* RightBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponComponent* LeftBack;

	virtual void PossessedBy(AController* NewController) override;
	virtual void Holster(bool value) override;
	virtual void RefreshAttributes() override;

	virtual void WeaponSwap();
	UFUNCTION(Server, Reliable)
	void ServerWeaponSwap();

	virtual void TraceMelee() override;
	virtual UAnimMontage* GetCombatMontage() override;	
};
