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

void AWorldGenerator::generateWorld()
{
	genBuildings();
	genParks();
	genRoads();
	genLowFreq();
}

void AWorldGenerator::genBuildings()
{
	for (uint8 x = 0; x < citySize; x++)
	{
		for (uint8 y = 0; y < citySize; y++)
		{
			//Calculate centre tile
			uint8 centre = (citySize - 1) / 2;

			//Calculates offset based on city size so blocks spawn around the centre
			int8 xOff = x - centre;
			int8 yOff = y - centre;

			//Determines variant across all variants of each type
			int8 variant = FMath::RandRange(1, Buildings.Num() - 1);
			int angle = FMath::RandRange(0, 4);

			//Populates array with generated tile
			levelMap[x][y] = SpawnTile(1, variant, FVector(offset*xOff, offset*yOff, 0), FRotator(0, 90 * angle, 0));
		}
	}
}

void AWorldGenerator::genParks()
{
	int numParks = 5;
	TArray<FVector2D> parkOrigins;

	for (int i = 0; i < numParks; i++)
	{
		FVector2D newPoint = FVector2D(FMath::RandRange(1, citySize - 1), FMath::RandRange(1, citySize - 1));
		while(tooClose(parkOrigins, newPoint, 6, parkOrigins.Num()))
			newPoint = FVector2D(FMath::RandRange(1, citySize - 1), FMath::RandRange(1, citySize - 1));
		parkOrigins.Add(newPoint);
	}

	for (int i = 0; i < parkOrigins.Num(); i++)
	{
		for (int x = parkOrigins[i].X - FMath::RandRange(3, 5); x < parkOrigins[i].X + FMath::RandRange(3, 5); x++)
		{
			for (int y = parkOrigins[i].Y - FMath::RandRange(3, 5); y < parkOrigins[i].Y + FMath::RandRange(3, 5); y++)
			{
				if (x < 0 || x > citySize - 1 || y < 0 || y > citySize - 1)
					continue;
				replace(FVector2D(x,y), 2, FMath::RandRange(0, Parks.Num() - 1), FMath::RandRange(0, 4));
				int nextLine = FMath::RandRange(0, 100);
				if (nextLine > 95)
					break;
			}
		}
	}
}

bool AWorldGenerator::tooClose(TArray<FVector2D>& points, FVector2D vec, int boundary, int8 numPoints)
{
	for (int i = 0; i < numPoints; i++)
	{
		if (abs(vec.X - points[i].X) < boundary || abs(vec.Y - points[i].Y) < boundary)
			return true;
	}
	return false;
}

void AWorldGenerator::replace(FVector2D vec, int tileType, int tileVariant, int angle)
{
	FVector pos = levelMap[(int)vec.X][(int)vec.Y]->GetActorLocation();
	levelMap[(int)vec.X][(int)vec.Y]->Destroy();
	levelMap[(int)vec.X][(int)vec.Y] = SpawnTile(tileType, tileVariant, pos, FRotator(0, 90 * angle, 0));
}

void AWorldGenerator::genRoads()
{
	TArray<FVector2D> roadPoints;

	//Calculate how many roads to make
	int numRoads = citySize / 2;

	//Calculate centre point
	uint8 centre = (citySize - 1) / 2;

	//Add centre as start for first road
	roadPoints.Add(FVector2D(centre, centre));

	for (int i = 0; i < numRoads; i++)
	{
		//Generate a new point somewhere within the city grid
		FVector2D newPoint = FVector2D(FMath::RandRange(1, citySize - 1), FMath::RandRange(1, citySize - 1));
		roadPoints.Add(newPoint);
	}

	for (int i = 0; i < roadPoints.Num(); i++)
	{
		//There is nowhere for the last point to link to, so it is omitted
		if (i == roadPoints.Num() - 1)
			continue;

		//Road is generated between the current point and the next point in the array
		FVector2D current = roadPoints[i];
		FVector2D goal = roadPoints[i + 1];

		replace(current, 0, 0);
		bool changeDirection = false;

		while (current != goal)
		{
			int x = 0, y = 0;

			//35% chance to change direction - stops the roads from being completely straight
			int axis = FMath::RandRange(0, 100);
			if (axis > 65) changeDirection = !changeDirection;


			if (changeDirection)
			{
				if (current.X < goal.X) x++;
				else if (current.X > goal.X) x--;
				else if (current.Y < goal.Y) y++;
				else if (current.Y > goal.Y) y--;
			}
			else
			{
				if (current.Y < goal.Y) y++;
				else if (current.Y > goal.Y) y--;
				else if (current.X < goal.X) x++;
				else if (current.X > goal.X) x--;
			}

			current.X += x;
			current.Y += y;

			//Bounds checking
			if (current.X > citySize - 1) current.X = citySize - 1;
			if (current.X < 0) current.X = 0;
			if (current.Y > citySize - 1) current.Y = citySize - 1;
			if (current.Y < 0) current.Y = 0;

			replace(current, 0, 0);
		}
	}
}

