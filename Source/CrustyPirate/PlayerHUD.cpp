// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"

void UPlayerHUD::SetHP(int NewHP)
{
	HPText->SetText(FText::FromString(FString::Printf(TEXT("HP: %d"), NewHP)));
}

void UPlayerHUD::SetDiamonds(int Amount)
{
	DiamondsText->SetText(FText::FromString(FString::Printf(TEXT("Diamonds: %d"), Amount)));
}

void UPlayerHUD::SetLevel(int Index)
{
	LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), Index)));
}
