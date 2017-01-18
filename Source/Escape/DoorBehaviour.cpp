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
		
}


// Called every frame
void UDoorBehaviour::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	float speed = 1.5f;

	float angle = maxAngle * DeltaTime * speed;

	FRotator newRotation = FRotator(0.0f, -angle, 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *(owner->GetActorRotation().ToString()));

	if (owner->GetActorRotation().Yaw > -maxAngle && !doorOpened)
		this->owner->AddActorLocalRotation(newRotation);
	else
	{
		if (!doorOpened)
		{
			doorOpened = true;
			this->owner->SetActorRotation(FRotator(0.0f, -maxAngle, 0));
		}
	}
}

