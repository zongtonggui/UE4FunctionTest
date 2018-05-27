// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoLayoutUI.h"
#include <DeclarativeSyntaxSupport.h>
#include <PanelSlot.h>
#include "AutoLayoutSlot.h"
#include <UObjectGlobals.h>




UAutoLayoutUI::UAutoLayoutUI(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

const FText UAutoLayoutUI::GetPaletteCategory()
{
	return FText::FromString(FString("SanWU"));
}

UClass* UAutoLayoutUI::GetSlotClass() const
{
	return UAutoLayoutUI::StaticClass();
}

void UAutoLayoutUI::OnSlotAdded(UPanelSlot* InSlot)
{
	if (MyAutoLayout.IsValid())
	{
		CastChecked<UAutoLayoutSlot>(InSlot)->BuildSlot(MyAutoLayout.ToSharedRef());

	}
}

void UAutoLayoutUI::OnSlotRemoved(UPanelSlot* InSlot)
{
	if (MyAutoLayout.IsValid())
	{

		TSharedPtr<SWidget> widget = InSlot->Content->GetCachedWidget();
		if (widget.IsValid())
		{
			MyAutoLayout->RemoveSlot(widget.ToSharedRef());
		}
	}
}

void UAutoLayoutUI::ReleaseSlateResources(bool bReaseChildren)
{
	Super::ReleaseSlateResources(bReaseChildren);
}

TSharedRef<SWidget> UAutoLayoutUI::RebuildWidget()
{
	MyAutoLayout = SNew(SAutoLayout).ContentMargin(ContentMargin);
	for (UPanelSlot* PanlSlot : Slots)
	{
		if (UAutoLayoutSlot* TypeSlot=Cast<UAutoLayoutSlot>(PanlSlot))
		{
			TypeSlot->Parent = this;
			TypeSlot->BuildSlot(MyAutoLayout.ToSharedRef());

		}
	}
	return MyAutoLayout.ToSharedRef();
}
