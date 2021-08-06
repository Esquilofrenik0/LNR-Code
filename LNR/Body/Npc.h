#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "Npc.generated.h"

UCLASS()
class LNR_API ANpc : public AAIController
{
	GENERATED_BODY()
public:
	ANpc();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABody* Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	class UBehaviorTreeComponent* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	UBlackboardComponent* BlackboardComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	FName TargetKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	FName DestinationKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sense)
	float SightRadius = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sense)
	float SightAge = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sense)
	float LooseSightRadius = SightRadius + 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sense)
	float FieldOfView = 120.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(BlueprintReadWrite)
	class ABody* Target;
	FTimerHandle LooseTargetHandle;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION() void OnPawnDetected(const TArray<AActor*>& DetectedPawns);
	UFUNCTION() void CanSeeTarget();
};
