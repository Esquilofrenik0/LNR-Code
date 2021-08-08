#include "Inventory.h"
#include "../Item/Item.h"
#include "Net/UnrealNetwork.h"

UInventory::UInventory()
{
	nSlots = 32;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
	CreateSlots(nSlots);
}

void UInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInventory, Slots);
}

bool UInventory::HasItem(FName itemName, int amount)
{
	for(FSlot slot : Slots) if(slot.Item != nullptr && slot.Item->Name == itemName && slot.Amount >= amount) return true;
	return false;
}

void UInventory::AddItem(class UItem* item, int amount)
{
	if(item == nullptr || amount <= 0) return;
	if (GetOwnerRole() == ROLE_Authority)
	{
		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].Item != nullptr && Slots[i].Item->Compare(item))
			{
				int finalAmount = Slots[i].Amount + amount;
				if(Slots[i].Item->Stack >= finalAmount)
				{
					Slots[i].Amount += amount;					
					return;
				}
				else
				{
					int receivedAmount = item->Stack - Slots[i].Amount;
					Slots[i].Amount += receivedAmount;
					amount -= receivedAmount;
				}
			}
		}
		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].Amount == 0 || Slots[i].Item == nullptr)
			{
				Slots[i].Item = item;
				Slots[i].Amount = amount;
				return;
			}
		}
	}
	else ServerAddItem(item, amount);
}

void UInventory::ServerAddItem_Implementation(class UItem* item, int amount)
{
	AddItem(item, amount);
}

void UInventory::RemoveItem(class UItem* item, int amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].Item != nullptr && Slots[i].Item->Compare(item))
			{
				Slots[i].Amount -= amount;
				if (Slots[i].Amount <= 0) Slots[i].Item = nullptr;
				return;
			}
		}
	}
	else
	{
		ServerRemoveItem(item, amount);
	}
}

void UInventory::ServerRemoveItem_Implementation(class UItem* item, int amount)
{
	RemoveItem(item);
}

void UInventory::StoreItem(class UItem* item, class UInventory* inventory, int amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		inventory->AddItem(item, amount);
		RemoveItem(item, amount);
	}
	else
	{
		ServerStoreItem(item, inventory, amount);
	}
}

void UInventory::ServerStoreItem_Implementation(class UItem* item, class UInventory* inventory, int amount)
{
	StoreItem(item, inventory, amount);
}

void UInventory::RetrieveItem(class UItem* item, class UInventory* inventory, int amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		AddItem(item, amount);
		inventory->RemoveItem(item, amount);
	}
	else
	{
		ServerRetrieveItem(item, inventory, amount);
	}
}

void UInventory::ServerRetrieveItem_Implementation(class UItem* item, class UInventory* inventory, int amount)
{
	RetrieveItem(item, inventory);
}

void UInventory::CreateSlots(int num)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		for (int i = 0; i < num; i++)
		{
			if (i >= Slots.Num()) Slots.Add(FSlot());
		}
	}
	else
	{
		ServerCreateSlots(num);
	}
}

void UInventory::ServerCreateSlots_Implementation(int num)
{
	CreateSlots(num);
}
