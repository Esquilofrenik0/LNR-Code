#include "Spawn.h"
#include "Net/UnrealNetwork.h"

ASpawn::ASpawn()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ASpawn::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
}

void ASpawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASpawn, Item);
}

void ASpawn::SetItem(class UItem* nItem)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		Item = nItem;
	}
	else
	{
		ServerSetItem(nItem);
	}
}

void ASpawn::ServerSetItem_Implementation(class UItem* nItem)
{
	SetItem(nItem);
}

void ASpawn::DestroyItem()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		MultiDestroyItem();
	}
	else
	{
		ServerDestroyItem();
	}
}

void ASpawn::ServerDestroyItem_Implementation()
{
	DestroyItem();
}

void ASpawn::MultiDestroyItem_Implementation()
{
	Destroy();
}
