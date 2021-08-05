#include "T_IsAlive.h"
#include "LNR/Body/Npc.h"
#include "LNR/Body/Body.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "LNR/Component/Attributes.h"

EBTNodeResult::Type UT_IsAlive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANpc* npc = Cast<ANpc>(OwnerComp.GetAIOwner()))
	{
		if (ABody* body = Cast<ABody>(npc->GetPawn()))
		{
			if (body->Attributes->State != EState::Dead)
			{
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
