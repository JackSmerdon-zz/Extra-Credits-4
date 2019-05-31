// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class EXTRACREDITSPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	//first person camera prototype
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
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

	//returns the first person camera subobject
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
