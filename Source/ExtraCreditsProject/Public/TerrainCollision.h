// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainCollision.generated.h"

UCLASS()
class EXTRACREDITSPROJECT_API ATerrainCollision : public AActor
{
	GENERATED_BODY()

private:
	class AWorldGenerator* worldGenerator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Sets default values for this actor's properties
	ATerrainCollision();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
