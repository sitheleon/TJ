// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EEnemyState.h"
#include "TongJeonGameInstance.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class A_TONGJEON_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	class UBlackboardComponent* BlackboardComponent;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UTongJeonGameInstance* GameInstance;





public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float SuspicionLevel = 0.0f;

	UFUNCTION(BlueprintCallable)
	void SetToChaseState();

	UFUNCTION(BlueprintCallable)
	void DetectPlayer(APawn* DetectedPawn, APawn* PawnToDetect);

	UFUNCTION(BlueprintCallable)
	void SetToStopState();

	UFUNCTION(BlueprintCallable)
	void SetToSuperChageState();

	FTimerHandle ForceChaseTimerHandle;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)	
	bool bForceChaseStarted = false;

	UFUNCTION()
	void ForceChasePlayer();

	bool bSuperChaseSet = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpotLightComponent* SpotLight;
};

