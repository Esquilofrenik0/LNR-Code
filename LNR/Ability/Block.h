﻿#pragma once
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LNR/Ability/Ability.h"
#include "Block.generated.h"

UCLASS()
class LNR_API UBlock : public UAbility
{
	GENERATED_BODY()
public:
	UBlock();

	UPROPERTY()
	class ABody* Body;
	UPROPERTY()
	class AHero* Hero;
	UPROPERTY()
	class UCharacterMovementComponent* Move;
	UPROPERTY()
	FTimerHandle BlockTimer;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void TickBlock();
	UFUNCTION(Client, Reliable)
	void ClientSetSpeed(float Speed, class UCharacterMovementComponent* CharacterMovement);

	UFUNCTION(Client, Reliable)
	void ClientSetCamera(class AHero* nHero, bool reset);
};
