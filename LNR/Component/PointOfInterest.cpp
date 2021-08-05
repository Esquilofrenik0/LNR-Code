#include "PointOfInterest.h"
#include "Components/WidgetComponent.h"

UPointOfInterest::UPointOfInterest()
{
	Actor = GetOwner();
	WorldMapIcon = CreateDefaultSubobject<UWidgetComponent>("WorldMapIcon");
	WorldMapIcon->SetupAttachment(this);
}

void UPointOfInterest::BeginPlay()
{
	Super::BeginPlay();
	Actor = GetOwner();
	WorldMapIcon->SetWorldLocation(Actor->GetActorLocation());
}

void UPointOfInterest::SetMarker()
{
	OnSetMarker.Broadcast();
}

void UPointOfInterest::ShowMarker()
{
	OnShowMarker.Broadcast();
}

void UPointOfInterest::HideMarker()
{
	OnHideMarker.Broadcast();
}
