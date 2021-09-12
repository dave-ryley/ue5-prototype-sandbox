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
	void SetServerName(const FText NewServerName);
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerNameText;
};
