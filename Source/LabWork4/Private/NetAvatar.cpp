// Fill out your copyright notice in the Description page of Project Settings.


#include "NetAvatar.h"
#include "GameFrameWork/CharacterMovementComponent.h"

ANetAvatar::ANetAvatar() :
	bSpeedBuff(false),
	HealthRegenMltp(0.05),
	MovementScale(1.0f)

{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ANetAvatar::BeginPlay()
{
	Super::BeginPlay();

	Camera->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

   

}

void ANetAvatar::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetAvatar, bHoldingRunKey);
	DOREPLIFETIME(ANetAvatar, bSpeedBuff);
}

void ANetAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANetAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANetAvatar::MoveRight);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ANetAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ANetAvatar::RunReleased);

}

void ANetAvatar::DoubleHeartBuff()
{
	Health = 200.f;
}

void ANetAvatar::HeartAndSpeedBuff()
{

	while (ANetAvatar::GetCharacterMovement()->Velocity.Length() > 0);
	{
		
		Health += Health * HealthRegenMltp;
	}

}

void ANetAvatar::HeartAndAttackBuff()
{
	//silah�n boyutu art�yo
}

void ANetAvatar::DoubleSpeedBuff(bool bSpeedTrigger)
{
	bSpeedBuff = bSpeedTrigger;
	OnRep_UpdateMovementParams();
}

void ANetAvatar::SpeedAndAttackBuff()
{
	//attack speed
}

void ANetAvatar::DoubleAttackBuff()
{
	//2x damage
}



void ANetAvatar::MoveForward(float Scale)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementScale * Scale);
}

void ANetAvatar::MoveRight(float Scale)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, MovementScale * Scale);
}




void ANetAvatar::OnRep_UpdateMovementParams()
{
	 if (bHoldingRunKey)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f + 600.0f * SpeedMltp;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.f + 300.0f * SpeedMltp;
	}
}

void ANetAvatar::RunPressed()
{
	if (HasAuthority())
	{
		bHoldingRunKey = true;
		OnRep_UpdateMovementParams();
	}
	else
	{
		ServerStartRunning();
	}
}

void ANetAvatar::RunReleased()
{
	if (HasAuthority())
	{
		bHoldingRunKey = false;
		OnRep_UpdateMovementParams();
	}
	else
	{
		ServerStopRunning();
	}
}

void ANetAvatar::ServerStartRunning_Implementation()
{
	RunPressed();
}

void ANetAvatar::ServerStopRunning_Implementation()
{
	RunReleased();
}