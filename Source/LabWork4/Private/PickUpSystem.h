// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "ItemPile.h"
#include "PickUpSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPickUpSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickUpSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void SnapItemToCharacter(AActor* TargetCharacter, AActor* Item, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void DropItemFromChacater(AActor* Item, AActor* TargetCharacter);

	UPROPERTY(BlueprintReadWrite)
	bool bHasItemInPile;
};
