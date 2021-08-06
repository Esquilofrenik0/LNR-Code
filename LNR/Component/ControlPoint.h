#pragma once
#include "CoreMinimal.h"
#include "PointOfInterest.h"
#include "LNR/LNR.h"
#include "ControlPoint.generated.h"

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class LNR_API UControlPoint : public UPointOfInterest
{
	GENERATED_BODY()
public:
	UControlPoint();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<TSubclassOf<class ABody>> SpawnTemplates;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<class UTexture2D*> FactionIcons;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FFaction ControlFaction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FFaction ContestingFaction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<class ABody*> Bodies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float Influence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float IncrementAmount;
	UPROPERTY(BlueprintReadWrite) FTimerHandle InfluenceTimer;
	
	UPROPERTY(BlueprintReadWrite) TArray<FFaction> Factions;
	
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable) TSubclassOf<ACharacter> GetSpawnTemplate();
	UFUNCTION(BlueprintCallable) UTexture2D* GetFactionIcon();
	UFUNCTION(BlueprintCallable) FLinearColor GetFactionColor();
	UFUNCTION(BlueprintCallable) void AddBody(ABody* body);
	UFUNCTION(BlueprintCallable) void RemoveBody(ABody* body);
	UFUNCTION(BlueprintCallable) void StartIncreaseInfluence();
	UFUNCTION(BlueprintCallable) void IncreaseInfluence();
	UFUNCTION(BlueprintCallable) void StartDecreaseInfluence();
	UFUNCTION(BlueprintCallable) void DecreaseInfluence();
	UFUNCTION(BlueprintCallable) FFaction GetWinningFaction();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetControl);
	UPROPERTY(BlueprintAssignable) FSetControl SetControl;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetAllFactions);
	UPROPERTY(BlueprintAssignable) FGetAllFactions GetAllFactions;
	UFUNCTION(BlueprintCallable) int GetFactionNum(FFaction faction);
	UFUNCTION(BlueprintCallable) FFaction GetFactionValue(int num);
}; 
