// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BadPotato.h"
#include "PotatoAIController.generated.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UENUM()
enum class EBotBehaviorType : uint8
{
	/* Does not move, remains in place until a player is spotted */
	Passive,

	/* Patrols a region until a player is spotted */
	Patrolling,
};
/**
 * 
 */
UCLASS()
class ATTACKONPOTATO_API APotatoAIController : public AAIController
{
	GENERATED_BODY()

		APotatoAIController(const class FObjectInitializer& ObjectInitializer);

	/* called whenever the controller possesses a character bot */
	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;

	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(Category = "AI", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), EditDefaultsOnly)
	FName TargetEnemyKeyName;

	//UPROPERTY(Category = Ai, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), EditDefaultsOnly)
	//FName CurrentWaypointKeyName;

	UPROPERTY(Category = "AI", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), EditDefaultsOnly)
	FName BotTypeKeyName;

public:

	// TODO Create way points class 
	//APotatoWayPoint* GetWaypoint();

	// place holder till we get the actual character class 
	ABaseCharacter* GetTargetEnemy(); 

	//void SetWaypoint(APotatoWaypoint * NewWayPoint);

	void SetTargetEnemy(APawn* NewTarget);

	void SetBlackboardBotType(EBotBehaviorType newType);

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp };

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp };


};
