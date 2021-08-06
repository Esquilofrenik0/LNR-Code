#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "LNR/Ability/Ability.h"
#include "LNR/LNR.h"
#include "LNR/Item/Dropable.h"
#include "LNR/Object/Container.h"
#include "Body.generated.h"

UCLASS(config=Game)
class LNR_API ABody : public ACharacter, public IAbilitySystemInterface, public IFactionAgentInterface
{
	GENERATED_BODY()
public:
	ABody();

	FTimerHandle RespawnHandle, ResetComboHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilitySystem)
	class UAttributes* Attributes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	class UAction* Action;
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
	class UTrace* Trace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite) UAnimInstance* Animator;
	UPROPERTY(Replicated, BlueprintReadWrite) bool IsAiming;
	UPROPERTY(Replicated, BlueprintReadWrite) bool IsShooting;
	UPROPERTY(Replicated, BlueprintReadWrite) FTransform LastHandTransform;	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Ability, Category = AbilitySystem)
	TArray<FGameplayAbilitySpecHandle> Ability;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Passive, Category = AbilitySystem)
	TArray<FGameplayAbilitySpecHandle> Passive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AbilitySystem)
	TArray<TSubclassOf<class UAbility>> DefaultAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AbilitySystem)
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<struct FDropable> Dropables;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UStaticMesh* LootBagMesh;
	UPROPERTY(Replicated) AContainer* LootBag;
	
	UFUNCTION() void OnRep_Ability(TArray<FGameplayAbilitySpecHandle> oldAbility);
	UFUNCTION() void OnRep_Passive(TArray<FGameplayAbilitySpecHandle> oldPassive);
	
	UFUNCTION(Server, Reliable, BlueprintCallable) void ServerSetIsAiming(bool value);
	
	UPROPERTY(BlueprintReadOnly) class APlayor* Player;
	UPROPERTY(BlueprintReadOnly) class ANpc* Npc;

	UPROPERTY(BLueprintReadWrite)
	TArray<AActor*> MeleeHits;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> UnarmedMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* TakeDamageMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GunDistanceFromCamera = 10;
	
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;

	virtual FFaction GetFaction() const override;
	virtual void SetFaction(const FFaction& InFaction) override;

	UFUNCTION() virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION() virtual void InitializeAttributes();
	UFUNCTION() virtual void GiveAbilities();

	UFUNCTION(BlueprintCallable) virtual void RefreshAttributes();
	UFUNCTION(Server, Reliable) void ServerRefreshAttributes();

	UFUNCTION(BlueprintCallable) virtual void Die();
	UFUNCTION(BlueprintCallable) virtual void DestroyCorpse();
	UFUNCTION(BlueprintCallable) virtual void Respawn();

	UFUNCTION(BlueprintCallable) void Attack();
	UFUNCTION(BlueprintCallable) void Sprint();
	UFUNCTION(BlueprintCallable) void Dodge();
	UFUNCTION(BlueprintCallable) void Block();

	UFUNCTION(BlueprintCallable) virtual void Holster(bool value);
	UFUNCTION(Server, Reliable) void ServerHolster(bool value);

	UFUNCTION(BlueprintCallable) virtual void ResetMelee();
	UFUNCTION(BlueprintCallable) virtual void TraceMelee();
	UFUNCTION(BlueprintCallable) virtual ABody* Shoot();
	UFUNCTION(BlueprintCallable) virtual UAnimMontage* GetCombatMontage();
	UFUNCTION(BlueprintCallable) virtual void ResetCombo();

	UFUNCTION(BlueprintImplementableEvent) void ResetRagdoll();
	UFUNCTION(BlueprintImplementableEvent) void StartRagdoll();
	UFUNCTION(BlueprintImplementableEvent) void StopRagdoll();
	
	UFUNCTION(BlueprintCallable) virtual void DropInventory();
	UFUNCTION(BlueprintCallable) void DropBag();
	UFUNCTION(Server, Reliable) void ServerDropBag();
	UFUNCTION(NetMulticast, Reliable) void MultiDropBag();

	void PlayMontage(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage);
	UFUNCTION(Server, Reliable) void ServerPlayMontage(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage);
	UFUNCTION(NetMulticast, Reliable) void MultiPlayMontage(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage);
	void OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void EnterAim();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void ExitAim();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void Fire();	
	UFUNCTION(Server, Reliable, BlueprintCallable) void ServerSetLastHandTransform(FTransform value);
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, class AActor* DamageCauser) override;
};
