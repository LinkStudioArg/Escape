// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorBehaviour.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UDoorBehaviour : public UActorComponent
{
	GENERATED_BODY()
private:
	bool doorOpened = false;
	AActor *owner;
	UPROPERTY(EditAnywhere)
	ATriggerVolume *trigger;

	UPROPERTY(EditAnywhere)
		APawn *TriggeringPawn;
public:	
	
	UPROPERTY(EditAnywhere)
	float maxAngle = 120.0f;
	// Sets default values for this component's properties
	UDoorBehaviour();	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OpenDoor(float DeltaTime);
	
};
