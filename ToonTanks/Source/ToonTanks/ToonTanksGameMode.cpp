// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnableState(false);
		}
		GameOver(false);
	}
	else if(ATurret* DestroyedTower = Cast<ATurret>(DeadActor))
	{
		DestroyedTower->HandleDestruction();

		TargetTowers--;

		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	TargetTowers = GetTargetTowersCount();
	
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	//GetWorldTimerManager().SetTimer(CountDownTimer, this, &AToonTanksGameMode::HandleCountDown, 1.0f, true, 1.f);
	
	if (ToonTanksPlayerController != nullptr)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);

		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true);
		FTimerHandle PlayerEnableTimerHandle;
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, 3.f, false);
	}
}

int32 AToonTanksGameMode::GetTargetTowersCount()
{
	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), ActorArray);
	return ActorArray.Num();
}
