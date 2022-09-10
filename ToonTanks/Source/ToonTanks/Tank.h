// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category="Tank", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank", meta = (AllowPrivateAccess = "true"))
	double TurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank", meta = (AllowPrivateAccess = "true"))
	double TurretRotationRate;

	APlayerController* PlayerController;
public:
	APlayerController* GetPlayerController() const;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(float Value);
	void Turn(float Value);
	void RotateTurretByRelativeAmount(float X);

	ATank();
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;
};

inline APlayerController* ATank::GetPlayerController() const
{
	return PlayerController;
}
