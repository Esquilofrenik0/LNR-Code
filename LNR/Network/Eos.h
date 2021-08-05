// #pragma once
// #include "CoreMinimal.h"
// #include "OnlineSubsystem.h"
// #include "Subsystems/GameInstanceSubsystem.h"
// #include "Eos.generated.h"
//
// UCLASS(BlueprintType)
// class LNR_API UEos : public UGameInstanceSubsystem
// {
// 	GENERATED_BODY()
// public:	
// 	UPROPERTY(BlueprintReadWrite) FString Name;
// 	FDelegateHandle LoginDelegateHandle;
// 	FDelegateHandle CreateSessionDelegateHandle;
// 	
// 	virtual void PostInitProperties() override;
// 	void HandleLoginComplete(int32 LocalUserNum,bool bWasSuccessful,const FUniqueNetId &UserId,const FString &Error);
// 	void HandleCreateSessionComplete(FName SessionName, bool bWasSuccessful);
// 	
// 	UFUNCTION(BlueprintCallable) void Login();
// 	UFUNCTION(BlueprintCallable) void CreateSession();
// };
