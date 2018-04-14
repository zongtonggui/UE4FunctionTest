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
		//���¼�����
		virtual void SetupInputComponent() override;

		//��ʼ�����첽��Դ����
		void StartAsyncLoadAssert();

		//ʹ��ObjectLibrary ��ȡָ��·���µ��ʲ���Ϣ AssetData��   ʹ��AssertRegistry Ҳ�ܻ�ȡ��Դ��AssetData
		void TestObjectLibrary();

		//��AssetData��Ϣת��ΪFSoftObjectPtr����FSoftObjectPath��Ȼ�������StreamableManager������Դ���첽����
		void TestStreamableManagerAsyncLoad();

		//�����ص���Դ�������ã���������������������֮��ͻ�����
		void KeepReference();

		//����ʲ��Ƿ����ڴ���
		void IsContainInMemory();
		
		//---------------------------------------------------------
		//Ŀǰ����֪����δ��ڴ���ж�أ�����2����������ж��--------
		//---------------------------------------------------------

		//ͨ��streaableManagerж���ʲ�
		void UnLoadAsset();

		//ͨ���������ж���ʲ�
		void ClearReference();
		static UObjectLibrary * ObjectLibrary;

		//���Ա�����ص���Դ���󣬷���ͻ����첽���غ�����
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UObject*> myobject;

};
