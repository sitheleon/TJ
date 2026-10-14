// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADoorActor.generated.h"
class AAInteractionButton;

UCLASS()
class A_TONGJEON_API AADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AADoorActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	class USoundCue* DoorOpenSound;

	UPROPERTY(VisibleAnywhere, Category = "Door")
	AAInteractionButton* Button1;

	UPROPERTY(VisibleAnywhere, Category = "Door")
	AAInteractionButton* Button2;

	UPROPERTY(EditAnywhere, Category = "Door")
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	bool bIsDoorOpened = false;

	bool bIsSoundPlayed = false;


	class UTongJeonGameInstance* GameInstance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleButtonPressed(AActor* ButtonActor);

	void TryOpenDoor();

	UFUNCTION(BlueprintCallable)
	void CloseDoor();

	FRotator InitialRotation;

    UPROPERTY(EditAnywhere)
	FRotator TargetRotation = FRotator(0.0f, 90.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	float RotationInterpSpeed = 1.0f; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
