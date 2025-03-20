// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ABlasterCharacter::ABlasterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlasterCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	
	// add default mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			InputSubsystem->AddMappingContext(DeafaultMappingContext, 0);
		}
	}
}

void ABlasterCharacter::StartJumping()
{
	UE_LOG(LogTemp, Warning, TEXT("ABlasterCharacter::StartJump"))
	Jump();
}

void ABlasterCharacter::EndJumping()
{
	UE_LOG(LogTemp, Warning, TEXT("ABlasterCharacter::StopJump"))
	StopJumping();
}

void ABlasterCharacter::Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("ABlasterCharacter::Move - %s"), *Value.ToString())

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRoration(0.f, Rotation.Yaw, 0.f);

		// get forward vector
		const FVector ForwarVector = FRotationMatrix(YawRoration).GetUnitAxis(EAxis::X);
		// get right vector
		const FVector RightVector = FRotationMatrix(YawRoration).GetUnitAxis(EAxis::Y);
		// add movement 
		AddMovementInput(ForwarVector, MovementVector.Y);
		AddMovementInput(RightVector, MovementVector.X);
	}
}

void ABlasterCharacter::Look(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("ABlasterCharacter::Look - %s"), *Value.ToString())

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("We have enhanced input component"))
		// jump
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ABlasterCharacter::StartJumping);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABlasterCharacter::EndJumping);
		// move
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::Move);
		// look
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::Look);
	}
}

