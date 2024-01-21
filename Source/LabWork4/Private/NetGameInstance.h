// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetBaseCharacter.h"
#include "NetGameInstance.generated.h"

/**
 * 
 */


UCLASS()
class UNetGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(BlueprintCallable)
	void host(FString MapName, FSPlayerInfo PlayerInfo);

	UFUNCTION(BlueprintCallable)
	void join(FString Address, FSPlayerInfo PlayerInfo);

	UPROPERTY(BlueprintReadWrite)
	FSPlayerInfo PlayerInfo;

	UPROPERTY(BlueprintReadWrite, Replicated)
	FSPlayerStats PlayerStats;
};
