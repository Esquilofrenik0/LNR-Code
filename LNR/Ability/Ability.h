#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemInterface.h"
#include "Ability.generated.h"

UENUM(BlueprintType)
enum class EAbilityInput : uint8
{
	Passive = 0 UMETA(DisplayName = "Passive"),
	Confirm = 1 UMETA(DisplayName = "Confirm"),
	Cancel = 2 UMETA(DisplayName = "Cancel"),
	Attack = 3 UMETA(DisplayName = "Attack"),
	Block = 4 UMETA(DisplayName = "Block"),
	Sprint = 5 UMETA(DisplayName = "Sprint"),
	Dodge = 6 UMETA(DisplayName = "Dodge")
};

UCLASS()
class LNR_API UAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UAbility();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAbilityInput AbilityInput = EAbilityInput::Passive;
};
