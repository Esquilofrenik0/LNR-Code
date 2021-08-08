#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS(Blueprintable)
class LNR_API ABuilding : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated, Instanced, EditAnywhere, BlueprintReadWrite)
	class UItem* Item;

	UFUNCTION(BlueprintCallable)
	void SetItem(UItem* nItem);
	UFUNCTION(Server, Reliable)
	void ServerSetItem(UItem* nItem);

	UFUNCTION(BlueprintCallable)
	void DestroyItem();
	UFUNCTION(Server, Reliable)
	void ServerDestroyItem();
	UFUNCTION(NetMulticast, Reliable)
	void MultiDestroyItem();
};
