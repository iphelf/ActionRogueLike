// Fill out your copyright notice in the Description page of Project Settings.


#include "YHealthPotionPickup.h"
#include "YAttributeComponent.h"

AYHealthPotionPickup::AYHealthPotionPickup()
{
	HealingAmount = 30.0f;
}

bool AYHealthPotionPickup::IsPickable(AYCharacter* Character)
{
	return Super::IsPickable(Character)
		&& Character->GetAttribute()->GetHealthRatio() < 1.0f;
}

void AYHealthPotionPickup::Pickup(AYCharacter* Character)
{
	Character->GetAttribute()->ChangeHealth(HealingAmount);
	Super::Pickup(Character);
}

