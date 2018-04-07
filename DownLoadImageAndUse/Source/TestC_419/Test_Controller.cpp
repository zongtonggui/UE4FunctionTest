// Fill out your copyright notice in the Description page of Project Settings.

#include "Test_Controller.h"
#include "FileHelper.h"
#include "Paths.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "ModuleManager.h"
#include "BulkData.h"
#include "Engine/Texture2D.h"


void ATest_Controller::Upload(const FString & URL, const FString & ContentString)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL(URL);
	HttpReuest->SetVerb(TEXT("POST"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->SetContentAsString(ContentString);//也可以用SetContent，只不过参数要换成TArray  
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &ATest_Controller::OnRequestComplete);
	HttpReuest->OnRequestProgress().BindUObject(this, &ATest_Controller::OnRequestProgress);
	HttpReuest->ProcessRequest();
}
void ATest_Controller::DownLoad(const FString & URL)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL(URL);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &ATest_Controller::OnRequestComplete);
	HttpReuest->OnRequestProgress().BindUObject(this, &ATest_Controller::OnRequestProgress);
	HttpReuest->ProcessRequest();
}
//从网络上下载图片，并以2进制的形式保存到本地
void ATest_Controller::OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		//如果是下载请求，可通过这段代码将文件保存  
		FString Filename = FPaths::GetCleanFilename(HttpRequest->GetURL());
		FFileHelper::SaveArrayToFile(HttpResponse->GetContent(), *FString::Printf(TEXT("%s%s"), *FPaths::GameSavedDir(), *Filename));
		UE_LOG(LogTemp,Warning,TEXT("SavePath:%s"), *FPaths::GameSavedDir());
	}
}

void ATest_Controller::OnRequestProgress(FHttpRequestPtr HttpRequest, int32 BytesSent, int32 BytesReceived)
{
	
}



//从本地加载图片，然后转换成Texture2D
UTexture2D * ATest_Controller::GetTexture2DFromDiskFile(const FString & FilePath, UTexture2D * MyTexture)
{
	TArray<uint8> RawFileData;
	if (FFileHelper::LoadFileToArray(RawFileData, *FilePath))
	{
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		//注意:照片格式是JPEG，其他格式也被支持
		IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
		if (ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		{
			const TArray<uint8>* UnCompressedBGRA = NULL;
			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UnCompressedBGRA))
			{
				//创建图片内存以存储图像数据
				
				MyTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(),ImageWrapper->GetHeight(), PF_B8G8R8A8);
				//填充图像数据
				uint8 *TextureData = static_cast<uint8 *>(MyTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
				FMemory::Memcpy(TextureData, UnCompressedBGRA->GetData(), UnCompressedBGRA->Num());
				MyTexture->PlatformData->Mips[0].BulkData.Unlock();

				//更新
				MyTexture->UpdateResource();
			}
		}

	}
	return MyTexture;
}
