// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* NewMenuInterface)
{
	MenuInterface = NewMenuInterface;
}

void UMenuWidget::Setup()
{
	AddToViewport();
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	
	FInputModeUIOnly Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Mode.SetWidgetToFocus(TakeWidget());

	PlayerController->SetInputMode(Mode);
	PlayerController->SetShowMouseCursor(true);
}

void UMenuWidget::TearDown()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeGameOnly Mode;
	Mode.SetConsumeCaptureMouseDown(true);

	PlayerController->SetInputMode(Mode);
	PlayerController->SetShowMouseCursor(false);
	RemoveFromViewport();
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	TearDown();
}
