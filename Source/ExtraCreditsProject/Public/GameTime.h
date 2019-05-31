// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameTime.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTRACREDITSPROJECT_API UGameTime : public UActorComponent
{
	GENERATED_BODY()

private:
	//This is 24 * 3600
	const int SECS_IN_DAY = 86400;

	float time = 0.0f;

	//this represents how many Minutes within the game to tick for every real-life second that passes
	float inGameMinsPerActualSecs = 0.0f;

public:	
	// Sets default values for this component's properties
	UGameTime();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float gameSpeedInMins = 10.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
