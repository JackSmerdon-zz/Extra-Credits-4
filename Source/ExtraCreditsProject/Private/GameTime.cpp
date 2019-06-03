// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "Public/GameTime.h"

// Sets default values for this component's properties
UGameTime::UGameTime()
{
	PrimaryComponentTick.bCanEverTick = true;

	SunLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunLight"));
	SunLight->bUsedAsAtmosphereSunLight = true;

	dayLengthInMins = 24.0f / gameSpeedInMins;
	dayLengthInSecs = dayLengthInMins * 60;
	inGameSecsPerActualSecs = SECS_IN_DAY / dayLengthInSecs;
	deltaSunRot = 360.0f / dayLengthInSecs;

	//set the inital state of the sun based off the start time
	time = startTimeInHours * 3600.0f;
}

// Called when the game starts
void UGameTime::BeginPlay()
{
	Super::BeginPlay();

	FRotator sunRot;
	sunRot.Pitch = (7.5f * startTimeInHours) - 90.0f;
	GetOwner()->SetActorRotation(sunRot);
}

// Called every frame
void UGameTime::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	time += inGameSecsPerActualSecs * DeltaTime;

	//update the rotation of the sun each frame
	FRotator ActorRotation = FRotator(-(deltaSunRot * DeltaTime), 0, 0);
	FQuat QuatRotation = FQuat(ActorRotation);
	GetOwner()->AddActorLocalRotation(QuatRotation);

	if (time >= SECS_IN_DAY)
	{
		time = 0;
		day++;
	}

	//FString timeString = formatHours(time) + ":" + formatMins(time);
	//print(timeString);
}

//allows the time to be formatted correctly
FString UGameTime::formatMins(int currentTime)
{
	FString newTime = "";
	int32 mins = 0;

	currentTime %= 3600;
	mins = currentTime / 60;

	if (mins < 10)
	{
		newTime = FString::FromInt(0) + FString::FromInt(mins);
	}
	else
	{
		newTime = FString::FromInt(mins);
	}

	return newTime;
}

//allows the time to be formatted correctly
FString UGameTime::formatHours(int currentTime)
{
	FString newTime = "";
	int32 hours = 0;

	hours = currentTime / 3600;
	currentTime %= 3600;

	if (hours < 10)
	{
		newTime = FString::FromInt(0) + FString::FromInt(hours);
	}
	else
	{
		newTime = FString::FromInt(hours);
	}

	return newTime;
}

FString UGameTime::GetFormattedTime()
{
	return formatHours(time) + ":" + formatMins(time);
}