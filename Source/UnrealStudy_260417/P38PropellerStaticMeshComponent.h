// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "P38PropellerStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_260417_API UP38PropellerStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UP38PropellerStaticMeshComponent();


	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	float RotateSpeed = 1200.0f;
};
