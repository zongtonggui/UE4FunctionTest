// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialGameHUD.h"
#include "Engine/Engine.h"
#include "DeclarativeSyntaxSupport.h"
#include "DataBind_Test/TutorialGameHUDUI.h"
#include "SWeakWidget.h"
#include "Engine/GameViewportClient.h"




void ATutorialGameHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (GEngine && GEngine->GameViewport)
	{
		UGameViewportClient* Viewport = GEngine->GameViewport;
		
		SAssignNew(GameHUDUI, STutorialGameHUDUI).OwnerHUD(this);
		Viewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(GameHUDUI.ToSharedRef())
		);
	}
}
