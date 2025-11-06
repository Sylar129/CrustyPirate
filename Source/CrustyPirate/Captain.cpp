// Fill out your copyright notice in the Description page of Project Settings.

#include "Captain.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ACaptain::ACaptain()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionBox"));
	AttackCollisionBox->SetupAttachment(RootComponent);
}

void ACaptain::BeginPlay()
{
	Super::BeginPlay();

	if (auto* PlayerController = Cast<APlayerController>(Controller))
	{
		if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ACaptain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACaptain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACaptain::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACaptain::JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACaptain::JumpEnded);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &ACaptain::JumpEnded);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ACaptain::Attack);
	}
}

void ACaptain::Move(const FInputActionValue& Value)
{

	float	MoveActionValue = Value.Get<float>();
	FVector Direction(1, 0, 0);
	AddMovementInput(Direction, MoveActionValue);

	FRotator CurrentRotation = Controller->GetControlRotation();
	if (MoveActionValue < 0)
	{
		if (CurrentRotation.Yaw != 180.0f)
		{
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch, 180.0f, CurrentRotation.Roll));
		}
	}
	else if (MoveActionValue > 0)
	{
		if (CurrentRotation.Yaw != 0.0f)
		{
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch, 0.0f, CurrentRotation.Roll));
		}
	}
}

void ACaptain::JumpStarted(const FInputActionValue& Value)
{
	Jump();
}

void ACaptain::JumpEnded(const FInputActionValue& Value)
{
	StopJumping();
}

void ACaptain::Attack(const FInputActionValue& Value) {}

void ACaptain::AttackBoxOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FrameSweep, const FHitResult& SweepResult) {}

void ACaptain::EnableAttackCollisionBox(bool Enabled) {}
