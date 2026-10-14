// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SpotLightComponent.h"

#include "TongJeonGameInstance.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
    SpotLight->SetupAttachment(GetMesh(), TEXT("IEye")); // 스켈레톤의 "IEye" 본에 부착
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	BlackboardComponent = GetController<AAIController>()->GetBlackboardComponent();
	
	BlackboardComponent->SetValueAsEnum("CurrentState", InitialState);

	GameInstance = Cast<UTongJeonGameInstance>(GetGameInstance());

	UE_LOG(LogTemp, Warning, TEXT("EnemyCharacter BeginPlay called"));

    SpotLight->SetIntensity(0.0f); // 초기 상태에서 빛을 끔


}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameInstance->bIsHighSuspicion)
	{
		// SuperChase 상태 전환은 한 번만
		if (!bSuperChaseSet)
		{
			SetToSuperChageState();
			bSuperChaseSet = true;
		}

		// 5초 후 무조건 플레이어 추격
		if (!bForceChaseStarted)
		{
			UE_LOG(LogTemp, Warning, TEXT("ForceChasePlayer CALLED"));

			bForceChaseStarted = true;
			GetWorldTimerManager().SetTimer(
				ForceChaseTimerHandle,
				this,
				&AEnemyCharacter::ForceChasePlayer,
				2.0f,
				false
			);
		}
	}


}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::SetToChaseState()
{
    EEnemyState CurrentState = static_cast<EEnemyState>(BlackboardComponent->GetValueAsEnum(TEXT("CurrentState")));
    if (CurrentState == EEnemyState::Chase || CurrentState == EEnemyState::OnlyChase)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum("CurrentState", EEnemyState::Chase);
    UE_LOG(LogTemp, Warning, TEXT("State changed to Chase"));
}

void AEnemyCharacter::DetectPlayer(APawn* DetectedPawn, APawn* PawnToDetect)
{
    EEnemyState CurrentState = static_cast<EEnemyState>(BlackboardComponent->GetValueAsEnum(TEXT("CurrentState")));

    if (CurrentState == EEnemyState::OnlyChase) { return; }
    if (DetectedPawn != PawnToDetect || CurrentState == EEnemyState::Stop) { return; }

    UE_LOG(LogTemp, Warning, TEXT("Player Detected!"));

    if (GameInstance->bIsHighSuspicion)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum("CurrentState", EEnemyState::Stop);
}

void AEnemyCharacter::SetToStopState()
{
    EEnemyState CurrentState = static_cast<EEnemyState>(BlackboardComponent->GetValueAsEnum(TEXT("CurrentState")));
    if (CurrentState == EEnemyState::Stop || CurrentState == EEnemyState::OnlyChase)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum("CurrentState", EEnemyState::Stop);
    UE_LOG(LogTemp, Warning, TEXT("State changed to Stop"));
}

void AEnemyCharacter::SetToSuperChageState()
{
    EEnemyState CurrentState = static_cast<EEnemyState>(BlackboardComponent->GetValueAsEnum(TEXT("CurrentState")));
    if (CurrentState == EEnemyState::OnlyChase)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum("CurrentState", EEnemyState::RealChase);
    UE_LOG(LogTemp, Warning, TEXT("State changed to SuperChase"));
}

void AEnemyCharacter::ForceChasePlayer()
{
    // OnlyChase 상태에서는 이미 추격 중이므로 중복 변경 방지
    EEnemyState CurrentState = static_cast<EEnemyState>(BlackboardComponent->GetValueAsEnum(TEXT("CurrentState")));
    if (CurrentState == EEnemyState::OnlyChase)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum("CurrentState", EEnemyState::OnlyChase);
    UE_LOG(LogTemp, Warning, TEXT("ForceChasePlayer called, changing state to OnlyChase"));

    SpotLight->SetIntensity(10000); // 빛을 켬
}


