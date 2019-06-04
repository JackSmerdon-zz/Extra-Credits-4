// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "PlayerWifiModule.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTRACREDITSPROJECT_API UPlayerWifiModule : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerWifiModule();

	const float getWifiHealth(){return wifiHealth;}
	void setWifiHealth(float f) { wifiHealth = f; }
	void addWifiToList(FVector comp);
	void removeWifiFromList(FVector comp);
	void WithinWifiRange(float f);

	UFUNCTION(BlueprintPure, Category = "WIFI Percent")
	float getWifiPercent() { return wifiPercentage;}

	float getMaxWifiRange() { return maxWifiSignalRange; }

	float getCurrentDepleteRate() { return currentDepleteRate; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void deplete(float f);

	void sortWifiArray();

	void noWifi();

	bool hasWifi = false;

	UPROPERTY(EditAnywhere, Category = "Points")
	float wifiHealth = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Points")
	float defaultDepleteRate = 0.03f;
	UPROPERTY(EditAnywhere, Category = "Points")
	float currentDepleteRate = 0.03f;

	UPROPERTY(EditAnywhere, Category = "Points")
	float maxWifiSignalRange = 10000.0f;

	TArray<FVector> nearbyWifiComponents;

	float nearestWifiComponentDistance = 0.0f;

	float wifiPercentage = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
