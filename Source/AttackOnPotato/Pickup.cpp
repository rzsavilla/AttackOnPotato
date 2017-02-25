// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create static mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));

	//Set Pickup mesh as the root component
	RootComponent = PickupMesh;


	bIsActive = true;	//Default pickup is active
}

FString APickup::NotifyType_Implementation()
{
	return sType;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Return pickup state
bool APickup::IsActive()
{
	return bIsActive;
}

//Set PickUpState
void APickup::SetActive(bool PickUpState)
{
	bIsActive = PickUpState;
}

void APickup::Collect_Implementation()
{
	bIsActive = true;
	//Log debug message
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);
}