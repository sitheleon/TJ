// Fill out your copyright notice in the Description page of Project Settings.


#include "InactivityCheckComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInactivityCheckComponent::UInactivityCheckComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInactivityCheckComponent::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PC->GetMousePosition(LastMousePosition.X, LastMousePosition.Y);
	}


	
}


// Called every frame
void UInactivityCheckComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (HasMouseMoved() || HasKeyJustPressed())
	{
		ResetInactivityTimer();
		//UE_LOG(LogTemp, Warning, TEXT("ResetTimer"))
	}
	else
	{
		InActivityTime += DeltaTime;
	}

	//UE_LOG(LogTemp, Error, TEXT("Current Inactivity Timer: %f"), InActivityTime);

	if (!bHasBroadcasted && InActivityTime >= InactivityThreshold)
	{
		bHasBroadcasted = true;

		//UE_LOG(LogTemp, Warning, TEXT("BreoadCast"));

		OnInactivityDetected.Broadcast();
	}
}

bool UInactivityCheckComponent::IsInactive() const
{
	return InActivityTime >= InactivityThreshold;
}

void UInactivityCheckComponent::ResetInactivityTimer()
{
	InActivityTime = 0.f;
	bHasBroadcasted = false;
}

bool UInactivityCheckComponent::HasMouseMoved() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if(!PC)
	{
		return false;
	}

	FVector2D CurrentPos;


	if (PC->GetMousePosition(CurrentPos.X, CurrentPos.Y))
	{
		if(!CurrentPos.Equals(LastMousePosition, 1.0f))
		{
			LastMousePosition = CurrentPos;
			return true;
		}
	}

	return false;

}


bool UInactivityCheckComponent::HasKeyJustPressed() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC)
	{
		return false;
	}

	TArray<FKey> KeysToCheck =
	{
		EKeys::AnyKey,
        EKeys::LeftMouseButton,
        EKeys::RightMouseButton,
        EKeys::W,
        EKeys::A,
        EKeys::S,
        EKeys::D
	};

	for (const FKey& Key : KeysToCheck)
	{
		if(PC->WasInputKeyJustPressed(Key))
		{	
			UE_LOG(LogTemp, Warning, TEXT("KeyPressed"));
			return true;
		}
	}

	return false;
}

