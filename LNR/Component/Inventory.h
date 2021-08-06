#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/Slot.h"
#include "Inventory.generated.h"

UCLASS()
class LNR_API UInventory : public UActorComponent
{
	GENERATED_BODY()
public:
	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int nSlots;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FSlot> Slots;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AddItem(class UItem* item, int amount = 1);
	UFUNCTION(Server, Reliable)
	void ServerAddItem(class UItem* dItem, int amount);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(class UItem* item);
	UFUNCTION(Server, Reliable)
	void ServerRemoveItem(class UItem* dItem);

	UFUNCTION(BlueprintCallable)
	void StoreItem(class UItem* item, class UInventory* inventory);
	UFUNCTION(Server, Reliable)
	void ServerStoreItem(class UItem* dItem, class UInventory* inventory);

	UFUNCTION(BlueprintCallable)
	void RetrieveItem(class UItem* item, class UInventory* inventory);
	UFUNCTION(Server, Reliable)
	void ServerRetrieveItem(class UItem* dItem, class UInventory* inventory);

	UFUNCTION(BlueprintCallable)
	void CreateSlots(int num);
	UFUNCTION(Server, Reliable)
	void ServerCreateSlots(int num);
};
