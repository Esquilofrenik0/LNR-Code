#include "SkSpawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Armor.h"
#include "LNR/Body/Hero.h"

ASkSpawn::ASkSpawn()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
}

void ASkSpawn::BeginPlay()
{
	Super::BeginPlay();
}
