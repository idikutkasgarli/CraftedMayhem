// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
#include "BaseItem.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
    SpawnBaseItems();
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnBaseItems()
{
    if (BaseItemBlueprint && HasAuthority())
    {
        FVector SpawnLocation = GetActorLocation();

        // Spawn i�lemini 8 defa ger�ekle�tir
        for (int32 i = 0; i < 8; ++i)
        {
            // �ember �eklinde spawn etmek i�in a��y� hesapla
            float Angle = 2.0f * PI * i / 8.0f;
            FVector Offset = FVector(FMath::Cos(Angle) * 200.0f, FMath::Sin(Angle) * 200.0f, 0.0f);

            // �ember �zerinde spawn konumunu ayarla
            FVector SpawnPosition = SpawnLocation + Offset;

            // BP_BaseItem spawn et
            ABaseItem* SpawnedBaseItem = GetWorld()->SpawnActor<ABaseItem>(BaseItemBlueprint, SpawnPosition, FRotator::ZeroRotator);

            // Spawn edilen BP_BaseItem'� kontrol et
            if (SpawnedBaseItem)
            {
                // �stedi�iniz ba�ka ayarlamalar� burada yapabilirsiniz
                SpawnedBaseItem->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            }
        }
    }
}

