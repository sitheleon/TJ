// Copyright Epic Games, Inc. All Rights Reserved.

#include "A_TongJeonGameMode.h"
#include "A_TongJeonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AA_TongJeonGameMode::AA_TongJeonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
