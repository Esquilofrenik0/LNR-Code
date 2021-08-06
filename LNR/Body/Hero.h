#pragma once
#include "CoreMinimal.h"
#include "Human.h"
#include "LNR/Item/Gun.h"
#include "LNR/LNR.h"
#include "Hero.generated.h"

UCLASS()
class AHero : public AHuman, public IFoliagePluginInterface
{
	GENERATED_BODY()
public:
	AHero();
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UInventory* Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class USpringArmComponent* TPArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UCameraComponent* TPCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class USpringArmComponent* FPArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UCameraComponent* FPCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UCameraComponent* WorldMapCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BaseLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector WorldMapLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector LocalMapLocation;
	UPROPERTY(BlueprintReadWrite) float DefaultFieldOfView;
	UPROPERTY(BlueprintReadWrite) float InputAxisYaw;
	UPROPERTY(BlueprintReadWrite) float InputAxisPitch;
	UPROPERTY(BlueprintReadWrite) float InputAxisRight;
	
	UPROPERTY(BlueprintReadWrite) class AContainer* Container;
	UPROPERTY(BlueprintReadWrite) FTimerHandle RegenerationHandle;
	UPROPERTY(BlueprintReadWrite) FTimerHandle ClientTickTimer;
	UPROPERTY(BlueprintReadWrite) bool InventoryOpen;
	UPROPERTY(BlueprintReadWrite) bool WorldMapActive;
	UPROPERTY(BlueprintReadWrite) bool LocalMapActive;
	UPROPERTY(BlueprintReadWrite) bool firstPerson;

	UPROPERTY(Replicated, BlueprintReadWrite) float Pitch;

	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartJump();
	void StopJump();

	void StartCrouch();
	void StopCrouch();

	void StartAttack();
	void StopAttack();

	void StartSprint();
	void StopSprint();

	void StartBlock();
	void StopBlock();

	void StartDodge();
	void StartHolster();
	void StartWeaponSwap();
	void StartWorldMap();
	void StartInventory();

	UFUNCTION(BlueprintCallable) void ClientTick();

	UFUNCTION(BlueprintCallable) void GrabWall();
	UFUNCTION(BlueprintCallable) void WallTimer();
	UFUNCTION(BlueprintCallable) FHitResult WallCheck();
	UFUNCTION(BlueprintCallable) void SetClimbing(bool value);
	UFUNCTION(Server, Reliable) void ServerSetClimbing(bool value);
	
	UFUNCTION(BlueprintCallable) void CycleCameras();
	UFUNCTION(BlueprintCallable) void ResetCamera();

	UFUNCTION(BlueprintCallable) void StartInteract();
	UFUNCTION(Server, Reliable) void ServerInteract();
	UFUNCTION(BlueprintCallable)AActor* GetTraceHitActor();

	UFUNCTION(BlueprintCallable) void UseItem(class UItem* item);
	UFUNCTION(Server, Reliable) void ServerUseItem(class UItem* item);

	UFUNCTION(BlueprintCallable) void TraceHud();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void WriteWorldInfo(const FString& worldInfo);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void ClearWorldInfo();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void OpenContainer(AContainer* hitContainer);

	virtual void DropInventory() override;
	virtual void Die() override;
	virtual void DestroyCorpse() override;

	UFUNCTION(Server, Reliable) void SetAttacking(bool value);
	UFUNCTION(Server, Reliable) void SetSprinting(bool value);
	UFUNCTION(Server, Reliable)	void SetBlocking(bool value);

	UFUNCTION(Server, Reliable, BlueprintCallable) void ServerSetFieldOfView(float value);
	UFUNCTION(Client, Reliable, BlueprintCallable) void ClientSetFieldOfView(float value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void SetInputModeUi(bool value);
	UFUNCTION(BlueprintImplementableEvent) void ShowInventory(bool value);
	UFUNCTION(BlueprintImplementableEvent) void ShowWorldMap(bool value);
	UFUNCTION(BlueprintImplementableEvent) void ShowWorldMarkers(bool value);
	UFUNCTION(BlueprintImplementableEvent) void UpdateCompass();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Foliage Plugin | Interface")
	void OnFoliageHarvested(AActor* FoliageActor, const TArray<FFoliageRewardData>& Rewards);
};
