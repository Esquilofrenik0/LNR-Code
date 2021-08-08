#pragma once
#include "CoreMinimal.h"
#include "Spawn.h"
#include "SkSpawn.generated.h"

UCLASS()
class LNR_API ASkSpawn : public ASpawn
{
	GENERATED_BODY()
public:
	ASkSpawn();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;
	virtual void BeginPlay() override;
};
