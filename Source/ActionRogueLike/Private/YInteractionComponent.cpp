// Fill out your copyright notice in the Description page of Project Settings.


#include "YInteractionComponent.h"
#include "YGamePlayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UYInteractionComponent::UYInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UYInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UYInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UYInteractionComponent::DoPrimaryInteract()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	AActor* InteractionActor;
	{
		FVector Start;
		FVector End;
		{
			FRotator EyesRotator;
			OwnerPawn->GetActorEyesViewPoint(Start, EyesRotator);
			End = Start + EyesRotator.Vector() * 300.0;
		}
		auto QueryParams{ FCollisionObjectQueryParams::DefaultObjectQueryParam };
		QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		FCollisionShape CollisionShape;
		float Radius{ 30.0f };
		CollisionShape.SetSphere(Radius);

		TArray<FHitResult> HitResults;
		bool bHit = GetWorld()->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, QueryParams, CollisionShape);
		FHitResult* FirstValidHitResult{ HitResults.FindByPredicate([](const FHitResult& HitResult) {
			AActor* HitActor = HitResult.GetActor();
			return HitActor && HitActor->Implements<UYGamePlayInterface>();
			}) };
		bHit = bHit && FirstValidHitResult;

		FColor TraceColor{ bHit ? FColor::Green : FColor::Red };
		DrawDebugLine(GetWorld(), Start, End, TraceColor, false, 2.0f, 0, 2.0f);
		if (!bHit) {
			return;
		}

		InteractionActor = FirstValidHitResult->GetActor();
		DrawDebugSphere(GetWorld(), FirstValidHitResult->ImpactPoint, Radius, 32, TraceColor, false, 2.0f, 0, 2.0f);
	}

	IYGamePlayInterface::Execute_Interact(InteractionActor, OwnerPawn);
}

