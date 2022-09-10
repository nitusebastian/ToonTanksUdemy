// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

private:
	FTimerHandle Timer;

	APawn* PlayerPawn;
	
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	bool IsPlayerTankInFireRange() const;

	virtual void HandleDestruction() override;
};
