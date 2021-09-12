// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "Components/TextBlock.h"

bool UServerRow::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!ensure(ServerNameText != nullptr)) return false;

	return true;
}

void UServerRow::SetServerName(const FText NewServerName)
{
	if (!ensure(ServerNameText != nullptr)) return;

	ServerNameText->SetText(NewServerName);
}
