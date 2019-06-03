// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExtraCreditsProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class AExtraCreditsProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override; //override begin play from the base class

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time", Meta = (BlueprintProtected = "True"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

public:
	AExtraCreditsProjectGameModeBase();
};
