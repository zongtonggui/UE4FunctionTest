// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateStyle.h"

/**
 * 
 */
//FMenuStyles :管理SlateStyleSet 并且返回，这个SlateStyleSet 会存有指定路径下的SlateStyle
class EXPLOREUE4_API FMenuStyles
{
public:
	// 初始化MenuStyleInstance 的值并且用 Slate Style Registry 进行注册.
	static void Initialize();
	// 取消注册 Slate Style Set and 并且重置 MenuStyleInstance 指针.
	static void Shutdown();
	// Retrieves a reference to the Slate Style pointed to by MenuStyleInstance.
	static const TSharedPtr<FSlateStyleSet> Get();
	// Retrieves the name of the Style Set.
	static FName GetStyleSetName();

private:
	////创建一个作用于指定路径的Slate Style Set
	static TSharedRef<class FSlateStyleSet> Create();
	// 我们的StyleSet的单例对象.
	static TSharedPtr<class FSlateStyleSet> MenuStyleInstance;
};
