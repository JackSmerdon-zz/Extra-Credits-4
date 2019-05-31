// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Public/PlayerWifiModule.h"
#include "wifi_component.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTRACREDITSPROJECT_API Uwifi_component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Uwifi_component();

	void setWifiRange(float f) { wifiRange = f; }
	const float getWifiRange() { return wifiRange; }
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float wifiRange = 20.0f;
	UPROPERTY(EditAnywhere)
	class UPlayerWifiModule *player;
	UPROPERTY(EditAnywhere)
	float depletion = 0.1f;
	ACharacter* myCharacter;

	float distance = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
