#include "Container.h"
#include "LNR/Component/Inventory.h"

AContainer::AContainer()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	Container = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Container"));
	RootComponent = Container;
	Inventory = CreateDefaultSubobject<UInventory>("Inventory");
}

void AContainer::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
}

FString AContainer::PrintContainerData()
{
	FString data = "Container\r";
	data += "Slots: " + FString::FromInt(Inventory->nSlots) + "\r";
	return data;
}
