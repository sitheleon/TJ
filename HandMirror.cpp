// Fill out your copyright notice in the Description page of Project Settings.


#include "HandMirror.h"

#include "Kismet/GameplayStatics.h"
#include "TongJeonGameInstance.h"
#include "GameFrameWork/Character.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHandMirror::AHandMirror()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Mesh->SetVisibility(false);

}

// Called when the game starts or when spawned
void AHandMirror::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	
	GameInstance = Cast<UTongJeonGameInstance>(GetGameInstance());

	
}

void AHandMirror::TriggerHandMirror()
{
	if (PlayerController)
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			UCameraComponent* PlayerCamera = PlayerCharacter->FindComponentByClass<UCameraComponent>();

			if (PlayerCamera)
			{
				FVector CameraLocation = PlayerCamera->GetComponentLocation();
				FRotator CameraRotation = PlayerCamera->GetComponentRotation();
				FVector MirrorLocation = CameraLocation + CameraRotation.Vector() * 300.0f;
		

				Mesh->SetWorldLocation(MirrorLocation);
				Mesh->SetWorldRotation(CameraRotation + FRotator(0.0f, 180.0f, 0.0f)); 
				Mesh->SetVisibility(true);

			}
		}	
	}
}

void AHandMirror::EndHandMirror()
{
	if (PlayerController)
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			UCameraComponent* PlayerCamera = PlayerCharacter->FindComponentByClass<UCameraComponent>();

			if (PlayerCamera)
			{
				Mesh->SetVisibility(false);
			}
		}
	}
}

// Called every frame
void AHandMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

