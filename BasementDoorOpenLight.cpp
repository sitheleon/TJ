// Fill out your copyright notice in the Description page of Project Settings.


#include "BasementDoorOpenLight.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ABasementDoorOpenLight::ABasementDoorOpenLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	RootComponent = SpotLight;

}

// Called when the game starts or when spawned
void ABasementDoorOpenLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasementDoorOpenLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

