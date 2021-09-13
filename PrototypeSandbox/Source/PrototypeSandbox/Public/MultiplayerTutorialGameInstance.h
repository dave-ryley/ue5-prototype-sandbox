// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuInterface.h"
#include "OnlineSubsystem.h"
#include "MultiplayerTutorialGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API UMultiplayerTutorialGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	virtual void FindSessions() override;
	
	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();
	
	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

	UFUNCTION(Exec)
	virtual void QuitGame() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> InGameMenuClass;
private:
	IOnlineSessionPtr SessionInterface;
	
	void OnSessionCreated(FName SessionName, bool IsSuccessful);
	void OnSessionDestroyed(FName SessionName, bool IsSuccessful);
	void OnFindSessionsComplete(bool IsSuccessful);

	class UMainMenu* Menu;
	class UInGameMenu* InGameMenu;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};
