// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EngineUtils.h"
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
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class PlayerWifiModule *player;

	AActor* player;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
