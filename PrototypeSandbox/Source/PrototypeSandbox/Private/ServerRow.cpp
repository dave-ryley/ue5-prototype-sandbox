// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

FServerData::FServerData()
	:	Name(FString(TEXT("Unknown"))),
		CurrentPlayers(0),
		MaxPlayers(0),
		HostUserName(TEXT("Unknown"))
{
}

FServerData::FServerData(const FOnlineSessionSearchResult* Result)
	:	Name(Result->GetSessionIdStr()),
		MaxPlayers(Result->Session.SessionSettings.NumPublicConnections),
		CurrentPlayers(MaxPlayers - Result->Session.NumOpenPublicConnections),
		HostUserName(Result->Session.OwningUserName)
{
}

bool UServerRow::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!ensure(ServerNameText != nullptr)) return false;
	if (!ensure(RowButton != nullptr)) return false;

	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
	return true;
}

void UServerRow::SetIsSelected(const bool IsSelected)
{
	bIsSelected = IsSelected;
}

bool UServerRow::IsRowSelected() const
{
	return bIsSelected;
}

void UServerRow::Setup(const FOnlineSessionSearchResult* Result)
{
	if (!ensure(Result != nullptr)) return;

	SessionResult = Result;
	ServerData = FServerData(Result);
	ServerNameText->SetText(FText::FromString(ServerData.Name));
	ServerOwnerText->SetText(FText::FromString(ServerData.HostUserName));
	FString ParticipantsText = ServerData.CurrentPlayers + TEXT("/") + ServerData.MaxPlayers;
	ServerParticipantsText->SetText(FText::FromString(MoveTemp(ParticipantsText)));
}

const FOnlineSessionSearchResult* UServerRow::GetSearchResult() const
{
	return SessionResult;
}

void UServerRow::SetOnClickedCallback(const FCallbackFunc Callback)
{
	OnClickCallback = Callback;
}

void UServerRow::OnClicked()
{
	if (OnClickCallback.IsSet() && SessionResult != nullptr)
	{
		const auto& Callback = OnClickCallback.GetValue();
		Callback(this);
	}
}
