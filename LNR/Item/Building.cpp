#include "Building.h"
#include "Net/UnrealNetwork.h"

void ABuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABuilding, Item);
}

void ABuilding::SetItem(class UItem* nItem)
{
	if (HasAuthority()) Item = nItem;
	else ServerSetItem(nItem);
}

void ABuilding::ServerSetItem_Implementation(class UItem* nItem)
{
	SetItem(nItem);
}

void ABuilding::DestroyItem()
{
	if (HasAuthority()) MultiDestroyItem();
	else ServerDestroyItem();
}

void ABuilding::ServerDestroyItem_Implementation()
{
	DestroyItem();
}

void ABuilding::MultiDestroyItem_Implementation()
{
	Destroy();
}
