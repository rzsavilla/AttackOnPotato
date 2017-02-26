// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AttackOnPotatoCharacter.generated.h"



UCLASS(Blueprintable)
class ATTACKONPOTATO_API AAttackOnPotatoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAttackOnPotatoCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** Sphere for collision when collecting */
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere;  }

	/** Collection Spheeeeerrreee*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collect", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;

	UFUNCTION(BlueprintCallable, Category = "Collect")
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///////Player STATS FUNCTIONS//////////
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void setHealth(int newHealth);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void addHealth(int health);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void setMaxHealth(int newMaxHealth);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void setSpeed(int newSpeed);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void setMaxSpeed(int newMaxSpeed);

	/**Start speed boost with new speed and add duration */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void boostSpeed(int newSpeed,float duration);

	//Weapons
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void addBomb(int iNum);
	void setMaxBomb(int iNum);

	//MULTIPLIERS
	//Player Regular speed/Minumum
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Multiplier", meta = (AllowPrivateAccess = "true"))
	bool bMultiplierTwo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Multiplier", meta = (AllowPrivateAccess = "true"))
	bool bMultiplierFive;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Multiplier", meta = (AllowPrivateAccess = "true"))
	bool bMultiplierTen;

	//Multiplier Setters
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void setTwoMultiplier(bool state);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void setFiveMultiplier(bool state);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void setThreeMultiplier(bool state);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void throwBomb();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Pickup Type"))
	void NotifyType(const FString& type);

protected:
	/** Collect any pickups inside collection sphere */
	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void CollectPickups();
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	////////Player STATS
	//Player Health when zero player dies
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	int iHealth;

	/** Player max health*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	int iMaxHealth;

	/** Player Current Move Speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	int iSpeed;

	/**Player Max Move Speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	int iMaxSpeed;

	/** Player Regular speed/Minumum*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	int iNormalSpeed;

	//EndSpeedBoost
	void endSpeedBoost();

	/**Player Regular speed/Minumum */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float fSpeedBoostDuration;

	//Power up timers
	FTimerHandle SpeedBoostTimer;

	//WEAPONS
	/** Current number of bombs*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	int iBombs;

	/** Maximum carriable bombs*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	int iMaxBombs;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class UThrownProjectile> ProjectileClass;
};
