// Fill out your copyright notice in the Description page of Project Settings.

#include "AssetPlayerController.h"
#include "Engine/Engine.h"
#include "Engine/StreamableManager.h"
#include "Private/Serialization/AsyncLoadingThread.h"
#include "Engine/Texture2D.h"
#include "Engine/AssetManager.h"
#include "AsyncLoading.h"
 
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

}


//开始进行异步资源加载
void AAssetPlayerController::StartAsyncLoadAssert()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Pressed 1 by C++ binding");
	TestObjectLibrary();
}


//使用ObjectLibrary 获取指定路径下的资产信息 AssetData。   使用AssertRegistry 也能获取资源的AssetData
void AAssetPlayerController::TestObjectLibrary()
{
	if (!ObjectLibrary)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(UTexture2D::StaticClass(), false, GIsEditor);
		ObjectLibrary->AddToRoot();
	}

	int AssetCount = ObjectLibrary->LoadAssetDataFromPath("/Game/Test");
	TestStreamableManagerAsyncLoad();
	UE_LOG(LogTemp, Warning, TEXT("Asset Count: %d"), AssetCount);
}


//将AssetData信息转换为FSoftObjectPtr或者FSoftObjectPath，然后才能用StreamableManager进行资源的异步加载. SreamableManager会让资源一直存在于内存中
void AAssetPlayerController::TestStreamableManagerAsyncLoad()
{
	FStreamableManager& streamable=UAssetManager::Get().GetStreamableManager();
	
	TArray<FAssetData> assetdata;
	ObjectLibrary->GetAssetDataList(assetdata);
	
	TArray<FSoftObjectPath> ItemsToStream;

	for (int i = 0; i < assetdata.Num(); i++)
	{
		ItemsToStream.AddUnique(assetdata[i].ToSoftObjectPath());
	}
	if (ItemsToStream.Num() > 0)
	{
		//想手动卸载资源bManageActiveHandle标记为true，默认为false：表示是否手动管理FStreamableHandle。
		//如果设置为true，则对象会一直常驻内存直到手动释放(必须手动调用对应的函数，否则就算把streamhandl指针引用清空，资产都不会被回收)。
		streamhandle=streamable.RequestAsyncLoad(ItemsToStream, FStreamableDelegate::CreateUObject(this, &AAssetPlayerController::KeepReference),1,false);
	}
}


//将加载的资源保持引用，否则在这个函数调用完成之后就会销毁
void AAssetPlayerController::KeepReference()
{
	TArray<FAssetData> assetdata;
	ObjectLibrary->GetAssetDataList(assetdata);
	
	if (Cast<UTexture2D>(assetdata[0].GetAsset()))
	{
		myobject=Cast<UTexture2D>(assetdata[0].GetAsset());
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Async Load Object OK");
	}

}

void AAssetPlayerController::IsContainInMemory()
{
	TArray<FAssetData> myAssetData;
	if (!ObjectLibrary)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(UTexture2D::StaticClass(), false, GIsEditor);
		ObjectLibrary->AddToRoot();
	}

	ObjectLibrary->LoadAssetDataFromPath("/Game/Test");
	ObjectLibrary->GetAssetDataList(myAssetData);
	if (myAssetData.Num() > 0)
	{
		if (myAssetData[0].IsAssetLoaded())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Async Remain In Memory");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Async Don't In Memory");
		}
	}
}

void AAssetPlayerController::UnLoadAsset()
{
	
	
	TArray<FAssetData> myAssetData;
	ObjectLibrary->GetAssetDataList(myAssetData);
	myobject = NULL;

	//手动卸载资源----方法1 : 如果有3处Streamhandle指向同一个资源，使用这个可以把这个三处对于资源的引用都释放掉。（方法1和方法2都只能让没有被持有的资源被回收）
	//FStreamableManager& streamable = UAssetManager::Get().GetStreamableManager();
	//streamable.Unload(myAssetData[0].ToSoftObjectPath());
	streamhandle = NULL;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Is UnLoading ...");
	
	//手动卸载资源----方法2 : 假设有3处加载同一个资源，必须所有3个都释放，资源才会被释放。
	//（即 只能释放此处对于资源的引用计数，如果自己不引用streamhandle,就自动释放从这个streamhandle加载的资源的所有权）
	//streamhandle->ReleaseHandle();
	
	//如果不手动调用GC，那么只能等到垃圾池到一定大小或者时间的时候，才会触发GC 回收机制
	GetWorld()->ForceGarbageCollection(true);
}
