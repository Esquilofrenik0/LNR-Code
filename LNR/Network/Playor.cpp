#include "Playor.h"
#include "GLNR.h"
#include "LNR/LNR.h"
#include "GameFramework/PlayerState.h"
#include "LNR/Body/Hero.h"
#include "GameFramework/GameModeBase.h"

void APlayor::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Hero = Cast<AHero>(InPawn);
	Print(PlayerState->GetPlayerName() + " joined session.");
}

void APlayor::Respawn_Implementation()
{
	Hero->Destroy();
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}
//
// void APlayor::OnNetCleanup(UNetConnection *Connection)
// {
// 	if (GetLocalRole() == ROLE_Authority && PlayerState != NULL)
// 	{
// 		AGLNR* GameMode = Cast<AGLNR>(GetWorld()->GetAuthGameMode());
// 		if (GameMode)
// 		{
// 			GameMode->PreLogout(this);
// 		}
// 	}
// 	Super::OnNetCleanup(Connection);
// }