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

//����һ��������ָ��·����Slate Style Set
TSharedRef<FSlateStyleSet> FMenuStyles::Create()
{
	//����һ��SlateStyleSet ȥָ�����ǵ�Slate Style .(���ǵ�Slate Style����Eidtor�д�����λ��/Game/UI/Styles·����)
	//�ڶ�������ָ���������ʽ����������
	//����������ΪInBasePath ,Resource.GetBrush����������BasePath��·���½���ƴ�ӣ�Ȼ�����
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