// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Math/UnrealMathUtility.h" 

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bPickable = true;
	bWasInPile = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	// Baþlangýçta kullanmak istediðiniz mesh'i ayarlayýn (replace "Path/To/Your/StaticMesh.StaticMesh" with your actual mesh path)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
	}

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	SetItemVisual(GetRandomItemType());
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseItem::SetItemVisual(ItemTypes ItemType)
{
	switch (ItemType)
	{
		case ItemTypes::Cube:
		{
			ChangeMesh("StaticMesh'/Engine/BasicShapes/Cube.Cube'");
			break;
		}
		case ItemTypes::Cone:
		{
			ChangeMesh("StaticMesh'/Engine/BasicShapes/Cone.Cone'");
			break;
		}
		case ItemTypes::Sphere:
		{
			ChangeMesh("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'");
			break;
		}
		case ItemTypes::Cylinder:
		{
			ChangeMesh("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'");
			break;
		}
	}
	
}

void ABaseItem::ChangeMesh(FString Path)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NewMeshAsset(*Path);
	if (NewMeshAsset.Succeeded())
	{
		// Mesh'i deðiþtirin
		Mesh->SetStaticMesh(NewMeshAsset.Object);
	}
	else
	{
		// Hata durumunda bir mesaj yazdýrabilirsiniz
		UE_LOG(LogTemp, Error, TEXT("Mesh bulunamadý: %s"), *Path);
	}
}

ItemTypes ABaseItem::GetRandomItemType()
{
	// Enum deðerlerini belirleme
	TArray<ItemTypes> AllItemTypes = { ItemTypes::Cube, ItemTypes::Cone, ItemTypes::Sphere, ItemTypes::Cylinder };

	// Rastgele bir tamsayý seç
	int32 RandomIndex = FMath::RandRange(0, AllItemTypes.Num() - 1);

	// Seçilen tamsayýya karþýlýk gelen enum deðerini döndür
	return AllItemTypes[RandomIndex];
}


