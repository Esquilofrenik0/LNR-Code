#include "WeaponComponent.h"
#include "Weapon.h"

void UWeaponComponent::SetupAttachments(UWeapon* nWeapon)
{
	if(nWeapon != nullptr)
	{
		Weapon = nWeapon;
		SetSkeletalMesh(Weapon->SkeletalMesh);
		
		Attachments.Reset();
		for(UStaticMesh* attachment : Weapon->Attachments)
		{
			UStaticMeshComponent* component = NewObject<UStaticMeshComponent>();
			component->SetStaticMesh(attachment);
			FName socketName = "FrontSight";
			if(component->DoesSocketExist("RearAimpoint")) socketName = "RearSight";
			if(component->DoesSocketExist("FrontAimpoint")) socketName = "FrontSight";
			component->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform, socketName);
			Attachments.Add(component);
		}
	}
	else
	{
		for(UStaticMeshComponent* component : Attachments) component->DestroyComponent();
		Attachments.Reset();
		Weapon = nullptr;
		SetSkeletalMesh(nullptr);
	}
}
