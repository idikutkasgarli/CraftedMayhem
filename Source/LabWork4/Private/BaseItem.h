// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseItem.generated.h"

UENUM(BlueprintType)
enum class ItemTypes : uint8
{
	Cube = 0,
	Cone = 1,
	Sphere = 2,
	Cylinder = 3,
};
class AItemPile;

UCLASS()
class ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite)
	bool bPickable;
	UPROPERTY(BlueprintReadWrite)
	bool bWasInPile;
	UPROPERTY(BlueprintReadWrite)
	AItemPile* LastItemPileIn;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable)
	void SetItemVisual(ItemTypes ItemType);
	UFUNCTION(BlueprintCallable)
	void ChangeMesh(FString path);
	UFUNCTION(BlueprintCallable)
	ItemTypes GetRandomItemType();


};
