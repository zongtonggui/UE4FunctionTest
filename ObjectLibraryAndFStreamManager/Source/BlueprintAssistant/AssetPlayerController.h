// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/ObjectLibrary.h"
#include "AssetPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class BLUEPRINTASSISTANT_API AAssetPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	//
		//绑定事件输入
		virtual void SetupInputComponent() override;

		//开始进行异步资源加载
		void StartAsyncLoadAssert();

		//使用ObjectLibrary 获取指定路径下的资产信息 AssetData。   使用AssertRegistry 也能获取资源的AssetData
		void TestObjectLibrary();

		//将AssetData信息转换为FSoftObjectPtr或者FSoftObjectPath，然后才能用StreamableManager进行资源的异步加载
		void TestStreamableManagerAsyncLoad();

		//将加载的资源保持引用，否则在这个函数调用完成之后就会销毁
		void KeepReference();

		//检查资产是否在内存中
		void IsContainInMemory();
		
		//---------------------------------------------------------
		//目前并不知道如何从内存中卸载，下面2个方法不能卸载--------
		//---------------------------------------------------------

		//通过streaableManager卸载资产
		void UnLoadAsset();

		//通过清除引用卸载资产
		void ClearReference();
		static UObjectLibrary * ObjectLibrary;

		//用以保存加载的资源对象，否则就会在异步加载后被销毁
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UObject*> myobject;

};
