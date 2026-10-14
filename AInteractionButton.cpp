// Fill out your copyright notice in the Description page of Project Settings.


#include "AInteractionButton.h"

// Sets default values
AAInteractionButton::AAInteractionButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAInteractionButton::Interact()
{
	if (!bIsPressed)
	{
		bIsPressed = true;
		OnButtonPressed.Broadcast(this);
		UE_LOG(LogTemp, Warning, TEXT("INTERACTED"));
	}
}

void AAInteractionButton::PressMeshZ(USceneComponent* TargetMesh, float PressDistance, float Duration)
{
    if (!TargetMesh) return;

    PressedMesh = TargetMesh;

    FVector Start = PressedMesh->GetRelativeLocation();
    TargetLocation = Start + FVector(0.f, 0.f, PressDistance);
    InterpSpeed = FMath::Abs(PressDistance) / Duration;

    SetActorTickEnabled(true);
    PrimaryActorTick.bCanEverTick = true;

    // Tick 정지를 위한 안전 타이머 (지나치게 계속 도는 것 방지)
    GetWorld()->GetTimerManager().SetTimer(StopTickTimer, this, &AAInteractionButton::StopTick, Duration + 0.2f, false);
}

void AAInteractionButton::StopTick()
{
    SetActorTickEnabled(false);
    PrimaryActorTick.bCanEverTick = false;
    PressedMesh = nullptr;
}


// Called when the game starts or when spawned
void AAInteractionButton::BeginPlay()
{
	Super::BeginPlay();
	
    UE_LOG(LogTemp, Warning, TEXT("AInteractionButton BeginPlay"));
}

// Called every frame
void AAInteractionButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!PressedMesh) return;

    FVector Current = PressedMesh->GetRelativeLocation();
    FVector NewLoc = FMath::VInterpTo(Current, TargetLocation, DeltaTime, InterpSpeed);

    PressedMesh->SetRelativeLocation(NewLoc);

    // 충분히 도달했으면 Tick 멈추기 (선택사항)
    if (FVector::Dist(NewLoc, TargetLocation) < 0.5f)
    {
        StopTick();
    }

}

