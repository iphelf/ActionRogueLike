// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YGamePlayInterface.h"
#include "YItemChest.generated.h"


UCLASS()
class ACTIONROGUELIKE_API AYItemChest : public AActor, public IYGamePlayInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AYItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(EditAnywhere)
	double TargetPitch;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};

