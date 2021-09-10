// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"

#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* MenuInterface);
	virtual void Setup();
	virtual void TearDown();

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
protected:
	IMenuInterface* MenuInterface;
};
