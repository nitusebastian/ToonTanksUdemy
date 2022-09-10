// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"


UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	virtual void HandleDestruction();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	void PlayDeathExplosion(FVector Location);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank", meta = (AllowPrivateAccess = "true"))
	float TurretRotationSpeed = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FX", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DeathExplosionFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FX", meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> DestroyCameraShakeClass;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void RotateTurret(FVector LookAtTarget) const;

	void Fire();

	
};
