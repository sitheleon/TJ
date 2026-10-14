// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInspection.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PointLightComponent.h"

// Sets default values
AItemInspection::AItemInspection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorldMesh"));
	RootComponent = WorldMesh;

	InspectionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InspectionMesh"));
	InspectionMesh->SetupAttachment(RootComponent);
	InspectionMesh->SetVisibility(false);

}

// Called when the game starts or when spawned
void AItemInspection::BeginPlay()
{
	Super::BeginPlay();
	
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bPlayerMovementEnabled = true;

    WorldMesh->SetVisibility(true);

    UE_LOG(LogTemp, Warning, TEXT("Inspection BeginPlay"));
}

// Called every frame
void AItemInspection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	        // 인스펙션 상태일 때 메쉬 회전
			if (bIsInspecting)
			{
				FRotator CurrentRotation = InspectionMesh->GetRelativeRotation();
				CurrentRotation.Yaw += RotationSpeed * DeltaTime;
				InspectionMesh->SetRelativeRotation(CurrentRotation);
			}
}

void AItemInspection::TriggerInspection()
{
	if (PlayerController)
    {
        // 플레이어 캐릭터 가져오기
        ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerController->GetPawn());
        if (PlayerCharacter)
        {
            // 플레이어 움직임 비활성화
            PlayerCharacter->GetCharacterMovement()->DisableMovement();
            bPlayerMovementEnabled = false;

            // 플레이어 카메라 가져오기
            UCameraComponent* PlayerCamera = PlayerCharacter->FindComponentByClass<UCameraComponent>();
            if (PlayerCamera)
            {   
                bIsInspecting = true; // 인스펙션 상태로 변경   

                // 인스펙션 메쉬를 카메라 앞에 배치
                FVector CameraLocation = PlayerCamera->GetComponentLocation();
                FRotator CameraRotation = PlayerCamera->GetComponentRotation();
                FVector InspectionLocation = CameraLocation + CameraRotation.Vector() * CameraDistance; // 카메라 앞 100 유닛

                InspectionLocation.Z -= 15.0f; // 약간 아래로 위치 조정

                InspectionMesh->SetWorldLocation(InspectionLocation);
                InspectionMesh->SetWorldRotation(CameraRotation);
                InspectionMesh->SetVisibility(true);

                WorldMesh->SetVisibility(false);





            }

            // 플레이어 입력 비활성화
            PlayerController->SetIgnoreMoveInput(true);
            PlayerController->SetIgnoreLookInput(true);
			
        }
    }
}

void AItemInspection::EndInspection()
{
	if (PlayerController)
    {
        // 플레이어 캐릭터 가져오기
        ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerController->GetPawn());
        if (PlayerCharacter && !bPlayerMovementEnabled)
        {
            // 플레이어 움직임 재활성화
            PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
            bPlayerMovementEnabled = true;

            // 인스펙션 메쉬 숨기기
            InspectionMesh->SetVisibility(false);

            // 플레이어 입력 활성화
            PlayerController->SetIgnoreMoveInput(false);
            PlayerController->SetIgnoreLookInput(false);



            bIsTriggered = false;
        }
        
    }
}

