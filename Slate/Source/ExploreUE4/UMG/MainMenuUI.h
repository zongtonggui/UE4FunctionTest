// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCompoundWidget.h"
#include "MainMenuHUD.h"
#include "SlateBasics.h"
#include "Reply.h"
#include "DeclarativeSyntaxSupport.h"

/**
 * 
 */
//一个Slate界面，显示在屏幕上
class EXPLOREUE4_API SMainMenuUI : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SMainMenuUI)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, MainMenuHUD)
	
	SLATE_END_ARGS()

	// Constructs and lays out the Main Menu UI Widget.
	// args Arguments structure that contains widget-specific setup information.
	void Construct(const FArguments& args);

	// Click handler for the Play Game! button – Calls MenuHUD’s PlayGameClicked() event.
	FReply PlayGameClicked();

	// Click handler for the Quit Game button – Calls MenuHUD’s QuitGameClicked() event.
	FReply QuitGameClicked();

	// Stores a weak reference to the HUD controlling this class.
	TWeakObjectPtr<class AMainMenuHUD> MainMenuHUD;
	const struct FGlobalStyle* MenuStyle;
};