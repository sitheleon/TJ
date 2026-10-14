// Fill out your copyright notice in the Description page of Project Settings.


#include "BlindingActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
ABlindingActor::ABlindingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

void ABlindingActor::SetBlind()
{
	MeshComponent->SetVisibility(true); // Mesh를 보이게 설정
}

void ABlindingActor::SetUnBlind()
{
	MeshComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABlindingActor::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->SetVisibility(false); // 초기에는 Mesh를 보이지 않게 설정

}

// Called every frame
void ABlindingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

