#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Compass.generated.h"

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class LNR_API UCompass : public UActorComponent
{
	GENERATED_BODY()	
public:
	UFUNCTION(BlueprintCallable) float RotationToCircleDegrees(int value);
	UFUNCTION(BlueprintCallable) float GetDelta(int a, int b, bool clockwise);
};
