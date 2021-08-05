#include "SmSpawn.h"

ASmSpawn::ASmSpawn() {
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}