#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Container.generated.h"

UCLASS()
class LNR_API AContainer : public AActor
{
	GENERATED_BODY()
public:
	AContainer();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Container;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventory* Inventory;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual FString PrintContainerData();
};
