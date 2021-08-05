#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Trace.generated.h"

UCLASS()
class LNR_API UTrace : public UActorComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	FHitResult Line(FVector start, FVector end, float drawTime, bool printName);
	
	UFUNCTION(BlueprintCallable)
	FHitResult Circle(FVector start, float radius, float drawTime, bool printName);
};
