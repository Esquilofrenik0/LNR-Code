#pragma once
#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

UCLASS()
class LNR_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UWeapon* Weapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UStaticMeshComponent*> Attachments;

	void SetupAttachments(UWeapon* nWeapon);
};
