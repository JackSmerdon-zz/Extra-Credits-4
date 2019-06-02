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
	generateWorld();
	correctTiles();
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldGenerator::oldGenerateWorld()
{
	for (uint8 x = 0; x < citySize; x++)
	{
		for (uint8 y = 0; y < citySize; y++)
		{
			uint8 centre = (citySize - 1) / 2;
			//Prevents spawning on fountain block
			if (x == centre && y == centre)
			{
				levelMap[x][y] = SpawnTile(1, 0, FVector(0, 0, 0), FRotator(0, 0, 0));
				continue;
			}

			else
			{
				//Calculates offset based on city size so blocks spawn around the centre
				int8 xOff = x - centre;
				int8 yOff = y - centre;

				//Determines road or city tile based on distribution percentage
				int8 type = rand() % 100;
				if (type > percentageBuildings)
					type = 0;
				else
					type = 1;

				//Determines variant across all variants of each type
				int8 variant = 0;
				if (type == 0)
				{
					//Road
					variant = rand() % Roads.Num();
				}
				else if (type == 1)
				{
					//Building
					variant = FMath::RandRange(1, Buildings.Num()-1);
				}

				//Populates array with generated tile
				levelMap[x][y] = SpawnTile(type, variant, FVector(offset*xOff, offset*yOff, 0), FRotator(0, 90, 0));
			}
		}
	}
}

void AWorldGenerator::generateWorld()
{
	genBuildings();
	genRoads();
	genLowFreq();
}

void AWorldGenerator::genBuildings()
{
	for (uint8 x = 0; x < citySize; x++)
	{
		for (uint8 y = 0; y < citySize; y++)
		{
			uint8 centre = (citySize - 1) / 2;
			//Prevents spawning on fountain block
			if (x == centre && y == centre)
			{
				levelMap[x][y] = SpawnTile(1, 0, FVector(0, 0, 0), FRotator(0, 0, 0));
				continue;
			}

			else
			{
				//Calculates offset based on city size so blocks spawn around the centre
				int8 xOff = x - centre;
				int8 yOff = y - centre;

				//Determines variant across all variants of each type
				int8 variant = FMath::RandRange(2, Buildings.Num() - 1);
				int angle = FMath::RandRange(0, 4);

				//Populates array with generated tile
				levelMap[x][y] = SpawnTile(1, variant, FVector(offset*xOff, offset*yOff, 0), FRotator(0, 90*angle, 0));
			}
		}
	}
}

void AWorldGenerator::genParks()
{

}

void AWorldGenerator::genRoads()
{
	int numRoads = (int)citySize / 3;
	//int numRoads = 2;
	TArray<FVector2D> roadPoints;
	for (int i = 0; i < numRoads; i++)
	{
		roadPoints.Add(FVector2D(FMath::RandRange(1, citySize-1), FMath::RandRange(1, citySize-1)));
	}

	for (int i = 0; i < roadPoints.Num(); i++)
	{
		if (i == roadPoints.Num() - 1)
			continue;

		auto replace = [&](FVector2D vec)
		{
			FVector pos = levelMap[(int)vec.X][(int)vec.Y]->GetActorLocation();
			levelMap[(int)vec.X][(int)vec.Y]->Destroy();
			levelMap[(int)vec.X][(int)vec.Y] = SpawnTile(0, 0, pos, FRotator(0, 0, 0));
		};

		FVector2D current = roadPoints[i];
		FVector2D goal = roadPoints[i + 1];

		replace(current);
	
		while (current != goal)
		{
			int x = 0, y = 0;

			if (current.X < goal.X) x++;
			else if (current.X > goal.X) x--;
			else if (current.Y < goal.Y) y++;
			else if (current.Y > goal.Y) y--;

			/*if (x != 0)
			{

			}*/


			current.X += x;
			current.Y += y;
			replace(current);
		}
	}
}

void AWorldGenerator::genLowFreq()
{

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
			tile->Tags.Add(FName("Road"));
			break;
		}
		case 1:
		{
			//Building
			tile = world->SpawnActor<ABuilding>(Buildings[tileIndex], position, rotation, spawnParams);
			tile->Tags.Add(FName("Building"));
			break;
		}
	}
	return tile;
}

