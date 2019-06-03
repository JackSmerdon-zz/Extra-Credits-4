// Fill out your copyright notice in the Description page of Project Settings.

#include "TerrainCollision.h"
#include "WorldGenerator.h"
#include "EngineUtils.h"

// Sets default values
ATerrainCollision::ATerrainCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATerrainCollision::BeginPlay()
{
	Super::BeginPlay();

	//iterate through the world, looking for the world generator actor
	for (TActorIterator<AWorldGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr)
		{
			worldGenerator = *ActorItr;
			break;
		}
	}

	float scale = worldGenerator->getCitySize();
	SetActorRelativeScale3D(FVector(scale, 1.0f, scale));
}

// Called every frame
void ATerrainCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}