// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Chase.generated.h"

/**
 * 
 */
UCLASS()
class A_TONGJEON_API UBTT_Chase : public UBTTaskNode
{
	GENERATED_BODY()
	
public: 

	UPROPERTY(EditAnywhere)
	float AcceptableRadius = 100.0f;

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;


	virtual void TickTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds
	) override;

};
