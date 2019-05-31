// Fill out your copyright notice in the Description page of Project Settings.

#include "..\Public\PlayerWifiModule.h"

// Sets default values for this component's properties
UPlayerWifiModule::UPlayerWifiModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UPlayerWifiModule::WithinWifiRange(float f)
{
	hasWifi = true;
	currentDepleteRate = f;
}

// Called when the game starts
void UPlayerWifiModule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPlayerWifiModule::deplete(float f)
{
	wifiHealth -= currentDepleteRate * f;
}

void UPlayerWifiModule::noWifi()
{
	hasWifi = false;
	if (currentDepleteRate != defaultDepleteRate) currentDepleteRate = defaultDepleteRate;
}


// Called every frame
void UPlayerWifiModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//depleate wifi health
	deplete(DeltaTime);

	//disable bool (will be re-enabled by wifi component)
	noWifi();
	// ...
}

