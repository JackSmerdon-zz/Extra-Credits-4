// Fill out your copyright notice in the Description page of Project Settings.


#include "wifi_component.h"

// Sets default values for this component's properties
Uwifi_component::Uwifi_component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void Uwifi_component::setMaxWifiHealth(float f)
{
	maxWifiHealth = f;
	wifiHealth = f;
}

// Called when the game starts
void Uwifi_component::BeginPlay()
{
	Super::BeginPlay();

	myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(myCharacter != nullptr) player = myCharacter->FindComponentByClass<UPlayerWifiModule>();
	DrawDebugSphere(GetWorld(), this->GetOwner()->GetActorLocation(), wifiRange, 26, FColor(0, 255, 0), true, -1, 0, 0);
}

// Called every frame
void Uwifi_component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	distance = FVector::Dist(myCharacter->GetActorLocation(), this->GetOwner()->GetActorLocation());

	if (distance <= wifiRange) {
		if (player != nullptr) {
			wifiHealth -= depletion * DeltaTime;
			if(wifiHealth > 0)
				player->WithinWifiRange(-depletion);
		}
	}
	else {
		if (wifiHealth < maxWifiHealth) wifiHealth += (depletion * DeltaTime) / 10;
	}
	// ...
}

