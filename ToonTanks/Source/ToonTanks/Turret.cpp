// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Kismet/GameplayStatics.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (IsPlayerTankInFireRange())
	{
		FVector TankLocation = PlayerPawn->GetActorLocation();
		RotateTurret(TankLocation);

		if (!GetWorldTimerManager().IsTimerActive(Timer))
		{
			GetWorldTimerManager().SetTimer(Timer, this, &ABasePawn::Fire, 3.0f, true);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(Timer);
	}
}



bool ATurret::IsPlayerTankInFireRange() const
{
	FVector TankLocation = PlayerPawn->GetActorLocation();
	double DistanceToTank = FVector::Dist(TankLocation ,GetActorLocation());
	if (DistanceToTank < 1000.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}
