// MINE

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OpenDoor(float DeltaTime, float DirectionYaw, float DoorSpeed);

	float TotalMassOfActors() const;

	

		
private:

	float InitialYaw;
	float CurrentYaw;
	
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurPlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float CloseSpeed = 2.f;

	float DoorSpeed = 0.f;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoors = 60.f;

};