// Fill out your copyright notice in the Description page of Project Settings.


#include "P38PropellerStaticMeshComponent.h"

UP38PropellerStaticMeshComponent::UP38PropellerStaticMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> P38Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));

	if (P38Propeller.Succeeded())
	{
		SetStaticMesh(P38Propeller.Object);
	}
}

void UP38PropellerStaticMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AddRelativeRotation(FRotator(0, 0, RotateSpeed * DeltaTime));

}
