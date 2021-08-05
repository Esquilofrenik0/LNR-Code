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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Attacking)
	bool Attacking;
	UFUNCTION()
	void OnRep_Attacking(bool oldAttacking);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Sprinting)
	bool Sprinting;
	UFUNCTION()
	void OnRep_Sprinting(bool oldSprinting);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Blocking)
	bool Blocking;
	UFUNCTION()
	void OnRep_Blocking(bool oldBlocking);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_State)
	TEnumAsByte<EState> State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Faction)
	TEnumAsByte<EFaction> Faction;
	UFUNCTION()
	virtual void OnRep_State(TEnumAsByte<EState> oldState);
	UFUNCTION()
	virtual void OnRep_Faction(TEnumAsByte<EFaction> oldFaction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Combo)
	int Combo;
	UFUNCTION()
	virtual void OnRep_Combo(int oldCombo);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxCombo)
	int MaxCombo;
	UFUNCTION()
	virtual void OnRep_MaxCombo(int oldMaxCombo);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
	float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Hunger)
	float Hunger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Damage)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Defense)
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxHunger)
	float MaxHunger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_BaseDamage)
	float BaseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_BaseDefense)
	float BaseDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_HealthRegeneration)
	float HealthRegeneration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_StaminaRegeneration)
	float StaminaRegeneration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_HungerRegeneration)
	float HungerRegeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_RespawnTime)
	float RespawnTime;

	UFUNCTION()
	virtual void OnRep_Health(float oldHealth);
	UFUNCTION()
	virtual void OnRep_Stamina(float oldStamina);
	UFUNCTION()
	virtual void OnRep_Hunger(float oldHunger);
	UFUNCTION()
	virtual void OnRep_Damage(float oldDamage);
	UFUNCTION()
	virtual void OnRep_Defense(float oldDefense);

	UFUNCTION()
	virtual void OnRep_MaxHealth(float oldMaxHealth);
	UFUNCTION()
	virtual void OnRep_MaxStamina(float oldMaxStamina);
	UFUNCTION()
	virtual void OnRep_MaxHunger(float oldMaxHunger);
	UFUNCTION()
	virtual void OnRep_BaseDamage(float oldBaseDamage);
	UFUNCTION()
	virtual void OnRep_BaseDefense(float oldBaseDefense);

	UFUNCTION()
	virtual void OnRep_HealthRegeneration(float oldHealthRegeneration);
	UFUNCTION()
	virtual void OnRep_StaminaRegeneration(float oldStaminaRegeneration);
	UFUNCTION()
	virtual void OnRep_HungerRegeneration(float oldHungerRegeneration);

	UFUNCTION()
	virtual void OnRep_RespawnTime(float oldRespawnTime);
};
