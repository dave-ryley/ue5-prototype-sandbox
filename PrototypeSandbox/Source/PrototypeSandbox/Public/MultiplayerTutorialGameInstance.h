// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuInterface.h"
#include "MultiplayerTutorialGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API UMultiplayerTutorialGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();
	
	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

	UFUNCTION(Exec)
	virtual void Quit() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> InGameMenuClass;
private:
	class UMainMenu* Menu;
	class UInGameMenu* InGameMenu;
};
