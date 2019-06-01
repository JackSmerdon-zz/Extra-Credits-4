// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Building.h"
#include "Road.h"
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
	AActor* SpawnTile(int8 tileType, int8 tileIndex, FVector position, FRotator rotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> Roads;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> Buildings;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UWorld* world;
	static const int16 offset = 1550;
	static const int8 percentageBuildings = 40;
	static const int8 citySize = 15;
	AActor* levelMap[citySize][citySize];
};
