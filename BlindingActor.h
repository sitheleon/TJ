// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlindingActor.generated.h"

UCLASS()
class A_TONGJEON_API ABlindingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlindingActor();

	UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* MeshComponent;

	UFUNCTION(BlueprintCallable, Category = "Blinding")
	void SetBlind();

	UFUNCTION(BlueprintCallable, Category = "Blinding")
	void SetUnBlind();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
