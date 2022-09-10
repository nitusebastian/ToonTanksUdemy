// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

class AToonTanksPlayerController;
class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleCountDown();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
	
private:
	ATank* Tank;
	AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.0f;

	void HandleGameStart();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CountDown", meta = (AllowPrivateAccess = "true"))
	FTimerHandle CountDownTimer;

	int32 TargetTowers = 0;

	int32 GetTargetTowersCount();
	
};
