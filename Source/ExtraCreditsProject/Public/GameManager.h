// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class EXTRACREDITSPROJECT_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	//camera prototype
	//UPROPERTY(EditAnywhere)
		//class GameTime *gameTime;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Game Time")
		class UGameTime *gameTime;

	UPROPERTY(EditAnywhere, Category = "Manage Downloads")
		class UManageDownloads *manageDownloads;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Game Time")
	FORCEINLINE class UGameTime* getGameTime() const { return gameTime; }

	UFUNCTION(BlueprintCallable, Category = "Downloads")
	FORCEINLINE class UManageDownloads* getManageDownloads() const { return manageDownloads; }
};
