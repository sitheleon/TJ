// Copyright Epic Games, Inc. All Rights Reserved.

#include "A_TongJeonCharacter.h"
#include "A_TongJeonProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "TongJeonGameInstance.h"

#include "InactivityCheckComponent.h"

//////////////////////////////////////////////////////////////////////////
// AA_TongJeonCharacter

AA_TongJeonCharacter::AA_TongJeonCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));



	    // 새 Skeletal Mesh Component 생성 및 루트에 부착
	ExtraMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ExtraMesh"));
	ExtraMesh->SetupAttachment(RootComponent);

	
	//InactivityComp = CreateDefaultSubobject<UInactivityCheckComponent>(TEXT("Inactivity Component"));


}

void AA_TongJeonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


 	// Get the game instance
	GameInstance = Cast<UTongJeonGameInstance>(GetGameInstance());

}

//////////////////////////////////////////////////////////////////////////

bool AA_TongJeonCharacter::bIsMoving()
{
	 // 현재 속도를 가져옴
	FVector CurrentVelocity = GetVelocity();

	// 속도의 크기가 0보다 크면 움직이고 있는 상태
	return !CurrentVelocity.IsNearlyZero();
}

void AA_TongJeonCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	GameInstance->SuspicionLevel = SuspicionLevel;
}

//////////////////////////////////////////////////////////////////////////// Input

void AA_TongJeonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		// 연속 점프 개선
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AA_TongJeonCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AA_TongJeonCharacter::Look);
	}
}


void AA_TongJeonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AA_TongJeonCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AA_TongJeonCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AA_TongJeonCharacter::GetHasRifle()
{
	return bHasRifle;
}


float AA_TongJeonCharacter::GetSuspicionLevel()
{
	return SuspicionLevel;
}

void AA_TongJeonCharacter::AdjustSuspicionLevel(float Amount)
{
	SuspicionLevel = FMath::Clamp(SuspicionLevel + Amount, 0.0f, 100.0f);
    if (SuspicionLevel >= 50.0f)
    {
        // 급박한 음악 재생 트리거 
        UE_LOG(LogTemp, Warning, TEXT("High Suspicion!"));

		if (GameInstance)
		{
			GameInstance->bIsHighSuspicion = true;
		}
    }
}




void AA_TongJeonCharacter:: MoveExtraMeshCloser()
{
	bMoveExtraMesh = true;

	if (ExtraMesh && SuspicionLevel <= 90.0f)	
	{	
		FVector Offset(0.0f, -50.0f, 0.0f);
		ExtraMesh->AddWorldOffset(Offset);

		UE_LOG(LogTemp, Warning, TEXT("Extra Mesh Moved!"));
	}
}