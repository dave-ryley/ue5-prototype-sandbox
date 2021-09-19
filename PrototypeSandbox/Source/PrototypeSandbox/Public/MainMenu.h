// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ServerRow.h>

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	void SetServerList(const TArray<struct FServerData>& ServerData);

	UFUNCTION(BlueprintCallable)
	FString GetHostServerName() const;
protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void OpenJoinMenu();
	
	UFUNCTION()
	void CloseSubMenu();

	UFUNCTION()
	void QuitGame();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* HostMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostBackButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinBackButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* ServerNameEditableText;
	
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;
	
	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerListBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UServerRow> ServerRowClass;

	UServerRow* CurrentlySelectedRow;
};
