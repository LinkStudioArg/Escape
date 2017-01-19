// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "GrabManager.h"


// Sets default values for this component's properties
UGrabManager::UGrabManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabManager::BeginPlay()
{
	Super::BeginPlay();

	myPlayerController = GetWorld()->GetFirstPlayerController();
	
}


// Called every frame
void UGrabManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector viewpointLocation;
	FRotator viewpointRotator;

	myPlayerController->GetPlayerViewPoint(viewpointLocation, viewpointRotator);

	//UE_LOG(LogTemp, Warning, TEXT("VP Location: %s, VP Rotator: %s"), *viewpointLocation.ToString(), * viewpointRotator.ToString());
	FVector viewpointRotToVector = viewpointRotator.Vector();
	viewpointRotToVector.Normalize();
	FVector viewpointRayEnd = viewpointLocation + viewpointRotToVector * reachingDistance * 100.0f;

	DrawDebugLine(GetWorld(), viewpointLocation, viewpointRayEnd, FColor(255, 0, 0), false, 0.0f, 0, .5f);

	FHitResult hit;

	GetWorld()->LineTraceSingleByObjectType(hit, viewpointLocation, viewpointRayEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));

	AActor * ActorHit = hit.GetActor();


	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(ActorHit->GetName()));
	}
	
	

}

