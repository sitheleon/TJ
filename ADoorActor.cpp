// Fill out your copyright notice in the Description page of Project Settings.


#include "ADoorActor.h"
#include "AInteractionButton.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"

#include "TongJeonGameInstance.h"

#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AADoorActor::AADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);

}







// Called when the game starts or when spawned
void AADoorActor::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UTongJeonGameInstance>(GetGameInstance());

	InitialRotation = DoorMesh->GetRelativeRotation();

	for (TActorIterator<AAInteractionButton> It(GetWorld()); It; ++It)
	{
		if (It->ActorHasTag("Button1"))
		{
			Button1 = *It;
		}
		else if (It->ActorHasTag("Button2"))
		{
			Button2 = *It;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Found NO TAGGED BUTTON"));	
		}
	}

	if(!Button1 || !Button2)
	{
		UE_LOG(LogTemp, Error, TEXT("Button1 or Button2 is not found"));
		return;
	}
	
	UE_LOG(LogTemp, Warning , TEXT("Button1 : %s"), *Button1->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Button2 : %s"), *Button2->GetName());

	if (Button1)
	{
		Button1->OnButtonPressed.AddDynamic(this, &AADoorActor::HandleButtonPressed);
	}

	if (Button2)
	{
		Button2->OnButtonPressed.AddDynamic(this, &AADoorActor::HandleButtonPressed);
	}
	
}

void AADoorActor::HandleButtonPressed(AActor* ButtonActor)
{
	TryOpenDoor();
}

void AADoorActor::TryOpenDoor()
{	
	
	UE_LOG(LogTemp, Warning, TEXT("Button1: %d, Button2: %d"), Button1->bIsPressed, Button2->bIsPressed);
	
	if (Button1 && Button2 && Button1->bIsPressed && Button2->bIsPressed && !bIsDoorOpened)
	{
		bIsDoorOpened = true;
		UE_LOG(LogTemp, Warning, TEXT("Door Opened")); // 문 여는 로직 
		//DoorMesh->SetRelativeRotation(FRotator(0.0f, 100.0f, 0.0f));

		
	}
}

void AADoorActor::CloseDoor()
{

		FRotator NewRotation = FMath::RInterpTo(InitialRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), RotationInterpSpeed);
		DoorMesh->SetRelativeRotation(NewRotation);

		UE_LOG(LogTemp, Warning, TEXT("Door Closed")); // 문 닫는 로직
		bIsDoorOpened = false;

}



// Called every frame
void AADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bIsDoorOpened && DoorMesh)
	{
		FRotator CurrentRotation = DoorMesh->GetRelativeRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationInterpSpeed);
		DoorMesh->SetRelativeRotation(NewRotation); 
		
		if (!DoorOpenSound)
		{
			return;
		}

		if (bIsSoundPlayed)
		{
			return; // 이미 소리가 재생 중이면 아무것도 하지 않음
		}

		UGameplayStatics::PlaySoundAtLocation(this, DoorOpenSound, GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Door is opening"));
		bIsSoundPlayed = true;


	}


	////////////////



}

