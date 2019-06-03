// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Engine.h"
#include "Components/DirectionalLightComponent.h"
#include "GameTime.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXTRACREDITSPROJECT_API UGameTime : public UActorComponent
{
	GENERATED_BODY()

private:
	//This is 24 * 3600
	const uint32 SECS_IN_DAY = 86400;

	//current time
	float time = 0.0f;

	//the rotation of the sun
	float sunRotTimer = 0.0f;

	//this represents how many seconds within the game to tick for every real-life second that passes
	float inGameSecsPerActualSecs = 0.0f;

	float dayLengthInSecs = 0.0f;
	float dayLengthInMins = 0.0f;

	float deltaSunRot = 0.0f;

	FString formatMins(int currentTime);
	FString formatHours(int currentTime);

	uint16 day = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Lighting")
		class UDirectionalLightComponent* SunLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Lighting")
		float gameSpeedInMins = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Lighting")
		float startTimeInHours = 7.0f;

public:
	// Sets default values for this component's properties
	UGameTime();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//returns the time but formatted as a 24-hour clock
	UFUNCTION(BlueprintPure, Category = "Game Time")
	FString GetFormattedTime();
};