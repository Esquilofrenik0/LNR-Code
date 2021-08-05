// #include "Eos.h"
// #include "GLNR.h"
// #include "Engine/LocalPlayer.h"
// #include "Engine/NetConnection.h"
// #include "GameFramework/GameModeBase.h"
// #include "GameFramework/PlayerController.h"
// #include "Interfaces/OnlinePresenceInterface.h"
// #include "OnlineSubsystem.h"
// #include "OnlineSubsystemUtils.h"
// #include "Kismet/GameplayStatics.h"
// #include "LNR/LNR.h"
//
// void UEos::PostInitProperties()
// {
// 	Super::PostInitProperties();
// 	if (this->HasAnyFlags(RF_ClassDefaultObject)) return;
// 	check(this->GetWorld() != nullptr);
// 	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
// 	if (Subsystem != nullptr && Subsystem->GetSubsystemName() == FName(TEXT("RedpointEOS")))
// 	{
// 	    // Login();
// 	
// 	
// 		// IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
// 		// IOnlinePartyPtr Party = Subsystem->GetPartyInterface();
// 		// IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
// 		// IOnlinePresencePtr Presence = Subsystem->GetPresenceInterface();
//
// 		// Party->AddOnPartyInvitesChangedDelegate_Handle(
// 		// FOnPartyInvitesChangedDelegate::CreateUObject(this, &UExampleCPPSubsystem::OnPartyInvitesChanged));
// 		// Party->AddOnPartyDataReceivedDelegate_Handle(
// 		// FOnPartyDataReceivedDelegate::CreateUObject(this, &UExampleCPPSubsystem::OnPartyDataReceived));
// 		// Session->AddOnSessionUserInviteAcceptedDelegate_Handle(FOnSessionUserInviteAcceptedDelegate::CreateUObject(
// 		// this,
// 		// &UExampleCPPSubsystem::OnSessionUserInviteAccepted));
// 		// Session->AddOnJoinSessionCompleteDelegate_Handle(
// 		// FOnJoinSessionCompleteDelegate::CreateUObject(this, &UExampleCPPSubsystem::OnSessionJoinedViaOverlay));
// 		// Presence->AddOnPresenceReceivedDelegate_Handle(
// 		// FOnPresenceReceivedDelegate::CreateUObject(this, &UExampleCPPSubsystem::OnPresenceReceived));
// 	}
// }
//
// void UEos::HandleLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
//                                const FString& Error)
// {
// 	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
// 	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
// 	Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, this->LoginDelegateHandle);
// 	this->LoginDelegateHandle.Reset();
//
// 	Name = Identity->GetPlayerNickname(0);
// 	Print(Name + " Logged In!");
// }
//
// void UEos::Login()
// {
// 	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
// 	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
// 	this->LoginDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(
// 		0, FOnLoginComplete::FDelegate::CreateUObject(this, &UEos::HandleLoginComplete));
// 	if (!Identity->AutoLogin(0)) Print("Login Failed!");
// }
//
// void UEos::CreateSession()
// {
// 	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
// 	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
// 	this->CreateSessionDelegateHandle =
// 		Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionComplete::FDelegate::CreateUObject(
// 			this, &UEos::HandleCreateSessionComplete));
//
// 	TSharedRef<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();
// 	SessionSettings->NumPublicConnections = 4; // The number of players.
// 	SessionSettings->bShouldAdvertise = true;  // Set to true to make this session discoverable with FindSessions.
// 	SessionSettings->bUsesPresence = false;    // Set to true if you want this session to be discoverable by presence (Epic Social Overlay).
//
// 	SessionSettings->Settings.Add( FName(TEXT("SessionSetting")),
// 		FOnlineSessionSetting(FString(TEXT("SettingValue")), EOnlineDataAdvertisementType::ViaOnlineService));
// 	
// 	if (!Session->CreateSession(0, FName(TEXT("MyLocalSessionName")), *SessionSettings)) Print("Couldn't Create Session");
//
// 	Print("Session Created");
// }
//
//
// void UEos::HandleCreateSessionComplete(FName SessionName, bool bWasSuccessful)
// {
// 	IOnlineSubsystem *Subsystem = Online::GetSubsystem(this->GetWorld());
// 	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
// 	Session->ClearOnCreateSessionCompleteDelegate_Handle(this->CreateSessionDelegateHandle);
// 	this->CreateSessionDelegateHandle.Reset();
// 	AGLNR* GameMode = Cast<AGLNR>(UGameplayStatics::GetGameMode(GetWorld()));
// 	GameMode->RegisterExistingPlayers();
// }