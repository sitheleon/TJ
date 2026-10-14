#include "BTT_OnlyChase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTT_OnlyChase::UBTT_OnlyChase()
{
    NodeName = TEXT("Only Chase with Delay");
}

EBTNodeResult::Type UBTT_OnlyChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UWorld* World = OwnerComp.GetWorld();
    if (!World) return EBTNodeResult::Failed;

    APawn* PlayerRef = UGameplayStatics::GetPlayerPawn(World, 0);
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!PlayerRef || !AIController) return EBTNodeResult::Failed;

    WeakAIController = AIController;
    WeakPlayerRef = PlayerRef;

    // 타이머 등록
    World->GetTimerManager().SetTimer(
        ChaseTimerHandle,
        FTimerDelegate::CreateUObject(this, &UBTT_OnlyChase::PerformChase, &OwnerComp),
        4.0f,
        false
    );

    return EBTNodeResult::InProgress;
}

void UBTT_OnlyChase::PerformChase(UBehaviorTreeComponent* OwnerComp)
{
    if (!WeakAIController.IsValid() || !WeakPlayerRef.IsValid())
    {
        FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FAIMoveRequest MoveRequest(WeakPlayerRef->GetActorLocation());
    MoveRequest.SetUsePathfinding(true);
    MoveRequest.SetAcceptanceRadius(AcceptableRadius);

    WeakAIController->MoveTo(MoveRequest);
    WeakAIController->SetFocus(WeakPlayerRef.Get());

    FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTT_OnlyChase::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (UWorld* World = OwnerComp.GetWorld())
    {
        World->GetTimerManager().ClearTimer(ChaseTimerHandle);
    }
    return EBTNodeResult::Aborted;
}

