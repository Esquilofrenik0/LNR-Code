#pragma once

#include "CoreMinimal.h"
#include "Container.h"
#include "Chest.generated.h"

UCLASS()
class LNR_API AChest : public AContainer
{
	GENERATED_BODY()
public:
	AChest();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Lid;
};
