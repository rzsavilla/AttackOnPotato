// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class ATTACKONPOTATO_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called every frame NEVER CALLED
	virtual void Tick(float DeltaTime) override;

	/**Returns whether pickup is active */
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	/** Allow Other classes to set pickup state*/
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool PickUpState);


	/** Function called when pickup is collected*/
	UFUNCTION(BlueprintNativeEvent)
	void Collect();
	virtual void Collect_Implementation();

	/** Returns pointer to pickup mesh*/
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** True when pickup can be used*/
	bool bIsActive;
private:
	
	/** Mesh for the pickup */
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;
};
