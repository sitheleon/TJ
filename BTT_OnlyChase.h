#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_OnlyChase.generated.h"

UCLASS()
class A_TONGJEON_API UBTT_OnlyChase : public UBTTaskNode
{
    GENERATED_BODY()
    
public:
    UBTT_OnlyChase();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    void PerformChase(UBehaviorTreeComponent* OwnerComp);

    FTimerHandle ChaseTimerHandle;
    TWeakObjectPtr<AAIController> WeakAIController;
    TWeakObjectPtr<APawn> WeakPlayerRef;

    float AcceptableRadius = 100.0f;
};
