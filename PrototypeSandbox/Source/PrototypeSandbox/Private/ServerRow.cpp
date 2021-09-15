// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UServerRow::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!ensure(ServerNameText != nullptr)) return false;
	if (!ensure(RowButton != nullptr)) return false;

	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
	return true;
}

void UServerRow::Setup(FOnlineSessionSearchResult const* Result)
{
	SessionResult = Result;
	ServerNameText->SetText(FText::FromString(SessionResult->GetSessionIdStr()));
}

void UServerRow::SetOnClickedCallback(const std::function<void(const FOnlineSessionSearchResult&)> Callback)
{
	OnClickCallback = Callback;
}

void UServerRow::OnClicked()
{
	if (OnClickCallback.IsSet() && SessionResult != nullptr)
	{
		const auto& Callback = OnClickCallback.GetValue();
		Callback(*SessionResult);
	}
}
