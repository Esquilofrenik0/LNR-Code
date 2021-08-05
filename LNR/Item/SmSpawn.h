#pragma once
#include "CoreMinimal.h"
#include "Spawn.h"
#include "SmSpawn.generated.h"

UCLASS()
class LNR_API ASmSpawn : public ASpawn
{
	GENERATED_BODY()
public:
	ASmSpawn();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;
};