void AWorldGenerator::genLowFreq()
{
	for (int i = 0; i < citySize/5; i++)
	{
		bool valid = false;
		FVector2D newPoint;
		while (!valid)
		{
			newPoint = FVector2D(FMath::RandRange(1, citySize - 1), FMath::RandRange(1, citySize - 1));
			if (!levelMap[(int)newPoint.X][(int)newPoint.Y]->ActorHasTag("Road"))
			{
				for (int x = newPoint.X - 1; x < newPoint.X + 1; x++)
				{
					for (int y = newPoint.Y - 1; y < newPoint.Y + 1; y++)
					{
						if (x < 0 || x > citySize - 1 || y < 0 || y > citySize - 1)
							continue;

						if (levelMap[x][y]->ActorHasTag("Road"))
							valid = true;
					}
				}
			}
		}
		replace(newPoint, 0, 7, FMath::RandRange(0, 4));
	}

	TArray<FVector2D> cafes;
	for (int i = 0; i < internetCafeCount; i++)
	{
		FVector2D newPoint = FVector2D(FMath::RandRange(1, citySize - 1), FMath::RandRange(1, citySize - 1));
		while (tooClose(cafes, newPoint, 2, cafes.Num()))
			newPoint = FVector2D(FMath::RandRange(1, citySize - 1), FMath::RandRange(1, citySize - 1));
		cafes.Add(newPoint);
	}
	for(int i = 0; i < cafes.Num(); i++)
		replace(cafes[i], 3, 0, FMath::RandRange(0, 4));
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
	case 2:
	{
		//Park
		tile = world->SpawnActor<APark>(Parks[tileIndex], position, rotation, spawnParams);
		tile->Tags.Add(FName("Park"));
		break;

	}
	case 3:
	{
		//Infrequent
		tile = world->SpawnActor<ABuilding>(Infrequent[tileIndex], position, rotation, spawnParams);
		tile->Tags.Add(FName("Infrequent"));
		break;
	}
	}
	return tile;
}

void AWorldGenerator::removeThickRoads()
{
	for (int x = 0; x < citySize; x++)
	{
		for (int y = 0; y < citySize; y++)
		{
			if (!levelMap[x][y]->ActorHasTag("Road"))
				continue;

			if(x+1 > citySize-1 || y+1 > citySize-1)
				continue;

			bool current = levelMap[x][y]->ActorHasTag("Road");
			bool right = levelMap[x + 1][y]->ActorHasTag("Road");
			bool down = levelMap[x][y + 1]->ActorHasTag("Road");
			bool diag = levelMap[x + 1][y + 1]->ActorHasTag("Road");

			if (current && right && down && diag)
			{
				int8 variant = FMath::RandRange(1, Buildings.Num() - 1);
				int angle = FMath::RandRange(0, 4);

				replace(FVector2D(x + 1, y + 1), 1, variant, angle);
			}
		}
	}
}

void AWorldGenerator::correctTiles()
{
	removeThickRoads();
	for (uint8 x = 0; x < citySize; x++)
	{
		for (uint8 y = 0; y < citySize; y++)
		{
			if (levelMap[x][y] != nullptr)
			{
				if (!levelMap[x][y]->ActorHasTag("Road"))
				{
					//print("Skipping Building..");
					continue;
				}
				if (levelMap[x][y]->ActorHasTag("Petrol Station"))
				{
					continue;
				}
				else
				{
					auto out_of_bounds = [](FVector2D vec)
					{
						bool fail = false;

						if (vec.X < 0 || vec.X > citySize - 1 || vec.Y < 0 || vec.Y > citySize - 1)
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

					switch (idx)
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

						levelMap[x][y] = world->SpawnActor<ARoad>(Roads[5], pos, FRotator(0, rot, 0));
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