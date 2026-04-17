// Fill out your copyright notice in the Description page of Project Settings.


#include "P38Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "P38PropellerStaticMeshComponent.h"
#include "Rocket.h"

#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AP38Pawn::AP38Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> P38Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI_Body(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/P38/Materials/MI_P38.MI_P38'"));

	if (P38Body.Succeeded())
	{
		Body->SetStaticMesh(P38Body.Object);
	}

	if (MI_Body.Succeeded())
	{
		Body->SetMaterial(0, MI_Body.Object);
	}

	Left = CreateDefaultSubobject<UP38PropellerStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UP38PropellerStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	Left->SetRelativeLocation(FVector(40.000000f, -20.000000f, 0.000000f));
	Right->SetRelativeLocation(FVector(40.000000f, 20.000000f, 0.000000f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(300.0f, 0.0f, 0.0f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->SocketOffset = FVector(0, 0, 40.0f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->TargetArmLength = 200.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 500.0f;
	

}

// Called when the game starts or when spawned
void AP38Pawn::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AP38Pawn::ProcessBeginOverlap);
}

// Called every frame
void AP38Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostValue);

}

// Called to bind functionality to input
void AP38Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &AP38Pawn::Rotate);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AP38Pawn::Fire);
		UIC->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AP38Pawn::Boost);
		UIC->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AP38Pawn::UnBoost);

	}

}

void AP38Pawn::Rotate(const FInputActionValue& value)
{
	FVector Rot = value.Get<FVector>();
	

	AddActorLocalRotation(FRotator(Rot.Y * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 80.0f,
		Rot.Z * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f,
		Rot.X * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f));
}

void AP38Pawn::Fire()
{
	GetWorld()->SpawnActor<ARocket>(ARocket::StaticClass(), Arrow->GetComponentTransform());
}

void AP38Pawn::Boost()
{
	BoostValue = 1.0f;
}

void AP38Pawn::UnBoost()
{
	BoostValue = 0.5f;
}

void AP38Pawn::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

