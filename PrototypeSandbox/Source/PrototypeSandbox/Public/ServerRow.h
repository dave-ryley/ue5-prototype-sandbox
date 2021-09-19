// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ServerRow.generated.h"

class FOnlineSessionSearchResult;

USTRUCT()
struct FServerData
{
    GENERATED_BODY()

	FServerData();
	explicit FServerData(const FOnlineSessionSearchResult* Result);

	FString Name;
	uint16 MaxPlayers;
    uint16 CurrentPlayers;
    FString HostUserName;
private:
	const class FOnlineSessionSearchResult* SourceResult;

	friend class UServerRow;
};
/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API UServerRow : public UUserWidget
{
	using FCallbackFunc = std::function<void(UServerRow*)>;
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
public:
	void SetIsSelected(bool IsSelected);

	UFUNCTION(BlueprintGetter)
	bool IsRowSelected() const;
	void Setup(const FServerData& Data);
	void Setup(FServerData&& Data);

	const FOnlineSessionSearchResult* GetSearchResult() const;
	void SetOnClickedCallback(FCallbackFunc Callback);
private:
	void UpdateText();
	
	UPROPERTY(BlueprintGetter=IsRowSelected)
	bool bIsSelected;
	
	UFUNCTION()
	void OnClicked();
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerOwnerText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerParticipantsText;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;
	
	FServerData ServerData;
	TOptional<FCallbackFunc> OnClickCallback;
};
