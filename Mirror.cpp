// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror.h"
#include "Components/StaticMeshComponent.h"
#include "TongJeonGameInstance.h"

// Sets default values
AMirror::AMirror()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AMirror::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UTongJeonGameInstance>(GetGameInstance());
	
}

// Called every frame
void AMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

