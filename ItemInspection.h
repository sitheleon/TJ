// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInspection.generated.h"





UCLASS()
class A_TONGJEON_API AItemInspection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemInspection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsTriggered = false;

    UPROPERTY(BlueprintReadOnly)
    bool bIsInspecting = false;

    // 월드용 오브젝트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inspection")
    class UStaticMeshComponent* WorldMesh;

    // 인스펙션 오브젝트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inspection")
    class UStaticMeshComponent* InspectionMesh;




    // 트리거 인스펙션 함수
    UFUNCTION(BlueprintCallable, Category = "Inspection")
    void TriggerInspection();

    // 끝내기 함수
    UFUNCTION(BlueprintCallable, Category = "Inspection")
    void EndInspection();

    UPROPERTY(EditAnywhere, Category = "Inspection")
    float CameraDistance = 70.0f;

    UPROPERTY(EditAnywhere, Category = "Inspection")
    float RotationSpeed = 50.0f;


private:
    // 플레이어 컨트롤러 참조
    APlayerController* PlayerController;

    // 원래 플레이어의 이동 상태를 저장
    bool bPlayerMovementEnabled;

    UPROPERTY(VisibleAnywhere, Category = "Lighting")
    class UPointLightComponent* InspectionLight;
};
