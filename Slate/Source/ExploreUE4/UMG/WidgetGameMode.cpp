// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetGameMode.h"
#include "MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"



AWidgetGameMode::AWidgetGameMode()
{
	HUDClass = AMainMenuHUD::StaticClass();
	
}

void AWidgetGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Test = nullptr;
	if (GetWorld())
		Test = GetWorld()->GetFirstPlayerController();
	if (nullptr != Test)
		Test->bShowMouseCursor = true;
}
