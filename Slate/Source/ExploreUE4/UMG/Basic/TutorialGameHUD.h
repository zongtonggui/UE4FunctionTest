// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ObjectMacros.h"
#include "TutorialGameHUD.generated.h"


/**
 * 
 */
class STutorialGameHUDUI;
UCLASS()
class EXPLOREUE4_API ATutorialGameHUD : public AHUD
{
	GENERATED_BODY()
	
public: 
	
	virtual void PostInitializeComponents() override;

public: 
	 TSharedPtr<STutorialGameHUDUI> GameHUDUI;
	
};
