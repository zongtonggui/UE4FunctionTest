// Fill out your copyright notice in the Description page of Project Settings.

#include "TutGameMode.h"
#include "TutorialGameHUD.h"




ATutGameMode::ATutGameMode()
{
	HUDClass = ATutorialGameHUD::StaticClass();
}

int32 ATutGameMode::GetScore()
{
	return CurrentScore;
}

void ATutGameMode::AddPoints(int32 value)
{
	if (value > 0)
		CurrentScore += value;
}

void ATutGameMode::DeductPoints(int32 value)
{
	if (value > 0)
		CurrentScore =FMath::Max(CurrentScore - value, 0);
}
