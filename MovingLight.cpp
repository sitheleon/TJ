// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingLight.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TongJeonGameInstance.h"	

// Sets default values
AMovingLight::AMovingLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	RootComponent = SpotLight;

	// 기본 Intensity 설정
	BaseIntensity = 15000.0f;        // 기본 빛 세기
	HighSuspicionIntensity = 100000.0f; // 의심도가 높을 때 빛 세기
	SpotLight->SetIntensity(BaseIntensity);

	// 깜빡이기 관련 변수 초기화
	BlinkInterval = 0.2f; // 깜빡이는 간격 (초)
	BlinkTimer = 0.0f;    // 타이머 초기화
	bIsLightOn = true;    // 초기 상태에서 빛이 켜져 있음
}

// Called when the game starts or when spawned
void AMovingLight::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UTongJeonGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		bShouldAccelerate = GameInstance->bIsHighSuspicion;
		SpotLight->SetIntensity(bShouldAccelerate ? HighSuspicionIntensity : BaseIntensity);
	}

}

// Called every frame
void AMovingLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameInstance)
	{
		bShouldAccelerate = GameInstance->bIsHighSuspicion;
	}

	// 의심도가 높아지면 모든 빛을 끔
	if (bShouldAccelerate)
	{
		SpotLight->SetIntensity(0.0f);
	}
	else
	{
		// 의심도가 낮아지면 기본 상태 유지 (Intensity만 BaseIntensity로 설정)
		SpotLight->SetIntensity(BaseIntensity);
	}
}
