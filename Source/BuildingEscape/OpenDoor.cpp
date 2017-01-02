// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	_ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	_Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, 
							   FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger volume every frame
	// If the actor that opens is in the volume
	if (_PressurePlate->IsOverlappingActor(_ActorThatOpens)) {
		OpenDoor();
		_LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() >= _LastDoorOpenTime + _DoorCloseDelay) {
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	_Owner->SetActorRotation(FRotator(0.f, _OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	_Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}
