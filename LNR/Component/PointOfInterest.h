#pragma once
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PointOfInterest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetMarker);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShowMarker);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHideMarker);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class LNR_API UPointOfInterest : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UPointOfInterest();
	UPROPERTY(BlueprintReadWrite) class AActor* Actor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UWidgetComponent* WorldMapIcon;
	
	UPROPERTY(BlueprintAssignable) FSetMarker OnSetMarker;
	UPROPERTY(BlueprintAssignable) FShowMarker OnShowMarker;;
	UPROPERTY(BlueprintAssignable) FHideMarker OnHideMarker;;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable) void SetMarker();
	UFUNCTION(BlueprintCallable) void ShowMarker();
	UFUNCTION(BlueprintCallable) void HideMarker();
}; 
