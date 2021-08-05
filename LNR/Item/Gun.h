#pragma once
#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"

UCLASS()
class LNR_API UGun : public UWeapon
{
	GENERATED_BODY()
public:
	UGun();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxAmmo; 
};
