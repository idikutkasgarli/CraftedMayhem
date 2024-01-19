#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseItem.generated.h"

UENUM(BlueprintType)
enum class ItemTypes : uint8
{
	Heart = 0,
	Speed = 1,
	Attack = 2,
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
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_SelectItem)
	ItemTypes ItemTypeRep;

	UFUNCTION(BlueprintCallable)
	void ChangeMesh(FString path);
	UFUNCTION(BlueprintCallable)
	ItemTypes GetRandomItemType();
	UFUNCTION(BlueprintCallable)
	void SelectItemType(ItemTypes ItemTypee);
	UFUNCTION(BlueprintCallable)
	void MultiPlayerSetVisuals();
	UFUNCTION(BlueprintCallable)
	void OnRep_SelectItem();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};