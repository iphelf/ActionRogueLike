// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YItemPickup.h"
#include "YHealthPotionPickup.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AYHealthPotionPickup : public AYItemPickup
{
	GENERATED_BODY()

public:
	AYHealthPotionPickup();

protected:
	virtual bool IsPickable(AYCharacter* Character)override;
	virtual void Pickup(AYCharacter* Character) override;

	UPROPERTY(EditAnywhere)
	float HealingAmount;
};
