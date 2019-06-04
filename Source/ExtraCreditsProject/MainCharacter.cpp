// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MainCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraSpringArm"));
	MainCameraSpringArm->SetupAttachment(RootComponent);
	MainCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f));
	MainCameraSpringArm->TargetArmLength = 3000.f;
	MainCameraSpringArm->bUsePawnControlRotation = false;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(MainCameraSpringArm, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;

	playerModule = CreateDefaultSubobject<UPlayerWifiModule>(TEXT("PlayerWifi"));

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Set default walking speed
	defaultWalkingSpeed = GetCharacterMovement()->MaxWalkSpeed;

	ConstructorHelpers::FObjectFinder<USoundCue> footstepSlowSoundCue(TEXT(" '/Game/Sounds/Raw/FootstepSlow_Cue'"));
	ConstructorHelpers::FObjectFinder<USoundCue> footstepFastSoundCue(TEXT(" '/Game/Sounds/Raw/FootstepFast_Cue'"));
	FootstepSlowCue = footstepSlowSoundCue.Object;
	FootstepFastCue = footstepFastSoundCue.Object;
	FootstepAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FootstepComp"));
	FootstepAudioComponent->bAutoActivate = false;
	FootstepAudioComponent->AutoAttachParent;
}

void AMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (FootstepSlowCue->IsValidLowLevel())
	{
		FootstepAudioComponent->SetSound(FootstepSlowCue);
	}
}


// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	FootstepAudioComponent->Play();

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector target;
	target.X = forwardMovement;
	target.Y = strafeMovement;
	target += this->GetActorLocation();
	FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), target);
	SetActorRotation(PlayerRot, ETeleportType::None);

	if (XMoving)
		FootstepAudioComponent->SetPaused(false);
	else if (YMoving)
		FootstepAudioComponent->SetPaused(false);
	else
		FootstepAudioComponent->SetPaused(true);


}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveStrafe", this, &AMainCharacter::MoveStrafe);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::StopSprint);
}

void AMainCharacter::MoveForward(float Value)
{
	//FootstepAudioComponent->Stop();
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}
	forwardMovement = Value;
	if (Value >= 1.f)
		YMoving = true;
	else if (Value <= -1.f)
		YMoving = true;
	else
		YMoving = false;
}

void AMainCharacter::MoveStrafe(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
	strafeMovement = Value;
	if (Value >= 0.1f)
		XMoving = true;
	else if (Value <= -0.1f)
		XMoving = true;
	else
		XMoving = false;
}

void AMainCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = defaultWalkingSpeed * sprintVal;
	FootstepAudioComponent->SetSound(FootstepFastCue);
}

void AMainCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = defaultWalkingSpeed;
	FootstepAudioComponent->SetSound(FootstepSlowCue);
}
