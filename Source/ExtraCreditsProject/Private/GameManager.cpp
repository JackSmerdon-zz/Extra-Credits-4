// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/GameManager.h"
#include "Public/GameTime.h"
#include "Public/ManageDownloads.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	gameTime = CreateDefaultSubobject<UGameTime>(TEXT("GameTime"));
	manageDownloads = CreateDefaultSubobject<UManageDownloads>(TEXT("ManageDownloads"));
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}