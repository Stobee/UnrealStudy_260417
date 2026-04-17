// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "P38Pawn.h"

AMyGameMode::AMyGameMode()
{

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass
	(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_PlayerController.BP_PlayerController_C'"));

	if (PlayerControllerBPClass.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_P38.BP_P38_C'"));
	
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}