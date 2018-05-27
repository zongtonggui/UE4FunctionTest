// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "AutoLayout.h"
#include <PanelSlot.h>
#include "AutoLayoutUI.generated.h"

/**
 * 
 */
UCLASS()
class UMGEXTERN_API UAutoLayoutUI : public UPanelWidget
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SanWu|AutoLayout")
	FMargin ContentMargin;
public:

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
protected:
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* InSlot)override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot)override;

	virtual void ReleaseSlateResources(bool bReaseChildren) override;
	virtual TSharedRef<SWidget>RebuildWidget()override;
	TSharedPtr<SAutoLayout> MyAutoLayout;
	
};
