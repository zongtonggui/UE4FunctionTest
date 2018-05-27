// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoLayout.h"



void SAutoLayout::Construct(const FArguments& InArgs)
{
	const int32 NumSlot = InArgs.Slots.Num();
	ContentMargin = InArgs._ContentMargin.Get();
	
	for (int32 SlotIndex = 0; SlotIndex < NumSlot; ++SlotIndex)
	{
		Children.Add(InArgs.Slots[SlotIndex]);
	}
}

void SAutoLayout::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	FVector2D areaSize = AllottedGeometry.GetLocalSize(); //�������Ĵ�С�ߴ�
	float startX = ContentMargin.Left;
	float startY = ContentMargin.Top;
	float currentMaxHeight = 0.f;
	
	if (Children.IsValidIndex(0))
	{ 

	for (int32 ChildIndex = 0; ChildIndex <= Children.Num(); ++ChildIndex)
	{
		if(	Children.IsValidIndex(ChildIndex))
		{ 
			const SBoxPanel::FSlot& CurChild = Children[ChildIndex];
			const EVisibility ChildVisiblity = CurChild.GetWidget()->GetVisibility();
			FVector2D Size = CurChild.GetWidget()->GetDesiredSize();
			//Accepts�ж�һ��Ԫ���Ƿ���Ҫ�������
			if (ArrangedChildren.Accepts(ChildVisiblity))
			{
				if (Size.Y > currentMaxHeight)
					currentMaxHeight = Size.Y;
			}
			if (startX + Size.X < areaSize.X)
			{
				//������ӿؼ���������Ļ�ϵ�ָ��λ��
				ArrangedChildren.AddWidget(ChildVisiblity, AllottedGeometry.MakeChild(CurChild.GetWidget(), FVector2D(startX, startY), FVector2D(Size.X, Size.Y)));
				startX += ContentMargin.Right;
				startX += Size.X;
			}
			else
			{
				startX = ContentMargin.Left;
				startY += currentMaxHeight+ContentMargin.Bottom;
				ArrangedChildren.AddWidget(ChildVisiblity, AllottedGeometry.MakeChild(CurChild.GetWidget(), FVector2D(startX, startY), FVector2D(Size.X, Size.Y)));
				startX += Size.X+ContentMargin.Right;
				currentMaxHeight = Size.Y;
			}
		}
	}

	}
	
}
