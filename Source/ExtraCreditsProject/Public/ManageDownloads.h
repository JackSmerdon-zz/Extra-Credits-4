// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Public/PlayerWifiModule.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "ManageDownloads.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTRACREDITSPROJECT_API UManageDownloads : public UActorComponent
{
	GENERATED_BODY()

private:
	float downloadPercent = 0.0f;
	int32 numOfFilesDownloaded = 0;
	float currentDownloadSpeed = 0.0f;
	float timer = 0.0f;

	class ACharacter *player;
	class UPlayerWifiModule *wifiComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//the download speed the player will get if they have full signal strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Downloads")
	float maxDownloadSpeed = 0.3f;

	//the time remaining in the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Downloads")
	int32 timeRemaining = 30;

public:	
	// Sets default values for this component's properties
	UManageDownloads();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Downloads")
	FORCEINLINE int32 getTimeRemaining() const { return timeRemaining; }

	UFUNCTION(BlueprintPure, Category = "Downloads")
	FORCEINLINE FString getDownloadPercentAsFormattedText() const { return FString(FString::FromInt(downloadPercent * 100) + "%"); }

	UFUNCTION(BlueprintPure, Category = "Downloads")
	FORCEINLINE float getDownloadPercent() const { return downloadPercent; }

	UFUNCTION(BlueprintPure, Category = "Downloads")
	FORCEINLINE int32 getNumOfFilesDownloaded() const { return numOfFilesDownloaded; }
};