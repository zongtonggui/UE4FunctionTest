// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialGameHUDUI.h"
#include "UMG/MenuStyles.h"
#include "DeclarativeSyntaxSupport.h"
#include "SOverlay.h"
#include "STextBlock.h"
#include "UMG/GlobalMenuStyle.h"
#include "../TutGameMode.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void STutorialGameHUDUI::Construct(const FArguments &args)
{
	OwnerHUD = args._OwnerHUD;
	//获取在Eidtor 中定义的Style	
	
	HUDStyle = &(FMenuStyles::Get()->GetWidgetStyle<FGlobalStyle>("Global"));
	//const TSharedPtr<FSlateStyleSet> MyStyleSet = FMenuStyles::Get();
	//HUDStyle = &(MyStyleSet->GetWidgetStyle<FGlobalStyle>("Global"));

	Score.Bind(this, &STutorialGameHUDUI::GetScore);
	Health.Bind(this, &STutorialGameHUDUI::GetHealth);
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.VAlign(EVerticalAlignment::VAlign_Top)
			[
				SNew(STextBlock)
				.TextStyle(&HUDStyle->MenuTitleStyle)
				.Text(Score)
			]
			+ SOverlay::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Right)
			.VAlign(EVerticalAlignment::VAlign_Top)
			[
				SNew(STextBlock)
				.TextStyle(&HUDStyle->MenuTitleStyle)
				.Text(Health)
			]
		];

}

FText STutorialGameHUDUI::GetScore() const
{
	// NOTE: THIS IS A TERRIBLE WAY TO DO THIS. DO NOT DO IT. IT ONLY WORKS ON SERVERS. USE GAME STATES INSTEAD!
	//OwnerHUD->GetWorldSettings()->GetWorld()->GetAuthGameMode()
	
	ATutGameMode* gameMode = Cast<ATutGameMode>(OwnerHUD->GetWorldSettings()->GetWorld()->GetAuthGameMode());

	if (gameMode == nullptr)
		return FText::FromString(TEXT("SCORE: --"));

	FString score = TEXT("SCORE: ");
	score.AppendInt(gameMode->GetScore());

	return FText::FromString(score);
	

	
}

FText STutorialGameHUDUI::GetHealth() const
{
	return FText::FromString("HEALTH: --");
}
