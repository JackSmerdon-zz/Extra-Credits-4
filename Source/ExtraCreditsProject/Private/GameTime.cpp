// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "GameTime.h"

// Sets default values for this component's properties
UGameTime::UGameTime()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGameTime::BeginPlay()
{
	Super::BeginPlay();


	inGameMinsPerActualSecs = SECS_IN_DAY / (gameSpeedInMins * 60);
}

// Called every frame
void UGameTime::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	time += inGameMinsPerActualSecs * DeltaTime;

	printFString("Time = %f", time);
}