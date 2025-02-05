// MINE
#include "Grabber.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay(){
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PhysicsHandle->GrabbedComponent){
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

void UGrabber::Grab(){
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	if(HitResult.GetActor()){
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			GetLineTraceEnd()
		);
	}
}

void UGrabber::Release(){
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle(){
	//Check PhysicsHandleComponent
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle){
		
	}else{
		UE_LOG(LogTemp, Error, TEXT("%s has no PhysicsHandle component"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent(){
		//check input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent){
		UE_LOG(LogTemp, Warning, TEXT("%s has InputComponent component"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach(){
	FVector PlayerViewPointLocation;

	FHitResult Hit;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

FVector UGrabber::GetLineTraceEnd() const{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetPlayersWorldPos() const{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}