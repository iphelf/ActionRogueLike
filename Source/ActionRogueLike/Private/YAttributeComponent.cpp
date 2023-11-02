// Fill out your copyright notice in the Description page of Project Settings.


#include "YAttributeComponent.h"

UYAttributeComponent::UYAttributeComponent()
{
	HealthMax = 100.0f;
	Health = HealthMax;
}

void UYAttributeComponent::BeginPlay()
{
	Health = HealthMax;
}

float UYAttributeComponent::GetHealthRatio() const
{
	return Health / HealthMax;
}

bool UYAttributeComponent::ChangeHealth(float Delta)
{
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}

bool UYAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

