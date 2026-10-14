// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AInteractionButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressed, AActor*, ButtonActor);

UCLASS()
class A_TONGJEON_API AAInteractionButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAInteractionButton();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnButtonPressed OnButtonPressed;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	bool bIsPressed = false;

	UFUNCTION(BlueprintCallable)
	void Interact();

	//
		//
		UFUNCTION(BlueprintCallable)
		void PressMeshZ(USceneComponent* TargetMesh, float PressDistance, float Duration = 0.5f);
	
	
		FVector TargetLocation;
		USceneComponent* PressedMesh;
	
		float InterpSpeed;
		FTimerHandle StopTickTimer;
	
		void StopTick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
