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

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Pickup")
	FString sType;

	/** Returns sType*/
	FORCEINLINE class FString GetSType() const { return sType; }

	///** Notify blueprint this type pickup has been collected*/
	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Pickup Type"))
	//FString NotifyType();
	//virtual FString NotifyType_Implementation();

	/* UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Pickup Type"))
	void NotifyType(FString& type);


	FString& getType() { return sType;  } */

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** True when pickup can be used*/
	bool bIsActive;

	float fZPos;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "PickupFloating", meta = (AllowPrivateAccess = "true"))
		float fFloatHeight;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "PickupFloating", meta = (AllowPrivateAccess = "true"))
		float fFloatSpeed;
private:
	
	float fCurrHeight;
	bool bUp;

	/** Mesh for the pickup */
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;
};
