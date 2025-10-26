// Fill out your copyright notice in the Description page of Project Settings.

#include "CrustyPirateGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UCrustyPirateGameInstance::SetHP(int NewHP)
{
	PlayerHP = NewHP;
}

void UCrustyPirateGameInstance::AddDiamond(int Amount)
{
	CollectedDiamonds += Amount;
}

void UCrustyPirateGameInstance::ChangeLevel(int LevelIndex)
{
	if (LevelIndex <= 0)
	{
		return;
	}

	CurrentLevelIndex = LevelIndex;
	UGameplayStatics::OpenLevel(GetWorld(), *FString::Printf(TEXT("Level_%d"), CurrentLevelIndex));
}

void UCrustyPirateGameInstance::RestartGame()
{
	PlayerHP = 100;
	CollectedDiamonds = 0;
	IsDoubleJumpUnlocked = false;
	ChangeLevel(1);
}
