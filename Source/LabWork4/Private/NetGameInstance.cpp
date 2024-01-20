// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameInstance.h"

void UNetGameInstance::host(FString MapName, FSPlayerInfo Info, FSPlayerStats Stats)
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, TEXT("Hosting Game..."));
	PlayerStats = Stats;
	PlayerInfo = Info;
	PlayerInfo.Ready = true;
	GWorld->ServerTravel(FString::Printf(TEXT("/Game/Maps/%s?listen"), *MapName));
}

void UNetGameInstance::join(FString Address, FSPlayerInfo Info, FSPlayerStats Stats)
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, FString::Printf(TEXT("Joining Game at %s..."), *Address));
	PlayerStats = Stats;
	PlayerInfo = Info;
	PlayerInfo.Ready = true;
	GWorld->GetFirstPlayerController()->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
