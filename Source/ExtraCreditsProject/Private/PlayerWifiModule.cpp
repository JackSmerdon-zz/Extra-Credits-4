// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PlayerWifiModule.h"

// Sets default values for this component's properties
UPlayerWifiModule::UPlayerWifiModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UPlayerWifiModule::addWifiToList(Uwifi_component* comp)
{
	if (!nearbyWifiComponents.Contains(comp)) 
	{
		int listCount = nearbyWifiComponents.Num();
		if (listCount == 0) nearbyWifiComponents.Add(comp);
		else 
		{
			nearbyWifiComponents.Add(comp);
			sortWifiArray();
		}
	}
}

void UPlayerWifiModule::removeWifiFromList(Uwifi_component* comp)
{
	if (nearbyWifiComponents.Contains(comp)) 
	{
		nearbyWifiComponents.Remove(comp);
	}
}

void UPlayerWifiModule::WithinWifiRange(float f)
{
	hasWifi = true;
	if(f > currentDepleteRate)
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

void UPlayerWifiModule::sortWifiArray()
{
	int numberOfElements = nearbyWifiComponents.Num();
	if (numberOfElements > 0) {
		for (int i = 0; i < numberOfElements; i++) {
			for (int j = 0; j < numberOfElements - i; j++)
				if(j+1 < numberOfElements)
					if ((nearbyWifiComponents[j]->getWifiDistance() - nearbyWifiComponents[j]->getWifiHealth()) > (nearbyWifiComponents[j + 1]->getWifiDistance() - nearbyWifiComponents[j + 1]->getWifiHealth()))
						nearbyWifiComponents.Swap(j, j + 1);
		}
	}
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
	sortWifiArray();
	//disable bool (will be re-enabled by wifi component)
	noWifi();
	// ...
}

