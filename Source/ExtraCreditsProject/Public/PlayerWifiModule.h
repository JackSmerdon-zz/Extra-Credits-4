// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float wifiHealth = 10.0f;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
