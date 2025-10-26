// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"

#include "CollectableItem.generated.h"

UENUM(BlueprintType)
enum class CollectableType : uint8
{
	Diamond,
	HealthPotion,
	DoubleJumpUpgrade,
};

UCLASS()
class CRUSTYPIRATE_API ACollectableItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectableItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* ItemFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CollectableType Type;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FrameSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
