// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WidgetGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EXPLOREUE4_API AWidgetGameMode : public AGameModeBase
{
	GENERATED_BODY()
	AWidgetGameMode();
public:
	
	
protected:
	virtual void BeginPlay() override;

};
