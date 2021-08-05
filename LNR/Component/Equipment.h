#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment.generated.h"

UCLASS()
class LNR_API UEquipment : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABody* Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Mesh;
	
	UPROPERTY(ReplicatedUsing = OnRep_Armor, Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<class UArmor*> Armor;
	UPROPERTY(ReplicatedUsing = OnRep_Weapon, Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<class UWeapon*> Weapon;

	UPROPERTY(ReplicatedUsing = OnRep_CombatStance, EditAnywhere, BlueprintReadWrite)
	bool CombatStance;
	
	UPROPERTY(VisibleAnywhere, Instanced, BlueprintReadWrite)
	TArray<class USkeletalMeshComponent*> ArmorSlot;
	UPROPERTY(VisibleAnywhere, Instanced, BlueprintReadWrite)
	TArray<class UWeaponComponent*> WeaponSlot;
	
	UPROPERTY(VisibleAnywhere, Instanced, BlueprintReadWrite)
	TArray<class UWeaponComponent*> HolsterSlot;

	UFUNCTION()
	void OnRep_Armor(TArray<UArmor*> oldArmor);
	UFUNCTION()
	void OnRep_Weapon(TArray<UWeapon*> oldWeapon);

	UFUNCTION()
	void OnRep_CombatStance(bool oldCombatStance);
	
	UFUNCTION(BlueprintCallable)
	UArmor* GetArmor(int index);	
	UFUNCTION(BlueprintCallable)
	void EquipArmor(class UArmor* nArmor);
	UFUNCTION(BlueprintCallable)
	void UnEquipArmor(int index);

	UFUNCTION(BlueprintCallable)
	UWeapon* GetWeapon(int index);
	UFUNCTION(BlueprintCallable)
	int GetWeaponSlot(class UWeapon* nWeapon);
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(class UWeapon* nWeapon);
	UFUNCTION(BlueprintCallable)
	void UnEquipWeapon(int index);

	UFUNCTION(BlueprintCallable)
	void WeaponSwap();

	UFUNCTION(BlueprintCallable)
	void SortArmor();
	UFUNCTION(BlueprintCallable)
	void SortWeapon();
	
protected:
	void DressArmor(int index, class UArmor* nArmor);
	void SetArmor(int index, class UArmor* nArmor);
	UFUNCTION(Server, Reliable)
	void ServerSetArmor(int index, class UArmor* nArmor);
	
	void DressWeapon(int index, class UWeapon* nWeapon);
	void SetWeapon(int index, class UWeapon* nWeapon);
	UFUNCTION(Server, Reliable)
	void ServerSetWeapon(int index, class UWeapon* nWeapon);
};
