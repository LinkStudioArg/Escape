// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GrabManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabManager : public UActorComponent
{
	GENERATED_BODY()
private:
	APlayerController * myPlayerController;
	UPROPERTY(EditAnywhere)
	float reachingDistance = 5.0f;
public:	
	// Sets default values for this component's properties
	UGrabManager();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
