// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Engine/TimerHandle.h"
#include "Enemy.generated.h"

class USphereComponent;
class APlayerCharacter;
class UTextRenderComponent;

UCLASS()
class CRUSTYPIRATE_API AEnemy : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	AEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void TakeDamage(int DamageAmount, float StunDuration);

protected:
	UFUNCTION()
	void DetectorOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FrameSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DetectorOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool ShouldMoveToTarget() const;
	void UpdateDirection(float MoveDirection);

	void UpdateHP(int NewHP);

	void Stun(float DurationInSeconds);
	void OnStunTimerTimeout();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* PlayerDetectorSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTextRenderComponent* HPText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APlayerCharacter* FollowTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StopDistanceToTarget = 70.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HitPoints = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsAlive = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsStunned = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	FTimerHandle StunTimer;
};
