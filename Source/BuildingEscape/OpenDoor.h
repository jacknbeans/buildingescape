// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, 
								FActorComponentTickFunction* ThisTickFunction ) override;

	void OpenDoor();
	void CloseDoor();

private:
	UPROPERTY(EditAnywhere)
	float _OpenAngle = -90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* _PressurePlate;

	UPROPERTY(EditAnywhere)
	float _DoorCloseDelay = 1.f;

	float _LastDoorOpenTime;

	AActor* _ActorThatOpens;

	AActor* _Owner;
};