void AWorldGenerator::correctTiles()
{
	for (uint8 x = 0; x < citySize; x++)
	{
		for (uint8 y = 0; y < citySize; y++)
		{
			if (levelMap[x][y] != nullptr)
			{
				if (levelMap[x][y]->ActorHasTag("Building"))
				{
					//print("Skipping Building..");
					continue;
				}
				else
				{
					if (x == 7 && y == 7)
						continue;

					auto out_of_bounds = [] (FVector2D vec)
					{
						bool fail = false;

						if (vec.X < 0 || vec.X > citySize-1 || vec.Y < 0 || vec.Y > citySize-1)
							fail = true;

						return fail;
					};

					FVector2D current(x, y), north(x, y + 1), east(x + 1, y), south(x, y - 1), west(x - 1, y);
					bool northRoad = false, eastRoad = false, southRoad = false, westRoad = false;
					int8 idx = 0;

					if (!out_of_bounds(north))
					{
						if (levelMap[(int)north.X][(int)north.Y]->ActorHasTag("Road"))
						{
							northRoad = true;
							idx++;
						}

					}

					if (!out_of_bounds(east))
					{
						if (levelMap[(int)east.X][(int)east.Y]->ActorHasTag("Road"))
						{
							eastRoad = true;
							idx++;
						}

					}

					if (!out_of_bounds(south))
					{
						if (levelMap[(int)south.X][(int)south.Y]->ActorHasTag("Road"))
						{
							southRoad = true;
							idx++;
						}
					}

					if (!out_of_bounds(west))
					{
						if (levelMap[(int)west.X][(int)west.Y]->ActorHasTag("Road"))
						{
							westRoad = true;
							idx++;
						}
					}

					FVector pos = levelMap[x][y]->GetActorLocation();
					levelMap[x][y]->Destroy();
					int rot = 0;

					switch(idx)
					{
						case 0:
						{
							//Help
							break;
						}
						case 1:
						{
							//End
							
							if (northRoad) rot = -90;
							if (eastRoad)  rot = 180;
							if (southRoad) rot = 90;
							if (westRoad)  rot = 0;

							levelMap[x][y] = world->SpawnActor<ARoad>(Roads[5], pos, FRotator(0,rot,0));
							levelMap[x][y]->Tags.Add(FName("Road"));
							break;
						}
						case 2:
						{
							//Straight

							if (northRoad && southRoad || eastRoad && westRoad)
							{
								if (northRoad && southRoad) rot = 90;
								if (eastRoad && westRoad) rot = 0;

								int var = rand() % 100;
								if (var < 50)
									var = 0;
								else if (var < 75)
									var = 1;
								else
									var = 2;

								if (var > 2)
									var = 2;

								levelMap[x][y] = world->SpawnActor<ARoad>(Roads[var], pos, FRotator(0, rot, 0));
								levelMap[x][y]->Tags.Add(FName("Road"));
								break;

							}

							else
							{
								if (northRoad && eastRoad) rot = -90;
								if (eastRoad && southRoad) rot = 180;
								if (southRoad && westRoad) rot = 90;
								if (westRoad && northRoad) rot = 0;

								levelMap[x][y] = world->SpawnActor<ARoad>(Roads[4], pos, FRotator(0, rot, 0));
								levelMap[x][y]->Tags.Add(FName("Road"));
								break;
							}
						}
						case 3:
						{
							//T
							if (!northRoad) rot = 0;
							if (!eastRoad)  rot = -90;
							if (!southRoad) rot = 180;
							if (!westRoad)  rot = 90;

							levelMap[x][y] = world->SpawnActor<ARoad>(Roads[6], pos, FRotator(0, rot, 0));
							levelMap[x][y]->Tags.Add(FName("Road"));
							break;
						}
						case 4:
						{
							//Cross
							levelMap[x][y] = world->SpawnActor<ARoad>(Roads[3], pos, FRotator(0, 0, 0));
							levelMap[x][y]->Tags.Add(FName("Road"));
							break;
						}
					}
				}
			}
		}
	}
}