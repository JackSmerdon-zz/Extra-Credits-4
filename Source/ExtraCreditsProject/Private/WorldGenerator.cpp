// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "Public/WorldGenerator.h"

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

	for (uint8 x = 0; x < citySize; x++)
	{
		for (uint8 y = 0; y < citySize; y++)
		{
			if (x == ((citySize - 1) / 2) && y == ((citySize - 1) / 2))
				continue;
			else
			{
				int8 xOff = x - ((citySize - 1) / 2);
				int8 yOff = y - ((citySize - 1) / 2);

				int8 type = rand() % 100;
				if (type > percentageBuildings)
					type = 0;
				else
					type = 1;

				int8 variant = 0;
				if (type == 0)
				{
					//Road
					variant = rand() % Roads.Num();
				}
				else if (type == 1)
				{
					//Building
					variant = rand() % Buildings.Num();
				}

				levelMap[x][y] = SpawnTile(type, variant, FVector(offset*xOff, offset*yOff, 0), FRotator(0, 90, 0));
			}
		}
	}
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AActor* AWorldGenerator::SpawnTile(int8 tileType, int8 tileIndex, FVector position, FRotator rotation)
{
	FActorSpawnParameters spawnParams;
	AActor* tile = NULL;

	switch (tileType)
	{
		case 0:
		{
			//Road
			tile = world->SpawnActor<ARoad>(Roads[tileIndex], position, rotation, spawnParams);
			break;
		}
		case 1:
		{
			//Building
			tile = world->SpawnActor<ABuilding>(Buildings[tileIndex], position, rotation, spawnParams);
			break;
		}
	}
	return tile;
}