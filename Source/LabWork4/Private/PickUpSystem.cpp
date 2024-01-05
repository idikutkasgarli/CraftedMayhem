// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpSystem.h"
#include "ItemPile.h"
#include "Components/PrimitiveComponent.h"

AItemPile ItemPile;
// Sets default values for this component's properties
UPickUpSystem::UPickUpSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickUpSystem::BeginPlay()
{
	Super::BeginPlay();

	//OnComponentBeginOverlap.AddDynamic(this, &UItemPickupComponent::OnPlayerEnterPickupZone);
	// ...
	
}



// Called every frame
void UPickUpSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickUpSystem::SnapItemToCharacter(AActor* TargetCharacter, AActor* Item, FName SocketName)
{
	if (!TargetCharacter || !Item) return;
	if (bItemInPile)
	{
		ItemPile.RemoveAnItemFromPile();
	}
	USkeletalMeshComponent* CharacterMesh = Cast<USkeletalMeshComponent>(TargetCharacter->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (!CharacterMesh) return;

	if (CharacterMesh->DoesSocketExist(SocketName))
	{
		FVector SocketLocation = CharacterMesh->GetSocketLocation(SocketName);
		Item->SetActorLocation(SocketLocation);
		
		Item->AttachToActor(TargetCharacter, FAttachmentTransformRules::KeepWorldTransform, SocketName);
	}
}

void UPickUpSystem::DropItemFromChacater(AActor* Item, AActor* TargetCharacter)
{
	if (!Item)return;

	Item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
}




