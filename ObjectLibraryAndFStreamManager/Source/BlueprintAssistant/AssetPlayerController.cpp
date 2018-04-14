// Fill out your copyright notice in the Description page of Project Settings.

#include "AssetPlayerController.h"
#include "Engine/Engine.h"
#include "Engine/StreamableManager.h"
#include "Private/Serialization/AsyncLoadingThread.h"
 
UObjectLibrary * AAssetPlayerController::ObjectLibrary=NULL;

//绑定事件输入
void AAssetPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnableInput(this);
	check(InputComponent);
	//输入事件的绑定,开始异步加载，在编辑器中是Action 是 1
	InputComponent->BindAction("LoadAsset",EInputEvent::IE_Pressed,this, &AAssetPlayerController::StartAsyncLoadAssert);
	//2键:检查资源是否是加载状态
	InputComponent->BindAction("CheckAsset", EInputEvent::IE_Pressed,this, &AAssetPlayerController::IsContainInMemory);
	//3键:进行资源的卸载
	InputComponent->BindAction("ReleaseAsset", EInputEvent::IE_Pressed, this, &AAssetPlayerController::UnLoadAsset);

	//4键:进行资源引用的清除
	InputComponent->BindAction("ClearReference", EInputEvent::IE_Pressed, this, &AAssetPlayerController::ClearReference);
}


//开始进行异步资源加载
void AAssetPlayerController::StartAsyncLoadAssert()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Pressed 1 by C++ binding");
	TestObjectLibrary();
	TestStreamableManagerAsyncLoad();
}


//使用ObjectLibrary 获取指定路径下的资产信息 AssetData。   使用AssertRegistry 也能获取资源的AssetData
void AAssetPlayerController::TestObjectLibrary()
{
	if (!ObjectLibrary)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, GIsEditor);
		ObjectLibrary->AddToRoot();
	}
	int AssetCount = ObjectLibrary->LoadBlueprintAssetDataFromPath("/Game/Test");

	UE_LOG(LogTemp, Warning, TEXT("Asset Count: %d"), AssetCount);
}


//将AssetData信息转换为FSoftObjectPtr或者FSoftObjectPath，然后才能用StreamableManager进行资源的异步加载
void AAssetPlayerController::TestStreamableManagerAsyncLoad()
{
	FStreamableManager* streamable = new FStreamableManager();
	TArray<FAssetData> assetdata;
	ObjectLibrary->GetAssetDataList(assetdata);

	TArray<FSoftObjectPath> ItemsToStream;

	for (int i = 0; i < assetdata.Num(); i++)
	{
		ItemsToStream.AddUnique(assetdata[i].ToSoftObjectPath());
	}
	if (ItemsToStream.Num() > 0)
	{
		streamable->RequestAsyncLoad(ItemsToStream, FStreamableDelegate::CreateUObject(this, &AAssetPlayerController::KeepReference));
	}
}


//将加载的资源保持引用，否则在这个函数调用完成之后就会销毁
void AAssetPlayerController::KeepReference()
{
	TArray<FAssetData> assetdata;
	ObjectLibrary->GetAssetDataList(assetdata);

	TArray<FSoftObjectPath> ItemsToStream;

	for (int i = 0; i < assetdata.Num(); i++)
	{
		ItemsToStream.AddUnique(assetdata[i].ToSoftObjectPath());
	}

	myobject.Add(assetdata[0].GetAsset());
	
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Async Load Object OK");

}

void AAssetPlayerController::IsContainInMemory()
{
	TArray<FAssetData> myAssetData;
	if (!ObjectLibrary)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, GIsEditor);
		ObjectLibrary->AddToRoot();
	}
	ObjectLibrary->LoadBlueprintAssetDataFromPath("/Game/Test");
	ObjectLibrary->GetAssetDataList(myAssetData);
	if (myAssetData[0].IsAssetLoaded())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Async Remain In Memory");
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Async Don't In Memory");
	
	}
}

void AAssetPlayerController::UnLoadAsset()
{
	TArray<FAssetData> myAssetData;
	if (!ObjectLibrary)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, GIsEditor);
		ObjectLibrary->AddToRoot();
	}
	ObjectLibrary->LoadBlueprintAssetDataFromPath("/Game/Test");
	ObjectLibrary->GetAssetDataList(myAssetData);
	FStreamableManager* streamable = new FStreamableManager();
	streamable->Unload(myAssetData[0].ToSoftObjectPath());
	FString Tip = "Start Asset Unload" + myAssetData[0].GetPrimaryAssetId().ToString();
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan,Tip);
}

void AAssetPlayerController::ClearReference()
{
	if (myobject.Num() > 0)
	{
		myobject[0] = NULL;
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "clear asset asset reference");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Don't have Asset");
	}
}
