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
			case ItemTypes::Cube:
			{
				switch (NewCheckingItems->ItemTypeRep)//with Cube
				{
					case ItemTypes::Cube:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CubeX2"));
						break;
					}
					case ItemTypes::Cone:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube-Cone"));
						break;
					}
					case ItemTypes::Sphere:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube-Cone"));
						break;
					}
					case ItemTypes::Cylinder:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube-Cylinder"));
						break;
					}
				}
				break;
			}
			case ItemTypes::Cone:
			{
				switch (NewCheckingItems->ItemTypeRep)
				{
					case ItemTypes::Cube:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cone-Cube"));
						break;
					}
					case ItemTypes::Cone:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ConeX2"));
						break;
					}
					case ItemTypes::Sphere:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cone-Sphere"));
						break;
					}
					case ItemTypes::Cylinder:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cone-Cylinder"));
						break;
					}
				}
				break;
			}
			case ItemTypes::Sphere:
			{
				switch (NewCheckingItems->ItemTypeRep)
				{
					case ItemTypes::Cube:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sphere-Cube"));
						break;
					}
					case ItemTypes::Cone:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sphere-Cone"));
						break;
					}
					case ItemTypes::Sphere:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SphereX2"));
						break;
					}
					case ItemTypes::Cylinder:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sphere-Cylinder"));
						break;
					}
				}
				break;
			}
			case ItemTypes::Cylinder:
			{
					switch (NewCheckingItems->ItemTypeRep)
					{
					case ItemTypes::Cube:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cylinder-Cube"));
						break;
					}
					case ItemTypes::Cone:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cylinder-Cone"));
						break;
					}
					case ItemTypes::Sphere:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cylinder-Sphere"));
						break;
					}
					case ItemTypes::Cylinder:
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CylinderX2"));
						break;
					}
				}
				break;
			}
		}
		CheckingItem = nullptr;
	}
}

