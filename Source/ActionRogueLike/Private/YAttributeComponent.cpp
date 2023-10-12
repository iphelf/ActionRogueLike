// Fill out your copyright notice in the Description page of Project Settings.


#include "YAttributeComponent.h"

UYAttributeComponent::UYAttributeComponent()
{
	Health = 100.0f;
}

bool UYAttributeComponent::ChangeHealth(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}

