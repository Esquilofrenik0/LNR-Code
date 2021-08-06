#pragma once
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "LNR/LNR.h"
#include "Attributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class LNR_API UAttributes : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAttributes();

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();
	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent();
	UFUNCTION(BlueprintCallable)
	float GetHungerPercent();
	UFUNCTION(BlueprintCallable)
	FString GetHealthText();
	UFUNCTION(BlueprintCallable)
	FString GetStaminaText();
	UFUNCTION(BlueprintCallable)
	FString GetHungerText();

	UFUNCTION(BlueprintCallable)
	FString GetDamageText();
	UFUNCTION(BlueprintCallable)
	FString GetDefenseText();

	UFUNCTION(BlueprintCallable)
	void Regenerate();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Attacking)
	bool Attacking;
	UFUNCTION() void OnRep_Attacking(bool oldAttacking);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Sprinting)
	bool Sprinting;
	UFUNCTION() void OnRep_Sprinting(bool oldSprinting);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Blocking)
	bool Blocking;
	UFUNCTION() void OnRep_Blocking(bool oldBlocking);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_State)
	TEnumAsByte<EState> State;
	UFUNCTION() virtual void OnRep_State(TEnumAsByte<EState> oldState);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Faction)
	TEnumAsByte<EFaction> Faction;
	UFUNCTION() virtual void OnRep_Faction(EFaction oldFaction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Combo)
	int Combo;
	UFUNCTION() virtual void OnRep_Combo(int oldCombo);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxCombo)
	int MaxCombo;
	UFUNCTION() virtual void OnRep_MaxCombo(int oldMaxCombo);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health)
	float Health;
	UFUNCTION()	virtual void OnRep_Health(float oldHealth);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Stamina)
	float Stamina;
	UFUNCTION()	virtual void OnRep_Stamina(float oldStamina);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Hunger)
	float Hunger;
	UFUNCTION()	virtual void OnRep_Hunger(float oldHunger);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Damage)
	float Damage;
	UFUNCTION()	virtual void OnRep_Damage(float oldDamage);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Defense)
	float Defense;
	UFUNCTION()	virtual void OnRep_Defense(float oldDefense);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth)
	float MaxHealth;
	UFUNCTION()	virtual void OnRep_MaxHealth(float oldMaxHealth);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxStamina)
	float MaxStamina;
	UFUNCTION()	virtual void OnRep_MaxStamina(float oldMaxStamina);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHunger)
	float MaxHunger;
	UFUNCTION()	virtual void OnRep_MaxHunger(float oldMaxHunger);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_BaseDamage)
	float BaseDamage;
	UFUNCTION()	virtual void OnRep_BaseDamage(float oldBaseDamage);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_BaseDefense)
	float BaseDefense;
	UFUNCTION()	virtual void OnRep_BaseDefense(float oldBaseDefense);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HealthRegeneration)
	float HealthRegeneration;
	UFUNCTION()	virtual void OnRep_HealthRegeneration(float oldHealthRegeneration);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_StaminaRegeneration)
	float StaminaRegeneration;
	UFUNCTION()	virtual void OnRep_StaminaRegeneration(float oldStaminaRegeneration);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HungerRegeneration)
	float HungerRegeneration;
	UFUNCTION()	virtual void OnRep_HungerRegeneration(float oldHungerRegeneration);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RespawnTime)
	float RespawnTime;
	UFUNCTION()	virtual void OnRep_RespawnTime(float oldRespawnTime);
};
