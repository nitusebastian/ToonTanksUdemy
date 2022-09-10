// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Speed = 50.0f;
	TurnRate = 100;
	TurretRotationRate = 100;
}



void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	PlayerController = Cast<APlayerController>(GetController());
	FHitResult HitResult;
	bool bWasHit = PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
	if (bWasHit)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Actor hit %s "), *HitResult.GetActor()->GetName())
		FVector TargetLocation = HitResult.ImpactPoint;
		//DrawDebugSphere(GetWorld(), ImpactPoint, 50.0f, 18, FColor::Red);

		
		RotateTurret(TargetLocation);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
	PlayerInputComponent->BindAxis("RotateTurret", this, &ATank::RotateTurretByRelativeAmount);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePawn::Fire);
	
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector(Value * Speed * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator(0, Value * TurnRate * GetWorld()->DeltaTimeSeconds, 0);
	AddActorLocalRotation(DeltaRotation);
}

void ATank::RotateTurretByRelativeAmount(float X)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = X * TurretRotationRate * GetWorld()->DeltaTimeSeconds;
	TurretMesh->AddRelativeRotation(DeltaRotation);
	
}