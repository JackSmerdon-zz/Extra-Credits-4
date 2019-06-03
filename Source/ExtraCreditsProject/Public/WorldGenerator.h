// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/Engine.h"
#include "Building.h"
#include "Road.h"
#include "Park.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGenerator.generated.h"


UCLASS()
class EXTRACREDITSPROJECT_API AWorldGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> Roads;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> Buildings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> Parks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> Infrequent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "World Generation")
		uint8 getCitySize() { return citySize; };
	UFUNCTION(BlueprintCallable, Category = "World Generation")
		int32 getOffset() { return offset; };
	UFUNCTION(BlueprintCallable, Category = "World Generation")
		void setCafeCount(uint8 cafeCount) { internetCafeCount = cafeCount; };

private:
	UWorld* world;
	static const int16 offset = 1550;
	static const uint8 citySize = 45;
	uint8 internetCafeCount = 15;
	AActor* levelMap[citySize][citySize];

	AActor* SpawnTile(int8 tileType, int8 tileIndex, FVector position, FRotator rotation);
	void removeThickRoads();
	void correctTiles();

	void generateWorld();
	void genBuildings();
	void genParks();
	void genRoads();
	void genLowFreq();

	bool tooClose(TArray<FVector2D>& points, FVector2D vec, int boundary, int8 numPoints);
	void replace(FVector2D vec, int tileType, int tileVariant, int angle = 0);
};