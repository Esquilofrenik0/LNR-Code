#include "SkSpawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Armor.h"
#include "Weapon.h"
#include "LNR/Body/Hero.h"
#include "Net/UnrealNetwork.h"

// void ASkSpawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
	// Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// DOREPLIFETIME_CONDITION_NOTIFY(ASkSpawn, SkeletalMesh, COND_None, REPNOTIFY_Always);
// }

ASkSpawn::ASkSpawn()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
}

void ASkSpawn::BeginPlay()
{
	Super::BeginPlay();
}

// void ASkSpawn::OnRep_SkeletalMesh(USkeletalMeshComponent* oldSkeletalMesh)
// {
	// oldSkeletalMesh = SkeletalMesh;
// }
