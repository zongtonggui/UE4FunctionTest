// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoLayoutSlot.h"
#include <Widget.h>
#include <PanelSlot.h>
#include "AutoLayout.h"




void UAutoLayoutSlot::SynchronizeProperties()
{

}

void UAutoLayoutSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	Slot = NULL;
}

void UAutoLayoutSlot::BuildSlot(TSharedRef<SAutoLayout> InAutoLayout)
{
	Slot = &InAutoLayout->AddSlot()[Content==NULL?SNullWidget::NullWidget:Content->TakeWidget()];
	
}
