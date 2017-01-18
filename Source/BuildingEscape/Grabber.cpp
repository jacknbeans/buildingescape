// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get player viewpoint this tick
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);

	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * _Reach;
	/// Draw a red trace in the world to visualize
	DrawDebugLine(
		GetWorld(),
		playerViewPointLocation,
		lineTraceEnd,
		FColor().Magenta,
		false,
		0.f,
		0,
		10.f
	);

	/// Setup query parameters
	auto collisionQueryParms = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	/// Line-trace (aka Ray-cast) out to reach distance
	FHitResult lineTraceHit;
	if (GetWorld()->LineTraceSingleByObjectType(
		OUT lineTraceHit,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		collisionQueryParms
	)) {
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *lineTraceHit.GetActor()->GetName())
	}
}

