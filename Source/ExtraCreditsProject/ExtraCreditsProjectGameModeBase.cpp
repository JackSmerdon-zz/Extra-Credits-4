// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraCreditsProjectGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AExtraCreditsProjectGameModeBase::AExtraCreditsProjectGameModeBase()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode now running"));

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Core/MainCharacterBP"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}