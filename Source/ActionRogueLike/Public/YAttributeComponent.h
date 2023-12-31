// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YAttributeComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UYAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, Instigator, UYAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

public:
	UYAttributeComponent();

	void BeginPlay();

	float GetHealthRatio() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ChangeHealth(float Delta);

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float HealthMax;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
};

