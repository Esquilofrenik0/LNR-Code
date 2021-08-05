// #include "GLNR.h"
// #include "OnlineSubsystem.h"
// #include "OnlineSubsystemUtils.h"
// #include "LNR/LNR.h"
//
// void AGLNR::PostLogin(APlayerController* InPlayerController)
// {
// 	if (!this->bAllExistingPlayersRegistered)
// 	{
// 		Super::PostLogin(InPlayerController);
// 		return;
// 	}
//
// 	check(IsValid(InPlayerController));
//
// 	FUniqueNetIdRepl UniqueNetIdRepl;
// 	if (InPlayerController->IsLocalPlayerController())
// 	{
// 		ULocalPlayer *LocalPlayer = InPlayerController->GetLocalPlayer();
// 		if (IsValid(LocalPlayer))
// 		{
// 			UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
// 		}
// 		else
// 		{
// 			UNetConnection *RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
// 			check(IsValid(RemoteNetConnection));
// 			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
// 		}
// 	}
// 	else
// 	{
// 		UNetConnection *RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
// 		check(IsValid(RemoteNetConnection));
// 		UniqueNetIdRepl = RemoteNetConnection->PlayerId;
// 	}
//
// 	TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
// 	check(UniqueNetId != nullptr);
//
// 	IOnlineSubsystem *Subsystem = Online::GetSubsystem(InPlayerController->GetWorld());
// 	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
//
// 	if (!Session->RegisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId, false))
// 	{
// 		Print("Couldn't Register Player");
// 		// The player could not be registered; typically you will want to kick the player from the server in this situation.
// 	}
//
// 	Super::PostLogin(InPlayerController);
// }
//
// void AGLNR::RegisterExistingPlayers()
// {
// 	for (auto It = this->GetWorld()->GetPlayerControllerIterator(); It; --It)
// 	{
// 		APlayerController* PlayerController = It->Get();
//         
// 		FUniqueNetIdRepl UniqueNetIdRepl;
// 		if (PlayerController->IsLocalPlayerController())
// 		{
// 			ULocalPlayer *LocalPlayer = PlayerController->GetLocalPlayer();
// 			if (IsValid(LocalPlayer))
// 			{
// 				UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
// 			}
// 			else
// 			{
// 				UNetConnection *RemoteNetConnection = Cast<UNetConnection>(PlayerController->Player);
// 				check(IsValid(RemoteNetConnection));
// 				UniqueNetIdRepl = RemoteNetConnection->PlayerId;
// 			}
// 		}
// 		else
// 		{
// 			UNetConnection *RemoteNetConnection = Cast<UNetConnection>(PlayerController->Player);
// 			check(IsValid(RemoteNetConnection));
// 			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
// 		}
//
// 		TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
// 		check(UniqueNetId != nullptr);
//
// 		IOnlineSubsystem *Subsystem = Online::GetSubsystem(PlayerController->GetWorld());
// 		IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
//
// 		if (!Session->RegisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId, false))
// 		{
// 			Print("Player Could not be Registered");
// 			// The player could not be registered; typically you will want to kick the player from the server in this situation.
// 		}
// 	}
// 	this->bAllExistingPlayersRegistered = true;
// }
//
// void AGLNR::PreLogout(APlayerController *InPlayerController)
// {
// 	check(IsValid(InPlayerController));
//
// 	// This code handles logins for both the local player (listen server) and remote players (net connection).
// 	FUniqueNetIdRepl UniqueNetIdRepl;
// 	if (InPlayerController->IsLocalPlayerController())
// 	{
// 		ULocalPlayer *LocalPlayer = InPlayerController->GetLocalPlayer();
// 		if (IsValid(LocalPlayer))
// 		{
// 			UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
// 		}
// 		else
// 		{
// 			UNetConnection *RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
// 			check(IsValid(RemoteNetConnection));
// 			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
// 		}
// 	}
// 	else
// 	{
// 		UNetConnection *RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
// 		check(IsValid(RemoteNetConnection));
// 		UniqueNetIdRepl = RemoteNetConnection->PlayerId;
// 	}
//
// 	// Get the unique player ID.
// 	TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
// 	check(UniqueNetId != nullptr);
//
// 	// Get the online session interface.
// 	IOnlineSubsystem *Subsystem = Online::GetSubsystem(InPlayerController->GetWorld());
// 	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
//
// 	// Unregister the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
// 	if (!Session->UnregisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId))
// 	{
// 		// The player could not be unregistered.
// 	}
// }