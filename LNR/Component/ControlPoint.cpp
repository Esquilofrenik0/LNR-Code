#include "ControlPoint.h"
#include "Attributes.h"
#include "LNR/Body/Body.h"

UControlPoint::UControlPoint()
{
	Influence = 1;
	IncrementAmount = 0.01;
}

void UControlPoint::BeginPlay()
{
	GetAllFactions.Broadcast();
}

TSubclassOf<ACharacter> UControlPoint::GetSpawnTemplate()
{
	FFactionInfo info;
	if(ControlFaction.GetFactionInfo(info))
	{
		return info.SpawnTemplate;
	}
	return nullptr;
}

UTexture2D* UControlPoint::GetFactionIcon()
{
	FFactionInfo info;
	if(ControlFaction.GetFactionInfo(info))
	{
		return info.Icon;
	}
	return nullptr;
}

FLinearColor UControlPoint::GetFactionColor()
{
	FFactionInfo info;
	if(ControlFaction.GetFactionInfo(info))
	{
		return info.Color;
	}
	return FLinearColor();
}

void UControlPoint::AddBody(ABody* body)
{
	Bodies.Add(body);
	ContestingFaction = GetWinningFaction();
	if (ControlFaction == ContestingFaction)
	{
		if (Influence < 1)
		{
			StartIncreaseInfluence();
		}
	}
	else
	{
		StartDecreaseInfluence();
	}
}

void UControlPoint::RemoveBody(ABody* body)
{
	Bodies.Remove(body);
	ContestingFaction = GetWinningFaction();
	if (ControlFaction == ContestingFaction)
	{
		if (Influence < 1)
		{
			StartIncreaseInfluence();
		}
	}
	else
	{
		StartDecreaseInfluence();
	}
}

void UControlPoint::StartIncreaseInfluence()
{
	GetWorld()->GetTimerManager().ClearTimer(InfluenceTimer);
	GetWorld()->GetTimerManager().SetTimer(InfluenceTimer, this, &UControlPoint::IncreaseInfluence, 0.1f, true);
}

void UControlPoint::IncreaseInfluence()
{
	Influence += IncrementAmount;
	if(Influence >= 1)
	{
		Influence = 1;
		ContestingFaction = ControlFaction;
		GetWorld()->GetTimerManager().ClearTimer(InfluenceTimer);
	}
}

void UControlPoint::StartDecreaseInfluence()
{
	GetWorld()->GetTimerManager().ClearTimer(InfluenceTimer);
	GetWorld()->GetTimerManager().SetTimer(InfluenceTimer, this, &UControlPoint::DecreaseInfluence, 0.1f, true);
}

void UControlPoint::DecreaseInfluence()
{
	Influence -= IncrementAmount;
	if(Influence <= 0)
	{
		Influence = 0;
		ControlFaction = ContestingFaction;
		SetControl.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(InfluenceTimer);
		GetWorld()->GetTimerManager().SetTimer(InfluenceTimer, this, &UControlPoint::IncreaseInfluence, 0.1f, true);
	}
}


FFaction UControlPoint::GetWinningFaction()
{
	TArray<int> FactionPoints;
	FactionPoints.Init(0, Factions.Num());
	int i = 0;
	for (ABody* body : Bodies)
	{
		if(body->Attributes->State != EState::Dead) FactionPoints[GetFactionNum(body->Attributes->Faction)] += 1;
		i++;
	}
	if (i == 0 || (i == 1 && Bodies[0]->Attributes->Faction == ControlFaction)) return ControlFaction;
	
	int winningScore = FactionPoints[GetFactionNum(ControlFaction)];
	FFaction winningFaction = ControlFaction;
	int j;
	for (j = 0; j < FactionPoints.Num(); j++)
	{
		if (FactionPoints[j] > winningScore)
		{
			winningScore = FactionPoints[j];
			winningFaction = GetFactionValue(j);
		}
	}
	return winningFaction;
}

int UControlPoint::GetFactionNum(FFaction faction)
{
	for(int i=0; i<Factions.Num();i++)
	{
		if(Factions[i] == faction) return i;
	}
	return 0;
}

FFaction UControlPoint::GetFactionValue(int num)
{
	return Factions[num];
}
