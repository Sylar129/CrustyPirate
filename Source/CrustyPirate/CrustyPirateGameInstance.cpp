// Fill out your copyright notice in the Description page of Project Settings.

#include "CrustyPirateGameInstance.h"

void UCrustyPirateGameInstance::SetHP(int NewHP)
{
	PlayerHP = NewHP;
}

void UCrustyPirateGameInstance::AddDiamond(int Amount)
{
	CollectedDiamonds += Amount;
}
