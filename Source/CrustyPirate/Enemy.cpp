// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "Components/SphereComponent.h"
#include "PaperZDAnimInstance.h"
#include "PlayerCharacter.h"
#include "Components/TextRenderComponent.h"

AEnemy::AEnemy()
{
	PlayerDetectorSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectorSphere"));
	PlayerDetectorSphere->SetupAttachment(RootComponent);

	HPText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HPText"));
	HPText->SetupAttachment(RootComponent);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerDetectorSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::DetectorOverlapBegin);
	PlayerDetectorSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::DetectorOverlapEnd);

	UpdateHP(HitPoints);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAlive && FollowTarget)
	{
		float MoveDirection = (FollowTarget->GetActorLocation().X - GetActorLocation().X) > 0 ? 1 : -1;
		UpdateDirection(MoveDirection);
		if (ShouldMoveToTarget())
		{
			if (CanMove)
			{
				FVector WorldDirection(1, 0, 0);
				AddMovementInput(WorldDirection, MoveDirection);
			}
		}
		else
		{
			// attack
		}
	}
}

void AEnemy::TakeDamage(int DamageAmount, float StunDuration)
{
	if (!IsAlive)
	{
		return;
	}

	UpdateHP(HitPoints - DamageAmount);

	if (HitPoints > 0)
	{
		IsAlive = true;
		GetAnimInstance()->JumpToNode(FName("JumpTakeHit"), FName("CrabbyStateMachine"));
	}
	else
	{
		IsAlive = false;
		CanMove = false;
		UpdateHP(0);
		HPText->SetHiddenInGame(true);

		GetAnimInstance()->JumpToNode(FName("JumpDie"), FName("CrabbyStateMachine"));
	}
}

void AEnemy::DetectorOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FrameSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		FollowTarget = Player;
	}
}

void AEnemy::DetectorOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		FollowTarget = nullptr;
	}
}

bool AEnemy::ShouldMoveToTarget() const
{
	bool Result = false;

	if (FollowTarget)
	{
		float DistanceToTarget = std::abs(FollowTarget->GetActorLocation().X - GetActorLocation().X);
		Result = DistanceToTarget > StopDistanceToTarget;
	}

	return Result;
}

void AEnemy::UpdateDirection(float MoveDirection)
{
	FRotator CurrentRotation = GetActorRotation();
	if (MoveDirection < 0)
	{
		if (CurrentRotation.Yaw != 180.0f)
		{
			SetActorRotation(FRotator(CurrentRotation.Pitch, 180.0f, CurrentRotation.Roll));
		}
	}
	else if (MoveDirection > 0)
	{
		if (CurrentRotation.Yaw != 0.0f)
		{
			SetActorRotation(FRotator(CurrentRotation.Pitch, 0.0f, CurrentRotation.Roll));
		}
	}
}

void AEnemy::UpdateHP(int NewHP)
{
	HitPoints = NewHP;

	FString Str = FString::Printf(TEXT("HP: %d"), HitPoints);
	HPText->SetText(FText::FromString(Str));
}
