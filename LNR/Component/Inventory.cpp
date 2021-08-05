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
	//Replicate to everyone
	DOREPLIFETIME(UInventory, Slots);
}

void UInventory::AddItem(class UItem* item, int amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].item == item)
			{
				Slots[i].amount += amount;
				return;
			}
		}
		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].amount == 0 || Slots[i].item == nullptr)
			{
				Slots[i].item = item;
				Slots[i].amount = amount;
				return;
			}
		}
	}
	else
	{
		ServerAddItem(item);
	}
}

void UInventory::ServerAddItem_Implementation(class UItem* item)
{
	AddItem(item);
}

void UInventory::RemoveItem(class UItem* item)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].item == item)
			{
				Slots[i].amount -= 1;
				if (Slots[i].amount <= 0) { Slots[i].item = nullptr; }
				return;
			}
		}
	}
	else
	{
		ServerRemoveItem(item);
	}
}

void UInventory::ServerRemoveItem_Implementation(class UItem* item)
{
	RemoveItem(item);
}

void UInventory::StoreItem(class UItem* item, class UInventory* inventory)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		inventory->AddItem(item);
		RemoveItem(item);
	}
	else
	{
		ServerStoreItem(item, inventory);
	}
}

void UInventory::ServerStoreItem_Implementation(class UItem* item, class UInventory* inventory)
{
	StoreItem(item, inventory);
}

void UInventory::RetrieveItem(class UItem* item, class UInventory* inventory)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		AddItem(item);
		inventory->RemoveItem(item);
	}
	else
	{
		ServerRetrieveItem(item, inventory);
	}
}

void UInventory::ServerRetrieveItem_Implementation(class UItem* item, class UInventory* inventory)
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
