// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraCreditsProjectGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "PlayerHUD.h"
#include "UserWidget.h"

void AExtraCreditsProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

AExtraCreditsProjectGameModeBase::AExtraCreditsProjectGameModeBase()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode now running"));

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Core/MainCharacterBP"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}