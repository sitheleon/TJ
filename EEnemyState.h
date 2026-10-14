// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum EEnemyState
{
	Stop UMETA(DisplayName = "Stop"),
	Idle UMETA(DisplayName = "Idle"),
	Chase UMETA(DisplayName = "Chase"),
	RealChase UMETA(DisplayName = "RealChase"),
	OnlyChase UMETA(DisplayName = "OnlyChase"),
};
