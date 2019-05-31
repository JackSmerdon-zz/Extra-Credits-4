// Fill out your copyright notice in the Description page of Project Settings.


#include "wifi_component.h"

// Sets default values for this component's properties
Uwifi_component::Uwifi_component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void Uwifi_component::BeginPlay()
{
	Super::BeginPlay();
	myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(myCharacter != nullptr) player = myCharacter->FindComponentByClass<UPlayerWifiModule>();

}

// Called every frame
void Uwifi_component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	distance = FVector::Dist(myCharacter->GetActorLocation(), this->GetOwner()->GetActorLocation());

	if (distance >= wifiRange) {
		if(player != nullptr) player->WithinWifiRange(depletion);
	}
	// ...
}

