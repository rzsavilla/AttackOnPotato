// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PotatoAIController.h"
#include "BadPotato.generated.h"

/* AI Include */
#include "Perception/PawnSensingComponent.h"

UCLASS()
class ATTACKONPOTATO_API ABadPotato : public ACharacter
{
	GENERATED_BODY()

	// Last time the player was spotted
	float LastSeenTime;

	// last time we attacked something
	float LastMeleeAttackTime;

	// time out value to clear the snsed position of the player. Should be higher than Sense interval in the PawnSense component not never miss sense ticks.
	UPROPERTY(EditDefaultsOnly, Category = "AI", VisibleAnywhere, BlueprintReadOnly)
	float SenseTimeOut;
	
	// Resets after sense time-out to avoid unnecessary clearing of the target each tick
	bool bSensedTarget;

	UPROPERTY(VisibleAnywhere, Category = "AI", BlueprintReadOnly, EditDefautsOnly)
	class UPawnSensingComponent* PawnSensingComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual bool IsSprinting() const override;

	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

	//UPROPERTY(VisibleAnywhere, Category = "Attacking", BlueprintReadOnly)
	//UCapsuleComponent* MeleeCollisionComp;

	/* A PAWN IS IN MELEE RANGE
	UFUNCTION()
	void OnMeleeCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, 
									class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void OnRetriggerMeleeStrike();

	//Deal damage to the actor that was hit by the animation
	UFUNCTION(BlueprintCallable, Category = "Attacking")
		void PerformMeleeStrike(AActor* HitActor);

	UFUNCTION(Reliable, NetMulticast)
		void SimulateMeleeStrike();

	void SimulateMeleeStrike_Implementation();

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
		TSubclassOf<UDamageType> PunchDamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
		float MeleeDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
		UAnimMontage* MeleeAnimMontage;

	/* Timer handle to manage continous melee attacks while in range of a player 
	FTimerHandle TimerHandle_MeleeAttack;

	/* Minimum time between melee attacks 
	float MeleeStrikeCooldown;

	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser, bool bKilled) override;*/

public:

	// Sets default values for this character's properties
	ABadPotato(const class FObjectInitialize& ObjectInitializer);

	//UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//bool isPunching;

	/* The bot behavior we want this bot to execute, (passive/patrol) by specifying EditAnywhere we can edit this value per-instance when placed on the map. */
	UPROPERTY(EditAnywhere, Category = "AI")
	EBotBehaviorType BotType;

	// the brain, we make decisions based on the data we feed it form the blackboard
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	void SetBotType(EBotBehaviorType NewType);
	
};
