#include "Mannequin.h"
#include "Components/PoseableMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMesh"));
	RootComponent = PoseableMesh;



}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	UpdateTargetPose(); // 즉시 한 번 실행

}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMannequin::UpdateTargetPose()
{
	TArray<FName> AllBones = {
		"head", "neck",
		"lForeArm", "rForeArm",
		"lHand", "rHand",
		"lShin", "rShin",
		"lFoot", "rFoot"
	};

	TArray<float> Angles = { -30.f, -15.f, 0.f, 15.f, 30.f };

	int32 NumToMove = FMath::RandRange(1, 2);
	for (int i = 0; i < NumToMove; ++i)
	{
		int32 BoneIndex = FMath::RandRange(0, AllBones.Num() - 1);
		FName BoneName = AllBones[BoneIndex];

		FRotator Rotation = FRotator::ZeroRotator;

		if (BoneName == "head")
		{
			// 머리는 Yaw만 회전 (좌우)
			Rotation.Yaw = Angles[FMath::RandRange(0, Angles.Num() - 1)];
		}
		else
		{
			// 다른 본은 Pitch, Yaw, Roll 모두 회전
			Rotation.Pitch = Angles[FMath::RandRange(0, Angles.Num() - 1)];
			Rotation.Yaw   = Angles[FMath::RandRange(0, Angles.Num() - 1)];
			Rotation.Roll  = Angles[FMath::RandRange(0, Angles.Num() - 1)];
		}

		PoseableMesh->SetBoneRotationByName(BoneName, Rotation, EBoneSpaces::ComponentSpace);
	}
}

void AMannequin::ChangeToRandomPosition(APlayerController* TargetController)
{
    if (!TargetController) return;

    APawn* PlayerPawn = TargetController->GetPawn();
    if (!PlayerPawn) return;

    FVector PlayerLocation = PlayerPawn->GetActorLocation();

    // 월드에 있는 모든 마네킹 찾기
    TArray<AActor*> Mannequins;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), Mannequins);

    int32 NumMannequins = Mannequins.Num();
    if (NumMannequins == 0) return;

    // 현재 마네킹의 인덱스 찾기
    int32 MyIndex = Mannequins.IndexOfByKey(this);

    // 원형 배치 반지름
    float Radius = 300.0f;

    // 각도 계산 (360도/마네킹 수)
    float AngleStep = 2 * PI / NumMannequins;
    float MyAngle = MyIndex * AngleStep;

    // 플레이어 기준 원형 배치 위치 계산
    FVector Offset = FVector(FMath::Cos(MyAngle), FMath::Sin(MyAngle), 0.f) * Radius;
    FVector NewLocation = PlayerLocation + Offset;
    NewLocation.Z = GetActorLocation().Z; // 기존 Z값 유지

    SetActorLocation(NewLocation);
}










