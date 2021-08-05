#include "Npc.h"
#include "LNR/Body/Body.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LNR/Component/Attributes.h"

ANpc::ANpc()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception")));
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LooseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = FieldOfView;
	SightConfig->SetMaxAge(SightAge);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ANpc::OnPawnDetected);

	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	TargetKey = "Target";
	DestinationKey = "Destination";
}

void ANpc::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Body = Cast<ABody>(InPawn);
	BlackboardComponent->InitializeBlackboard(*BlackboardComponent->GetBlackboardAsset());
	BrainComponent->StartLogic();
}

void ANpc::BeginPlay()
{
	Super::BeginPlay();
}

void ANpc::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	if (!Body) Body = Cast<ABody>(GetOwner());
	if (Body)
	{
		for (int i = 0; i < DetectedPawns.Num(); i++)
		{
			if (ABody* body = Cast<ABody>(DetectedPawns[i]))
			{
				if (body->Attributes->State != EState::Dead && body->Attributes->Faction != Body->Attributes->Faction)
				{
					Target = body;
					BlackboardComponent->SetValueAsObject(TargetKey, Target);
					GetWorldTimerManager().ClearTimer(LooseTargetHandle);
					GetWorldTimerManager().SetTimer(LooseTargetHandle, this, &ANpc::CanSeeTarget, 2, true);
					Body->GetCharacterMovement()->MaxWalkSpeed = Body->RunSpeed;
					BehaviorTree->RestartTree();
					return;
				}
			}
		}
	}
}

void ANpc::CanSeeTarget()
{
	TArray<AActor*> PerceivedActors;
	GetPerceptionComponent()->GetCurrentlyPerceivedActors(GetPerceptionComponent()->GetDominantSense(), PerceivedActors);
	for (int i = 0; i < PerceivedActors.Num(); i++)
	{
		if (Cast<ABody>(PerceivedActors[i]) == Target && Target->Attributes->State != EState::Dead) return;
	}
	
	Target = nullptr;
	BlackboardComponent->ClearValue(TargetKey);
	BehaviorTree->RestartTree();
	GetWorldTimerManager().ClearTimer(LooseTargetHandle);
}
