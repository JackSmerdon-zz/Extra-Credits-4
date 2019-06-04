// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/PlayerWifiModule.h"
#include "ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "Engine/Classes/Sound/SoundCue.h"
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
	float defaultWalkingSpeed = 0.0f;
	float sprintVal = 5.0f;
	float GTime = 0.0f;
	bool XMoving = false;
	bool YMoving = false;

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

	//handles strafing left and right
	void MoveStrafe(float Val);

	void StartSprint();
	void StopSprint();

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		USoundCue* FootstepCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		UAudioComponent* FootstepAudioComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents();

	UFUNCTION(BlueprintCallable, Category = "Wifi")
	FORCEINLINE class UPlayerWifiModule* getPlayerWifiModule() const { return playerModule; }
};
