// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

	UFUNCTION()
	void Continue();

	UFUNCTION()
	void Quit();

	UPROPERTY(meta = (BindWidget))
	class UButton* ContinueButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
};
