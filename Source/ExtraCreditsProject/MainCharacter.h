// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/PlayerWifiModule.h"
#include "MainCharacter.generated.h"

UCLASS()
class EXTRACREDITSPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:

	float forwardMovement = 0.0f;
	float strafeMovement = 0.0f;

	//camera prototype
	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraComponent* MainCamera;

	//camera boomarm prototype
	UPROPERTY(EditAnywhere, Category = "Camera")
		class USpringArmComponent* MainCameraSpringArm;

	UPROPERTY(EditAnywhere, Category = "Wifi")
		class UPlayerWifiModule * playerModule;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//handles moving forward and back
	void MoveForward(float Val);

	//hadles strafing left and right
	void MoveStrafe(float Val);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Wifi")
	FORCEINLINE class UPlayerWifiModule* getPlayerWifiModule() const { return playerModule; }
};
