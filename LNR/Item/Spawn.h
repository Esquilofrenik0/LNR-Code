#pragma once
#include "Item.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawn.generated.h"

UCLASS(Blueprintable)
class LNR_API ASpawn : public AActor
{
	GENERATED_BODY()
public:
	ASpawn();
	UPROPERTY(Replicated, Instanced, EditAnywhere, BlueprintReadWrite)
	class UItem* Item;
	
	virtual void BeginPlay() override;

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
