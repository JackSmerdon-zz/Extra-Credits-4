// Fill out your copyright notice in the Description page of Project Settings.

#include "ManageDownloads.h"

// Sets default values for this component's properties
UManageDownloads::UManageDownloads()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UManageDownloads::BeginPlay()
{
	Super::BeginPlay();	

	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (player != nullptr) wifiComponent = player->FindComponentByClass<UPlayerWifiModule>();
}


// Called every frame
void UManageDownloads::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	timer += DeltaTime;
	if (timer >= 1.0f)
	{
		timeRemaining--;
		timer = 0.0f;
	}

	//update the current download percent of the files
	if (wifiComponent->getWifiPercent() > minDownloadStrength)
	{
		currentDownloadSpeed = maxDownloadSpeed * wifiComponent->getWifiPercent();
		downloadPercent += (currentDownloadSpeed / (1.0f / maxDownloadSpeed)) * DeltaTime;
	}

	//download has finished
	if (downloadPercent >= 1.0f)
	{
		numOfFilesDownloaded++;
		downloadPercent = 0.0f;
	}

	//if the player has run out of time...
	if (timeRemaining == 0)
	{

	}
}