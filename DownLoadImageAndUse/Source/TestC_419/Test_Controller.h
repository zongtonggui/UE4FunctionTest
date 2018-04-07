// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HttpModule.h"
#include "Http.h"
#include "Runtime/Online/http/Public/Interfaces/IHttpRequest.h"
#include "Test_Controller.generated.h"



/**
 * 
 */
UCLASS()
class TESTC_419_API ATest_Controller : public APlayerController
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void DownLoad(const FString& URL);

	void OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	void OnRequestProgress(FHttpRequestPtr HttpRequest, int32 BytesSent, int32 BytesReceived);

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetTexture2DFromDiskFile(const FString& FilePath, UTexture2D* MyTexture);
};
