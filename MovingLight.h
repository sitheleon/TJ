#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingLight.generated.h"

UCLASS()
class A_TONGJEON_API AMovingLight : public AActor
{
	GENERATED_BODY()

private:
	class UTongJeonGameInstance* GameInstance;

	// 빛 세기 관련 변수
	UPROPERTY(EditAnywhere)
	float BaseIntensity = 5000.0f;

	UPROPERTY(EditAnywhere)
	float HighSuspicionIntensity = 100000.0f;

	UPROPERTY(EditAnywhere)
	float BlinkInterval = 0.2f; // 깜빡이는 간격 (초)

	float BlinkTimer = 0.0f;    // 타이머 값
	bool bIsLightOn = true;     // 현재 빛이 켜져 있는지 여부
	bool bShouldAccelerate = false;

public:	
	// Sets default values for this actor's properties
	AMovingLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpotLightComponent* SpotLight;
};
