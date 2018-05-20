// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuStyles.h"
#include "SlateGameResources.h"
#include "SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FMenuStyles::MenuStyleInstance = NULL;
void FMenuStyles::Initialize()
{
	if (!MenuStyleInstance.IsValid())
	{
		MenuStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*MenuStyleInstance);
	}
}

//创建一个作用于指定路径的Slate Style Set
TSharedRef<FSlateStyleSet> FMenuStyles::Create()
{
	//创建一个SlateStyleSet 去指向我们的Slate Style .(我们的Slate Style是在Eidtor中创建，位于/Game/UI/Styles路径下)
	//第二个参数指定了这个样式集的作用域
	//第三个参数为InBasePath ,Resource.GetBrush将会基础这个BasePath的路径下进行拼接，然后查找
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FMenuStyles::GetStyleSetName(), "/Game/UI/Styles", "/Game/UI/Styles");
	return StyleRef;
}

FName FMenuStyles::GetStyleSetName()
{
	static FName StyleSetName(TEXT("MenuStyles"));
	return StyleSetName;
}


void FMenuStyles::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*MenuStyleInstance);
	ensure(MenuStyleInstance.IsUnique());
	MenuStyleInstance.Reset();
}

const TSharedPtr<FSlateStyleSet> FMenuStyles::Get()
{
	if(MenuStyleInstance.IsValid())
		return MenuStyleInstance;
	else 
	{
		Initialize();
		return MenuStyleInstance;
	}
}