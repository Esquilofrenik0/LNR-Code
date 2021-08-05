#include "Trace.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

void UTrace::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

FHitResult UTrace::Line(FVector start, FVector end, float drawTime, bool printName)
{
	FHitResult hit;
	FCollisionObjectQueryParams queryParams;
	FCollisionQueryParams traceParams;
	traceParams.AddIgnoredActor(GetOwner());
	if (drawTime > 0) { DrawDebugLine(GetWorld(), start, end, FColor::Orange, false, drawTime); }
	if (GetWorld()->LineTraceSingleByObjectType(OUT hit, start, end, queryParams, traceParams))
	{
		if (printName)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Hit: " + hit.GetActor()->GetName());
		}
	}	
	return hit;
}

FHitResult UTrace::Circle(FVector start, float radius, float drawTime, bool printName)
{
	FHitResult hit;
	FCollisionObjectQueryParams queryParams;
	FCollisionQueryParams traceParams;
	traceParams.AddIgnoredActor(GetOwner());
	if (drawTime > 0) { DrawDebugSphere(GetWorld(), start, radius, 32, FColor::Orange, false, drawTime); }
	if(GetWorld()->SweepSingleByObjectType(hit, start, start, FQuat::Identity, queryParams, FCollisionShape::MakeSphere(radius), traceParams))
	{
		if (printName)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Hit: " + hit.GetActor()->GetName());
		}
	}
	return hit;
}
