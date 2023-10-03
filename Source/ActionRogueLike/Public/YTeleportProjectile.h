// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YProjectile.h"
#include "YTeleportProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AYTeleportProjectile : public AYProjectile
{
	GENERATED_BODY()

public:
	AYTeleportProjectile();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void Explode();
	void Teleport();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ExplodeEffectComp;

	UPROPERTY(EditAnywhere)
	float TravelTime;
	FTimerHandle TravelTimerHandle;

	UPROPERTY(EditAnywhere)
	float ExplodeTime;
	FTimerHandle ExplodeTimerHandle;
};
