#include "Attributes.h"
#include "AbilitySystemComponent.h"
#include "LNR/LNR.h"
#include "Net/UnrealNetwork.h"

UAttributes::UAttributes()
{
	State = EState::Idle;

	Combo = 0;
	MaxCombo = 1;
	Attacking = false;
	Sprinting = false;
	Blocking = false;

	MaxHealth = 100;
	MaxStamina = 100;
	MaxHunger = 100;
	BaseDamage = 1;
	BaseDefense = 1;
	Health = MaxHealth;
	Stamina = MaxStamina;
	Hunger = 0;
	Damage = BaseDamage;
	Defense = BaseDefense;

	HealthRegeneration = 1;
	StaminaRegeneration = 1;
	HungerRegeneration = 0.1;
	
	RespawnTime = 60;
}

float UAttributes::GetHealthPercent() { return Health / MaxHealth; }

float UAttributes::GetStaminaPercent() { return Stamina / MaxStamina; }

float UAttributes::GetHungerPercent() { return Hunger / MaxHunger; }

FString UAttributes::GetHealthText()
{
	return "Health: " + FString::FromInt(Health) + " / " + FString::FromInt(MaxHealth) + " (+" +
		FString::FromInt(HealthRegeneration) + "/s)";
}

FString UAttributes::GetStaminaText()
{
	return "Stamina: " + FString::FromInt(Stamina) + " / " + FString::FromInt(MaxStamina) + " (+" +
		FString::FromInt(StaminaRegeneration) + "/s)";
}

FString UAttributes::GetHungerText()
{
	return "Hunger: " + FString::FromInt(Hunger) + " / " + FString::FromInt(MaxHunger) + " (+" +
		FString::FromInt(HungerRegeneration) + "/s)";
}

FString UAttributes::GetDamageText()
{
	return "Damage: " + FString::FromInt(Damage) + " (Base: " + FString::FromInt(BaseDamage) + ")";
}

FString UAttributes::GetDefenseText()
{
	return "Defense: " + FString::FromInt(Defense) + " (Base: " + FString::FromInt(BaseDefense) + ")";
}

void UAttributes::Regenerate()
{
	Health += HealthRegeneration;
	if (Health > MaxHealth) Health = MaxHealth;
	Stamina += StaminaRegeneration;
	if (Stamina > MaxStamina) Stamina = MaxStamina;
	Hunger += HungerRegeneration;
	if (Hunger > MaxHunger) Hunger = MaxHunger;
}

void UAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, State, COND_None, REPNOTIFY_Always);
	// DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Faction, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Combo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, MaxCombo, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Hunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Defense, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, MaxHunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, BaseDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, BaseDefense, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, StaminaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, HungerRegeneration, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Attacking, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Sprinting, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, Blocking, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributes, RespawnTime, COND_None, REPNOTIFY_Always);
}

void UAttributes::OnRep_Attacking(bool oldAttacking)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Attacking, oldAttacking);
}

void UAttributes::OnRep_Sprinting(bool oldSprinting)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Sprinting, oldSprinting);
}

void UAttributes::OnRep_Blocking(bool oldBlocking)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Blocking, oldBlocking);	
}

void UAttributes::OnRep_State(TEnumAsByte<EState> oldState)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, State, oldState);
}

void UAttributes::OnRep_Faction(EFaction oldFaction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Faction, oldFaction);
}

void UAttributes::OnRep_Combo(int oldCombo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Combo, oldCombo);
}

void UAttributes::OnRep_MaxCombo(int oldMaxCombo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, MaxCombo, oldMaxCombo);
}

void UAttributes::OnRep_Health(float oldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Health, oldHealth);
}

void UAttributes::OnRep_Stamina(float oldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Stamina, oldStamina);
}

void UAttributes::OnRep_Hunger(float oldHunger)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Hunger, oldHunger);
}

void UAttributes::OnRep_Damage(float oldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Damage, oldDamage);
}

void UAttributes::OnRep_Defense(float oldDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Defense, oldDefense);
}

void UAttributes::OnRep_MaxHealth(float oldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, MaxHealth, oldMaxHealth);
}

void UAttributes::OnRep_MaxStamina(float oldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, MaxStamina, oldMaxStamina);
}

void UAttributes::OnRep_MaxHunger(float oldMaxHunger)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, MaxHunger, oldMaxHunger);
}

void UAttributes::OnRep_BaseDamage(float oldBaseDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, BaseDamage, oldBaseDamage);
}

void UAttributes::OnRep_BaseDefense(float oldBaseDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, Hunger, oldBaseDefense);
}

void UAttributes::OnRep_HealthRegeneration(float oldHealthRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, HealthRegeneration, oldHealthRegeneration);
}

void UAttributes::OnRep_StaminaRegeneration(float oldStaminaRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, StaminaRegeneration, oldStaminaRegeneration);
}

void UAttributes::OnRep_HungerRegeneration(float oldHungerRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, HungerRegeneration, oldHungerRegeneration);
}

void UAttributes::OnRep_RespawnTime(float oldRespawnTime)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributes, RespawnTime, oldRespawnTime);
}
