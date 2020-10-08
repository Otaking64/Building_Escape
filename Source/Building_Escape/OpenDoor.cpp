// MINE


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
	if(!PressurPlate){
		UE_LOG(LogTemp, Error, TEXT("%s has the opendoor componen but no pressureplate is set"), *GetOwner()->GetName());

	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();


	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PressurPlate && PressurPlate->IsOverlappingActor(ActorThatOpens)){
		DoorSpeed = DeltaTime*OpenSpeed;
		OpenDoor(DeltaTime, TargetYaw, DoorSpeed);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}else{
		if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay){
			DoorSpeed = DeltaTime*CloseSpeed;
			OpenDoor(DeltaTime, InitialYaw, DoorSpeed);
		}	
	}
}

void UOpenDoor::OpenDoor(float DeltaTime, float TargetYaw, float DoorSpeed){

	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DoorSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

}

