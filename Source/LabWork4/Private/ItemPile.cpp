// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPile.h"
ABaseItem* CheckingItem;
//ABaseItem* LastItem;
// Sets default values
AItemPile::AItemPile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CheckingItem = nullptr;
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
	if (!HasAuthority())return;
	if (!Item)return;
	if (HoldingItems.Num() == 2)return;
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
					//buraya yeni itemi çýkar ve eski iki itemi yok et veya gizle
					//yeni bi fonk aç ve burda oluþan yeni Item'ý spawnla ve özelliklerini oyuncuya ver
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("executed"));
					SetCraftedItem(ExistingItem);
				}
			}
		}
	}
}

void AItemPile::RemoveAnItemFromItemPile(ABaseItem* ItemToRemove)
{
	HoldingItems.Remove(ItemToRemove);
}

	
void AItemPile::SetCraftedItem(ABaseItem* NewCheckingItems)
{
	if (!HasAuthority())return;
	if (!CheckingItem)
	{
		CheckingItem = NewCheckingItems;
	}
	else
	{
		switch (CheckingItem->ItemTypeRep)
		{
			case ItemTypes::Heart:
			{
				switch (NewCheckingItems->ItemTypeRep)//with Cube
				{
					case ItemTypes::Heart:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HeartX2"));
						break;
					}
					case ItemTypes::Speed:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hearth-Speed"));
						break;
					}
					case ItemTypes::Attack:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hearth-Attack"));
						break;
					}
				}
				break;
			}
			case ItemTypes::Speed:
			{
				switch (NewCheckingItems->ItemTypeRep)
				{
					case ItemTypes::Heart:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Speed-Heart"));
						break;
					}
					case ItemTypes::Speed:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SpeedX2"));
						break;
					}
					case ItemTypes::Attack:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Speed-Attack"));
						break;
					}
				}
				break;
			}
			case ItemTypes::Attack:
			{
				switch (NewCheckingItems->ItemTypeRep)
				{
					case ItemTypes::Heart:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack-Heart"));
						break;
					}
					case ItemTypes::Speed:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack-Speed"));
						break;
					}
					case ItemTypes::Attack:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AttackX2"));
						break;
					}
	
				}
				break;
			}

		}
		CheckingItem = nullptr;
	}
}

