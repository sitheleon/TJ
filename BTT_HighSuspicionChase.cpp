// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_HighSuspicionChase.h"
#include "Mannequin.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_HighSuspicionChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    static bool bHasChased = false;
    if (bHasChased)
    {
        return EBTNodeResult::Succeeded;
    }

    UWorld* World = OwnerComp.GetWorld();
    if (!World) 
    {
        return EBTNodeResult::Failed;
    }

    TArray<AActor*> Mannequins;
    UGameplayStatics::GetAllActorsOfClass(World, AMannequin::StaticClass(), Mannequins);

    if (Mannequins.Num() == 0) return EBTNodeResult::Failed;

    // 랜덤 마네킨 선택
    int32 Index = FMath::RandRange(0, Mannequins.Num() - 1);
    AActor* TargetMannequin = Mannequins[Index];

    // AIController 가져오기
    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon) 
    {
        return EBTNodeResult::Failed;
    }

    // MoveTo 명령
    AICon->MoveToLocation(TargetMannequin->GetActorLocation());
    UE_LOG(LogTemp, Warning, TEXT("Chasing Mannequin: %s"), *TargetMannequin->GetName());

    bHasChased = true;
    return EBTNodeResult::Succeeded;
}

