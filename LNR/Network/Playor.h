#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Playor.generated.h"

UCLASS()
class LNR_API APlayor : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	
	virtual void OnPossess(APawn* InPawn) override;
	// virtual void OnNetCleanup(UNetConnection* Connection) override;

	UFUNCTION(Server, Reliable)
	void Respawn();
};
