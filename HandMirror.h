// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "HandMirror.generated.h"

UCLASS()
class A_TONGJEON_API AHandMirror : public AActor
{
	GENERATED_BODY()
private:

	class UTongJeonGameInstance* GameInstance;
	
	APlayerController* PlayerController;
public:	
	// Sets default values for this actor's properties
	AHandMirror();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void TriggerHandMirror();	

	UFUNCTION(BlueprintCallable)
	void EndHandMirror();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HandMirror")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HandMirror")
	class UStaticMeshComponent* Root;
};
