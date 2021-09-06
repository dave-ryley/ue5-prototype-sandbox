// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "PlatformTrigger.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	auto staticMesh = GetStaticMeshComponent();
	staticMesh->SetMobility(EComponentMobility::Movable);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	staticMesh->SetStaticMesh(cubeMesh.Object);
	staticMesh->SetRelativeScale3D(FVector{ 1.0f, 1.0f, 0.2f });
}

AMovingPlatform::~AMovingPlatform()
{
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority() && bIsActive)
	{
		CalculateDirection();
		auto location = GetActorLocation();
		auto direction = (CurrentTarget - CurrentStart).GetSafeNormal();
		location += MoveSpeed * DeltaSeconds * direction;
		SetActorLocation(location);
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartLocation = GetActorLocation();
	TargetLocationWorld = GetTransform().TransformPosition(TargetLocation);
	CurrentStart = StartLocation;
	CurrentTarget = TargetLocationWorld;

	Distance = (CurrentTarget - CurrentStart).Size();
}

void AMovingPlatform::Activate(APlatformTrigger& Trigger)
{
	UE_LOG(LogTemp, Warning, TEXT("Enabled by %s"), *Trigger.GetName());
	bIsActive = true;
}

void AMovingPlatform::Deactivate(APlatformTrigger& Trigger)
{
	UE_LOG(LogTemp, Warning, TEXT("Disabled by %s"), *Trigger.GetName());
	bIsActive = false;
}

void AMovingPlatform::CalculateDirection()
{
	auto currentLocation = GetActorLocation();
	if ((currentLocation - CurrentStart).Size() > Distance)
	{
		FVector swap = CurrentStart;
		CurrentStart = CurrentTarget;
		CurrentTarget = swap;
	}
}