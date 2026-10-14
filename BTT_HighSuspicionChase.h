// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_HighSuspicionChase.generated.h"

UCLASS()
class A_TONGJEON_API UBTT_HighSuspicionChase : public UBTTaskNode
{
    GENERATED_BODY()
    
public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
