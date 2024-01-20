// Fill out your copyright notice in the Description page of Project Settings.


#include "NetBaseCharacter.h"
#include "NetGameInstance.h"
#include <Kismet/GameplayStatics.h>

static UDataTable* SBodyParts = nullptr;

static const wchar_t* BodyPartNames[] =
{
	TEXT("Face"),
	TEXT("Hair"),
	TEXT("Chest"),
	TEXT("Hands"),
	TEXT("Legs"),
	TEXT("Beard"),
	TEXT("EyeBrows")
};

// Sets default values
ANetBaseCharacter::ANetBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PartFace = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Face"));
	PartFace->SetupAttachment(GetMesh());
	PartFace->SetLeaderPoseComponent(GetMesh());

	PartHands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands"));
	PartHands->SetupAttachment(GetMesh());
	PartHands->SetLeaderPoseComponent(GetMesh());

	PartLegs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
	PartLegs->SetupAttachment(GetMesh());
	PartLegs->SetLeaderPoseComponent(GetMesh());

	PartHair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hair"));
	PartHair->SetupAttachment(PartFace, FName("headSocket"));

	PartBeard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beard"));
	PartBeard->SetupAttachment(PartFace, FName("headSocket"));

	PartEyeBrows = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EyeBrows"));
	PartEyeBrows->SetupAttachment(PartFace, FName("headSocket"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_Eyes(TEXT("StaticMesh'/Game/StylizedModularChar/Meshes/SM_Eyes.SM_Eyes'"));

	PartEyes = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eyes"));
	PartEyes->SetupAttachment(PartFace, FName("headSocket"));
	PartEyes->SetStaticMesh(SK_Eyes.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BodyParts(TEXT("DataTable'/Game/Blueprints/DT_BodyParts.DT_BodyParts'"));
	SBodyParts = DT_BodyParts.Object;

	bDead = false;
	PlayerDamage = 20.f;
	MaxHealth = 100;
	SpeedMltp = 0.f;
	HealthMltp = 1.f;
	DamageMltp = 1.f;
}

// Called when the game starts or when spawned
/*void ANetBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	if (IsLocallyControlled())
	{
		UNetGameInstance* Instance = Cast<UNetGameInstance>(GWorld->GetGameInstance());
		if (Instance && Instance->PlayerInfo.Ready)
		{
			SubmitPlayerInfoToServer(Instance->PlayerInfo);
			Health = Instance->PlayerStats.Health;
			SpeedMltp = Instance->PlayerStats.SpeedMltp;
			DamageMltp = Instance->PlayerStats.DamageMltp;
		}
	}	
}*/

void ANetBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (IsLocallyControlled())
	{
		UNetGameInstance* Instance = Cast<UNetGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (Instance)
		{
			
			SubmitPlayerInfoToServer(Instance->PlayerInfo);

			// Retrieve and set player stats from the game instance
			Health = Instance->PlayerStats.Health;
			SpeedMltp = Instance->PlayerStats.SpeedMltp;
			DamageMltp = Instance->PlayerStats.DamageMltp;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PLAYER STATS UPDATED"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Health: %f"), Health));
		}
		else
		{
			// Log an error or display a message if the game instance is not found
			UE_LOG(LogTemp, Error, TEXT("Game instance not found."));
		}
	}
}

void ANetBaseCharacter::OnConstruction(const FTransform& Transform)
{
	UpdateBodyParts();
}

// Called every frame
void ANetBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void ANetBaseCharacter::ChangeBodyPart(EBodyPart index, int value, bool DirectSet)
{
	FSMeshAssetList* List = GetBodyPartList(index, PartSelection.isFemale);
	if (List == nullptr) return;

	int CurrentIndex = PartSelection.Indices[(int)index];

	if (DirectSet) 
	{ 
		CurrentIndex = value; 
	}
	else 
	{ 
		CurrentIndex += value; 
	}

	int Num = List->ListSkeletal.Num() + List->ListStatic.Num();

	if (CurrentIndex < 0) 
	{ 
		CurrentIndex += Num; 
	}
	else 
	{ 
		CurrentIndex %= Num; 
	}

	PartSelection.Indices[(int)index] = CurrentIndex;

	switch (index)
	{
	case EBodyPart::BP_Face:PartFace->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]); break;
	case EBodyPart::BP_Beard:PartBeard->SetStaticMesh(List->ListStatic[CurrentIndex]); break;
	case EBodyPart::BP_Chest:GetMesh()->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]); break;
	case EBodyPart::BP_Hair:PartHair->SetStaticMesh(List->ListStatic[CurrentIndex]); break;
	case EBodyPart::BP_Hands:PartHands->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]); break;
	case EBodyPart::BP_Legs:PartLegs->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]); break;
	case EBodyPart::BP_EyeBrows:PartEyeBrows->SetStaticMesh(List->ListStatic[CurrentIndex]); break;
	}
}

