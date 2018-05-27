// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelSlot.h"
#include "AutoLayout.h"
#include "AutoLayoutSlot.generated.h"

/**
 * 
 */
UCLASS()
class UMGEXTERN_API UAutoLayoutSlot : public UPanelSlot
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	void BuildSlot(TSharedRef<SAutoLayout> InAutoLayout);
private:
	SAutoLayout::FSlot* Slot;
	
};
