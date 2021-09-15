// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
public:
	void Setup(FOnlineSessionSearchResult const * Result);
	void SetOnClickedCallback(std::function<void(const class FOnlineSessionSearchResult& )> Callback);
private:

	UFUNCTION()
	void OnClicked();
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerNameText;

	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;
	
	class FOnlineSessionSearchResult const * SessionResult;
	TOptional<std::function<void(const FOnlineSessionSearchResult&)>> OnClickCallback; 
};