void ANetBaseCharacter::ChangeGender(bool _isFemale)
{
	PartSelection.isFemale = _isFemale;
	UpdateBodyParts();
}

/*void ANetBaseCharacter::SubmitPlayerInfoToServer_Implementation(FSPlayerInfo Info, FSPlayerStats Stats)
{
	PartSelection = Info.BodyParts;
	PlayerStats = Stats.PlayerStats;

	if (HasAuthority())
	{
		OnRep_PlayerInfoChanged();
		OnRep_PlayerStatChanged();
	}
}*/

void ANetBaseCharacter::SubmitPlayerInfoToServer_Implementation(FSPlayerInfo Info)
{
	PartSelection = Info.BodyParts;
	PlayerStats = Info.PlayerStats;

	if (HasAuthority())
	{
		OnRep_PlayerInfoChanged();
		OnRep_PlayerStatChanged();
	}

}

void ANetBaseCharacter::OnRep_PlayerInfoChanged()
{
	UpdateBodyParts();
}

void ANetBaseCharacter::OnRep_PlayerStatChanged()
{
	UpdatePlayerStats();
}

void ANetBaseCharacter::WhenDead_Implementation()//replike_?
{

	if (PlayerController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("disabled"));

		bDead = true;
		WhenDied();
	}

}

void ANetBaseCharacter::OnRep_bDead()
{
	WhenDead();
}

void ANetBaseCharacter::OnRep_Buff()
{
	
}

void ANetBaseCharacter::DisableInputPlayer()
{
	PlayerController->DisableInput(nullptr); // nullptr, tüm giriþ türlerini devre dýþý býrakýr
	PlayerController->UnPossess();
}



void ANetBaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetBaseCharacter, PartSelection);
	DOREPLIFETIME(ANetBaseCharacter, PlayerStats);
	DOREPLIFETIME(ANetBaseCharacter, Health);
	DOREPLIFETIME(ANetBaseCharacter, bDead);
	DOREPLIFETIME(ANetBaseCharacter, SpeedMltp);
	DOREPLIFETIME(ANetBaseCharacter, HealthMltp);
	DOREPLIFETIME(ANetBaseCharacter, DamageMltp);
}

FSMeshAssetList* ANetBaseCharacter::GetBodyPartList(EBodyPart part, bool isFemale)
{
	FString Name = FString::Printf(TEXT("%s%s"), isFemale ? TEXT("Female") : TEXT("Male"), BodyPartNames[(int)part]);
	return SBodyParts ? SBodyParts->FindRow<FSMeshAssetList>(*Name, nullptr) : nullptr;
}

void ANetBaseCharacter::UpdateBodyParts()
{
	ChangeBodyPart(EBodyPart::BP_Face, 0, false);
	ChangeBodyPart(EBodyPart::BP_Beard, 0, false);
	ChangeBodyPart(EBodyPart::BP_Chest, 0, false);
	ChangeBodyPart(EBodyPart::BP_Hair, 0, false);
	ChangeBodyPart(EBodyPart::BP_Hands, 0, false);
	ChangeBodyPart(EBodyPart::BP_Legs, 0, false);
	ChangeBodyPart(EBodyPart::BP_EyeBrows, 0, false);

}

void ANetBaseCharacter::UpdatePlayerStats()
{
	UNetGameInstance* Instance = Cast<UNetGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Instance)
	{

		Health = Instance->PlayerStats.Health;
		SpeedMltp = Instance->PlayerStats.SpeedMltp;
		DamageMltp = Instance->PlayerStats.DamageMltp;
	}
}

void ANetBaseCharacter::TakeDamage_Implementation(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!HasAuthority())return;
	if (bDead)return;
	PlayerDamage = Damage;
	Health = Health - Damage;
	if (Health <= 0)
	{
		bDead = true;
		WhenDead();
	}
}



