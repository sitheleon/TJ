// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mannequin.generated.h"

UCLASS()
class A_TONGJEON_API AMannequin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMannequin();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UPoseableMeshComponent* PoseableMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UFUNCTION(BlueprintCallable, Category = "Pose")
	void UpdateTargetPose();

	UFUNCTION(BlueprintCallable, Category = "Pose")
	void ChangeToRandomPosition(APlayerController* TargetController);

};
