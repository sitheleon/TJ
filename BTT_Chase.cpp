// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Chase.h"
#include "AIController.h"
#include "EnemyCharacter.h"


EBTNodeResult::Type UBTT_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory)
{
    UE_LOG(LogTemp, Warning, TEXT("Chase"));

    APawn* PlayerRef = GetWorld()->GetFirstPlayerController()->GetPawn();

    FVector PlayerLocation = PlayerRef->GetActorLocation();

    FAIMoveRequest MoveRequest(PlayerLocation);
    MoveRequest.SetUsePathfinding(true);
    MoveRequest.SetAcceptanceRadius(AcceptableRadius);

    AAIController* AIController = OwnerComp.GetAIOwner();

    AIController->MoveTo(MoveRequest);
    AIController->SetFocus(PlayerRef);


    return EBTNodeResult::InProgress;
}

void UBTT_Chase::TickTask(UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory,
        float DeltaSeconds)
{    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        APawn* ControlledPawn = AIController->GetPawn();
        if (ControlledPawn)
        {
            // ControlledPawn을 AEnemyCharacter로 캐스팅
            AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(ControlledPawn);
            if (EnemyCharacter)
            {
                
                if (EnemyCharacter->SuspicionLevel >= 0.0f)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Chase!"));
                    // 추가적인 동작 수행
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("NO SOUND"));
                }
            }
        }
    }
}
