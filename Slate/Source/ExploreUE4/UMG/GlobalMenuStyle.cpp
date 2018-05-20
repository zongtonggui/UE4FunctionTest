// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalMenuStyle.h"

void FGlobalStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
}

const FName FGlobalStyle::TypeName = TEXT("FGlobalStyle");

const FName FGlobalStyle::GetTypeName() const
{
	static const FName TypeName = TEXT("FGlobalStyle");
	return TypeName;
}

const FGlobalStyle& FGlobalStyle::GetDefault()
{
	static FGlobalStyle Default;
	return Default;
}

UGlobalMenuStyle::UGlobalMenuStyle(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}