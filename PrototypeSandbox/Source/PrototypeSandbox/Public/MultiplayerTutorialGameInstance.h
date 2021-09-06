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

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MenuClass;

private:
	class UMainMenu* Menu;
};
