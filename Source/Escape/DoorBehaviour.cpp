// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "DoorBehaviour.h"


// Sets default values for this component's properties
UDoorBehaviour::UDoorBehaviour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorBehaviour::BeginPlay()
{
	Super::BeginPlay();

	this->owner = GetOwner();
	this->TriggeringPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UDoorBehaviour::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (trigger->IsOverlappingActor(TriggeringPawn))
		OpenDoor(DeltaTime);
	else 
	{
		CloseDoor(DeltaTime);
	}
	
}

void UDoorBehaviour::OpenDoor(float DeltaTime)
{
	this->owner->SetActorRotation(FMath::RInterpTo(owner->GetActorRotation(), FRotator(0.0f, -maxAngle, 0.0f), DeltaTime, rotationSpeed));
		
}

void UDoorBehaviour::CloseDoor(float DeltaTime)
{
	this->owner->SetActorRotation(FMath::RInterpTo(owner->GetActorRotation(), FRotator(0.0f, 0.0f, 0.0f), DeltaTime, 3 * rotationSpeed));

}
