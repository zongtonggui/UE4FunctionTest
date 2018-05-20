// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCompoundWidget.h"
#include "../TutorialGameHUD.h"
#include "DeclarativeSyntaxSupport.h"



class EXPLOREUE4_API STutorialGameHUDUI:public SCompoundWidget
{
	SLATE_BEGIN_ARGS(STutorialGameHUDUI) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATutorialGameHUD>, OwnerHUD)

	SLATE_END_ARGS()

public:

	void Construct(const FArguments &args);

public:

	/**
	* Stores a weak reference to the HUD owning this widget.
	**/
	TWeakObjectPtr<ATutorialGameHUD> OwnerHUD;
	/**
	* A reference to the Slate Style used for this HUD's widgets.
	**/
	const struct FGlobalStyle* HUDStyle;

	/**
	* Attribute storing the binding for the player's score.
	**/
	TAttribute<FText> Score;

	/**
	* Attribute storing the binding for the player's health.
	**/
	TAttribute<FText> Health;

	/**
	* Our Score will be bound to this function, which will retrieve the appropriate data and convert it into an FText.
	**/
	FText GetScore() const;

	/**
	* Our Health will be bound to this function, which will retrieve the appropriate data and convert it into an FText.
	**/
	FText GetHealth() const;
};
