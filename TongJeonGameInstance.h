// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TongJeonGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class A_TONGJEON_API UTongJeonGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UTongJeonGameInstance();

	virtual void Init() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsHighSuspicion = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsBasementMiniGameOn = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsPlayerFacingMirror = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float SuspicionLevel;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsReadyToEnd = false;
};
