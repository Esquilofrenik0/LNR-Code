#include "T_AttackTarget.h"
#include "GameplayTagsManager.h"
#include "LNR/Body/Npc.h"
#include "LNR/Body/Body.h"
#include "LNR/Component/Action.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "LNR/Ability/Ability.h"
#include "LNR/Component/Attributes.h"

EBTNodeResult::Type UT_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANpc* npc = Cast<ANpc>(OwnerComp.GetAIOwner());
	ABody* body = Cast<ABody>(npc->GetPawn());
	if(!body->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		body->Attributes->Combo = FMath::RandRange(0, body->Attributes->MaxCombo-1);
		body->Attack();
	}
	return EBTNodeResult::Succeeded;
}
