// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <SBoxPanel.h>
#include <SharedPointer.h>
#include <SWidget.h>

/**
 * 
 */
class UMGEXTERN_API SAutoLayout:public SBoxPanel
{
public:
	class FSlot :public SBoxPanel::FSlot
	{
	public:
		FSlot() :SBoxPanel::FSlot() {}
		FSlot& MaxHeight(const TAttribute<float> & InMaxHeight)
		{
			MaxSize = InMaxHeight;
			return *this;
		}
		FSlot& FillHeight(const TAttribute<float>& StrethCoefficient)
		{
			SizeParam = FStretch(StrethCoefficient);
			return *this;
		}
		FSlot& Padding(float uniform)
		{
			SlotPadding = FMargin(uniform);
			return *this;
		}
		FSlot& Padding(float Horizontal, float vertical)
		{
			SlotPadding = FMargin(Horizontal,vertical);
			return *this;
		}
		FSlot& Padding(float left, float Top, float Right, float bottom)
		{
			SlotPadding = FMargin(left,Top,Right,bottom);
			return *this;
		}
		FSlot& Padding(const TAttribute<FMargin>::FGetter &Indelegate)
		{
			SlotPadding.Bind(Indelegate);
			return *this;
		}

		FSlot& HAlign(EHorizontalAlignment InHAlignment)
		{
			HAlignment = InHAlignment;
			return *this;
		}

		FSlot& VAlign(EVerticalAlignment InVAlignment)
		{
			VAlignment = InVAlignment;
			return *this;
		}

		FSlot& Padding(TAttribute<FMargin> InPadding) 
		{
			SlotPadding = InPadding; 
			return *this;
		}

		FSlot& operator[](TSharedRef<SWidget>InWidget)
		{
			SBoxPanel::FSlot::operator[](InWidget);
			return *this;
		}

		FSlot& Expose(FSlot*& OutVarToInit)
		{
			OutVarToInit = this;
			return *this;
		}
	};

	static FSlot& Slot()
	{
		return *(new FSlot());
	}

public:
	SLATE_BEGIN_ARGS(SAutoLayout) {}
	SLATE_ATTRIBUTE(FMargin,ContentMargin)
	SLATE_SUPPORTS_SLOT(SAutoLayout::FSlot)
	SLATE_END_ARGS()

	FORCEINLINE SAutoLayout() :SBoxPanel(Orient_Horizontal) {};

	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
public:
	void Construct(const FArguments& InArgs);
	FSlot& AddSlot() 
	{
		SAutoLayout::FSlot& NewSlot = *new FSlot();
			this->Children.Add(&NewSlot);
			return NewSlot;
 	}

	FMargin ContentMargin;
};
