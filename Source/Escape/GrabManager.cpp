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
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!physicsHandle) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s: UPhysicsHandleComponent missing!"), *(GetOwner()->GetName()));
	}
	if (!input)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: UInputComponent missing!"), *(GetOwner()->GetName()));
	}
	else 
	{
		input->BindAction("Interact", IE_Pressed, this, &UGrabManager::Grab);
		input->BindAction("Interact", IE_Released, this, &UGrabManager::Release);
	}
	
}

// Called every frame
void UGrabManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (physicsHandle->GrabbedComponent) 
	{
		physicsHandle->SetTargetLocation(GetViewpointEnd());
	}
}
FVector UGrabManager::GetViewpointStart()
{
	FVector viewpointLocation;

	FRotator viewpointRotator;

	myPlayerController->GetPlayerViewPoint(viewpointLocation, viewpointRotator);

	return viewpointLocation;
}

FVector UGrabManager::GetViewpointEnd() 
{
	FVector viewpointLocation;

	FRotator viewpointRotator;

	myPlayerController->GetPlayerViewPoint(viewpointLocation, viewpointRotator);

	//UE_LOG(LogTemp, Warning, TEXT("VP Location: %s, VP Rotator: %s"), *viewpointLocation.ToString(), * viewpointRotator.ToString());
	FVector viewpointRotToVector = viewpointRotator.Vector();

	viewpointRotToVector.Normalize();

	FVector viewpointRayEnd = viewpointLocation + viewpointRotToVector * reachingDistance * 100.0f;

	return viewpointRayEnd;
}

void UGrabManager::Grab() 
{
	//UE_LOG(LogTemp, Warning, TEXT("Grabbing"));

	auto hitResult = GetFirstPhysicsBodyInReach();

	auto ComponentToGrab = hitResult.GetComponent();

	auto actorHit = hitResult.GetActor();

	if (actorHit)
	{
		physicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation() + ComponentToGrab->GetOwner()->GetActorUpVector() * 50.0f, true);
	}
}

void UGrabManager::Release() 
{
	//UE_LOG(LogTemp, Warning, TEXT("Releasing"));

	physicsHandle->ReleaseComponent();
}

const FHitResult UGrabManager::GetFirstPhysicsBodyInReach()
{
	
	FVector viewpointRayStart = GetViewpointStart();

	FVector viewpointRayEnd = GetViewpointEnd();

	//DrawDebugLine(GetWorld(), viewpointLocation, viewpointRayEnd, FColor(255, 0, 0), false, 0.0f, 0, .5f);

	FHitResult hit;

	GetWorld()->LineTraceSingleByObjectType(hit, viewpointRayStart, viewpointRayEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));

	return hit;

}
