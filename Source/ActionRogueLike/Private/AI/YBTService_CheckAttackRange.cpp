// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/YBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UYBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp{ OwnerComp.GetBlackboardComponent() };
	if (!ensure(BlackboardComp)) return;
	AActor* TargetActor{ Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName)) };
	if (!TargetActor) return;
	APawn* AIPawn{ OwnerComp.GetAIOwner()->GetPawn() };
	if (!ensure(AIPawn)) return;
	bool bWithinAttackRange{ true };
	bWithinAttackRange = bWithinAttackRange && FVector::Distance(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());
	bWithinAttackRange = bWithinAttackRange && OwnerComp.GetAIOwner()->LineOfSightTo(TargetActor);
	BlackboardComp->SetValueAsBool(WithinAttackRangeKey.SelectedKeyName, bWithinAttackRange);
}

