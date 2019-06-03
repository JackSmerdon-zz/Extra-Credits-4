

#include "Public/PlayerWifiModule.h"
// Sets default values for this component's properties
UPlayerWifiModule::UPlayerWifiModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UPlayerWifiModule::addWifiToList(FVector comp)
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

void UPlayerWifiModule::removeWifiFromList(FVector comp)
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
					if (FVector::Dist(nearbyWifiComponents[j], this->GetOwner()->GetActorLocation()) > FVector::Dist(nearbyWifiComponents[j + 1], this->GetOwner()->GetActorLocation()))
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

	if (nearbyWifiComponents.Num() > 0) {
		nearestWifiComponentDistance = FVector::Dist(this->GetOwner()->GetActorLocation(), nearbyWifiComponents[0]);

		wifiPercentage = nearestWifiComponentDistance / maxWifiSignalRange;
	}
	else 
	{
		wifiPercentage = 0.0f;
	}
	// ...
}

