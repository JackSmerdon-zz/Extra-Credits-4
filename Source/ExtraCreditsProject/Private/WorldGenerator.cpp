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
	
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldGenerator::SpawnTile(int8 tileType, int8 tileIndex)
{
	switch (tileType)
	{
		case 0:
		{
			//Road
			world->SpawnActor<RoadBP>();
			break;
		}
		case 1:
		{
			//Building
			break;
		}
	}

	//world->SpawnActor<>


	//world->SpawnActor<ATerrainSegment>(Segments[segmentNum], spawnLocation, spawnRotation, spawnParams);
}