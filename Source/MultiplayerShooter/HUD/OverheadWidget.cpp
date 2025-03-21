// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "GameFramework/PlayerState.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;

	switch (RemoteRole)
	{
	case ROLE_Authority:
		Role = FString("Authority");
		break;
	case ROLE_AutonomousProxy:
		Role = FString("AutonomousProxy");
		break;
	case ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
		break;
	case ROLE_None:
		Role = FString("None");
		break;
	}

	FString RemoteRoleString = FString::Printf(TEXT("Remote Role: %s"), *Role);
	SetDisplayText(RemoteRoleString);
}

void UOverheadWidget::ShowPlayerName(APawn* InPawn)
{
	
	if (InPawn->Controller.Get() != nullptr)
	{
		if (APlayerState* PlayerState = InPawn->Controller.Get()->GetPlayerState<APlayerState>())
		{
			FString PlayerName = PlayerState->GetPlayerName();

			FString PlayerNameString = FString::Printf(TEXT("Player name: %s"), *PlayerName);
			SetDisplayText(PlayerNameString);
		}
	}
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();

	Super::NativeDestruct();
}
