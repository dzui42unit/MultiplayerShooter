// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MULTIPLAYERSHOOTER_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetDisplayText(FString TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerName(APawn* InPawn);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DisplayText;

	virtual void NativeDestruct() override;
};
