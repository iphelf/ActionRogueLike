// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/YAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

void AYAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (PlayerCharacter) {
		//GetBlackboardComponent()->SetValueAsVector("MoveToLocation", PlayerCharacter->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerCharacter);
	}
}

