// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Public/PlayerWifiModule.h"
#include "wifi_component.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXTRACREDITSPROJECT_API Uwifi_component : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	Uwifi_component();

	void setWifiRange(float f) { wifiRange = f; }
	const float getWifiRange() { return wifiRange; }
	void setDepleteRate(float f) { depletion = f; }
	const float getDepleteRate() { return depletion; }
	void setMaxWifiHealth(float f);
	const float getMaxWifiHealth() { return maxWifiHealth; }
	const float getWifiHealth() { return wifiHealth; }

	const float getWifiDistance() { return distance; }


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "WIFI MODULE")
		float wifiRange = 1500.0f;
	UPROPERTY(EditAnywhere, Category = "WIFI MODULE")
		class UPlayerWifiModule *player;
	UPROPERTY(EditAnywhere, Category = "WIFI MODULE")
		float depletion = 0.2f;
	UPROPERTY(EditAnywhere, Category = "WIFI MODULE")
		float maxWifiHealth = 1.0f;
	UPROPERTY(EditAnywhere, Category = "WIFI MODULE")
		float wifiHealth = 1.0f;
	ACharacter* myCharacter;

	bool isInPlayerList = false;

	float distance = 0.0f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};