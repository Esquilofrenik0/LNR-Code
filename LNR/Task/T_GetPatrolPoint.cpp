#include "T_GetPatrolPoint.h"
#include "LNR/Body/Npc.h"
#include "LNR/Body/Body.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UT_GetPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ANpc* npc = Cast<ANpc>(OwnerComp.GetAIOwner());
	ABody* body = Cast<ABody>(npc->GetPawn());
	body->GetCharacterMovement()->MaxWalkSpeed = body->WalkSpeed;
	if(UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		FNavLocation Result;
		if(NavSys->GetRandomReachablePointInRadius(body->GetActorLocation(), 50000, Result))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("Destination", Result.Location);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
