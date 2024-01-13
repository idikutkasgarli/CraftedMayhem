// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.h"
#include "NetBaseCharacter.h"
#include "ItemPile.generated.h"

UCLASS()
class AItemPile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: 
	UPROPERTY(BlueprintReadWrite)
	TArray<ABaseItem*> HoldingItems;
	UPROPERTY(BlueprintReadWrite)
	ANetBaseCharacter* BelongCharacter;
	UFUNCTION(BlueprintCallable)
	void AddToPile(ABaseItem* Item, bool& bFilled);
	UFUNCTION(BlueprintCallable)
	void RemoveAnItemFromItemPile(ABaseItem* ItemToRemove);
	UFUNCTION(BlueprintCallable)
	void SetCraftedItem(ABaseItem* NewCheckingItems);

};
