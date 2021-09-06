// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();
	~AMovingPlatform();
	void Tick(float DeltaSeconds) override;
	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 20;

	UPROPERTY(EditAnywhere, Meta=(MakeEditWidget=true))
	FVector TargetLocation;

	void Activate(class APlatformTrigger& Trigger);
	void Deactivate(class APlatformTrigger& Trigger);
private:
	void CalculateDirection();

	FVector StartLocation;
	FVector TargetLocationWorld;
	
	FVector CurrentStart;
	FVector CurrentTarget;

	float Distance;
	bool bIsActive = false;
};
