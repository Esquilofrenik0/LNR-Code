#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "T_GetPatrolPoint.generated.h"

UCLASS()
class LNR_API UT_GetPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
