// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPile.h"

//ABaseItem* LastItem;
// Sets default values
AItemPile::AItemPile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AItemPile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemPile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemPile::AddToPile(ABaseItem* Item, bool& bFilled)
{
	if (!Item)return;
	//LastItem = Item;
	bFilled = false;
	if (HoldingItems.Num() < 2)
	{
		HoldingItems.Add(Item);
		if (HoldingItems.Num() == 2)
		{
			bFilled = true;
			for (ABaseItem* ExistingItem : HoldingItems)
			{
				if (ExistingItem)
				{
					ExistingItem->bPickable = false;
					ExistingItem->SetActorHiddenInGame(false);
					//buraya yeni itemi ��kar ve eski iki itemi yok et veya gizle
					//yeni bi fonk a� ve burda olu�an yeni Item'� spawnla ve �zelliklerini oyuncuya ver
				}
			}
		}
	}
}

void AItemPile::RemoveAnItemFromItemPile(ABaseItem* ItemToRemove)
{
	HoldingItems.Remove(ItemToRemove);
}

