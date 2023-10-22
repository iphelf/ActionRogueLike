// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YDummyTarget.generated.h"

class UYAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AYDummyTarget : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AYDummyTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY()
	UYAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnHealthChanged(AActor* Cause, UYAttributeComponent* OwningComp, float NewHealth, float Delta);
};

