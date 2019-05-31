// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "WorldGenerator.h"

// Sets default values
AWorldGenerator::AWorldGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldGenerator::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	SpawnTile(0, 0, FVector(250, 0, 250), FRotator(0,0,0));
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldGenerator::SpawnTile(int8 tileType, int8 tileIndex, FVector position, FRotator rotation)
{
	FActorSpawnParameters spawnParams;

	switch (tileType)
	{
		case 0:
		{
			//Road
			ARoad* road = world->SpawnActor<ARoad>(Roads[tileIndex], position, rotation, spawnParams);
			break;
		}
		case 1:
		{
			//Building
			break;
		}
	}
}