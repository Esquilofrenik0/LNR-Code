#include "Hero.h"
#include "LNR/Network/Playor.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "LNR/Component/Action.h"
#include "LNR/Component/Inventory.h"
#include "LNR/Component/Equipment.h"
#include "LNR/Component/Trace.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "LNR/Item/Spawn.h"
#include "LNR/Object/Container.h"
#include "LNR/Item/Item.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Component/Attributes.h"
#include "Net/UnrealNetwork.h"


AHero::AHero()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	Inventory = CreateDefaultSubobject<UInventory>("Inventory");
	
	TPArm = CreateDefaultSubobject<USpringArmComponent>("TPArm");
	TPArm->SetupAttachment(RootComponent);
	TPArm->TargetArmLength = 300.0f;
	TPArm->bUsePawnControlRotation = true;
	TPCamera = CreateDefaultSubobject<UCameraComponent>("TPCamera");
	TPCamera->SetupAttachment(TPArm, USpringArmComponent::SocketName);
	TPCamera->bUsePawnControlRotation = false;
	TPCamera->SetAutoActivate(true);
	TPCamera->SetActive(true);

	FPArm = CreateDefaultSubobject<USpringArmComponent>("FPArm");
	FPArm->SetupAttachment(GetMesh(), "Head");
	FPArm->TargetArmLength = -10.0f;
	FPArm->bUsePawnControlRotation = true;
	FPCamera = CreateDefaultSubobject<UCameraComponent>("FPCamera");
	FPCamera->SetupAttachment(FPArm, USpringArmComponent::SocketName);
	FPCamera->bUsePawnControlRotation = false;
	FPCamera->SetAutoActivate(false);
	FPCamera->SetActive(false);
	
	WorldMapCamera = CreateDefaultSubobject<UCameraComponent>("WorldMapCamera");
	WorldMapCamera->SetAutoActivate(false);
	WorldMapCamera->SetActive(false);
	LocalMapLocation = FVector(0, 0, 100000);
	WorldMapLocation = FVector(0, 0, 600000);
	WorldMapActive = false;
	Container = nullptr;
	firstPerson = false;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	DefaultFieldOfView = 90;
	Npc = nullptr;
}

void AHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHero, Pitch);
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalRole() == ROLE_AutonomousProxy || GetNetMode() == NM_Standalone)
	{
		GetWorldTimerManager().ClearTimer(ClientTickTimer);
		GetWorldTimerManager().SetTimer(ClientTickTimer, this, &AHero::ClientTick, 0.1, true);
	}
	WorldMapCamera->SetWorldLocation(WorldMapLocation);
	WorldMapCamera->SetWorldRotation(FRotator(-90, 0, 0));
	ShowWorldMarkers(false);
}

void AHero::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	GetWorldTimerManager().ClearTimer(RegenerationHandle);
	GetWorldTimerManager().SetTimer(RegenerationHandle, Attributes, &UAttributes::Regenerate, 1, true);
}

void AHero::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	// Key Press
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHero::StartInteract);
	PlayerInputComponent->BindAction("Holster", IE_Pressed, this, &AHero::StartHolster);
	PlayerInputComponent->BindAction("WeaponSwap", IE_Pressed, this, &AHero::StartWeaponSwap);
	PlayerInputComponent->BindAction("CycleCameras", IE_Pressed, this, &AHero::CycleCameras);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AHero::StartDodge);
	PlayerInputComponent->BindAction("WorldMap", IE_Pressed, this, &AHero::StartWorldMap);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AHero::StartInventory);
	// Key Press and Release
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHero::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHero::StopJump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AHero::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AHero::StopCrouch);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHero::StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AHero::StopAttack);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHero::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AHero::StopSprint);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AHero::StartBlock);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &AHero::StopBlock);
	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHero::MoveRight);
	// Controller
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHero::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHero::LookUpAtRate);
}

void AHero::StartJump()
{
	if (Attributes->State == EState::Climbing) SetClimbing(false);
	else
	{
		if (GetCharacterMovement()->IsFalling()) GrabWall();
		else Jump();
	}
}

void AHero::StopJump()
{
	StopJumping();
}

void AHero::TurnAtRate(float Rate)
{
	if (!InventoryOpen && !WorldMapActive)
	{
		InputAxisYaw = Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds();
		AddControllerYawInput(InputAxisYaw);
		UpdateCompass();
	}
}

void AHero::LookUpAtRate(float Rate)
{
	if (!InventoryOpen && !WorldMapActive)
	{
		InputAxisPitch = Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds();
		AddControllerPitchInput(InputAxisPitch);
	}
}

void AHero::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		if (Attributes->State == EState::Climbing)
		{
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
			AddMovementInput(Direction, Value);
		}
		else
		{
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void AHero::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AHero::StartCrouch()
{
	Crouch();
}

void AHero::StopCrouch()
{
	UnCrouch();
}

void AHero::StartAttack()
{
	if (!InventoryOpen && !WorldMapActive)
	{
		SetAttacking(true);
		Attack();
	}
}

void AHero::StopAttack()
{
	SetAttacking(false);
}

void AHero::StartSprint()
{
	SetSprinting(true);
	Sprint();
}

void AHero::StopSprint()
{
	SetSprinting(false);
}

void AHero::StartBlock()
{
	SetBlocking(true);
	Block();
}

void AHero::StopBlock()
{
	SetBlocking(false);
}

void AHero::StartDodge()
{
	Dodge();
}

void AHero::StartHolster()
{
	if (Attributes->State == EState::Idle)
	{
		Equipment->CombatStance = !Equipment->CombatStance;
		Holster(Equipment->CombatStance);
	}
}

void AHero::StartWeaponSwap()
{
	if (WorldMapActive)
	{
		LocalMapActive = !LocalMapActive;
		if (LocalMapActive)
		{
			FVector loc = GetActorLocation();
			LocalMapLocation = FVector(GetActorLocation().X, GetActorLocation().Y, LocalMapLocation.Z);
			WorldMapCamera->SetWorldLocation(LocalMapLocation);
		}
		else WorldMapCamera->SetWorldLocation(WorldMapLocation);
	}
	else if (Attributes->State == EState::Idle) WeaponSwap();
}

void AHero::StartWorldMap()
{
	WorldMapActive = !WorldMapActive;
	if (WorldMapActive)
	{
		if (LocalMapActive)
		{
			FVector loc = GetActorLocation();
			LocalMapLocation = FVector(GetActorLocation().X, GetActorLocation().Y, LocalMapLocation.Z);
			WorldMapCamera->SetWorldLocation(LocalMapLocation);
		}
		else WorldMapCamera->SetWorldLocation(WorldMapLocation);

		TPCamera->SetActive(false);
		FPCamera->SetActive(false);
		WorldMapCamera->SetActive(true);
		SetInputModeUi(true);
		ShowWorldMarkers(true);
	}
	else
	{
		SetInputModeUi(false);
		ShowWorldMarkers(false);
		ResetCamera();
	}
}

void AHero::StartInventory()
{
	InventoryOpen = !InventoryOpen;
	ShowInventory(InventoryOpen);
	SetInputModeUi(InventoryOpen);
}

void AHero::ClientTick()
{
	TraceHud();
	if (Attributes->State == EState::Climbing) WallTimer();
}

void AHero::GrabWall()
{
	FHitResult hit = WallCheck();
	if (hit.GetActor()) SetClimbing(true);
}

void AHero::WallTimer()
{
	FHitResult hit = WallCheck();
	if (hit.GetActor())
	{
		Attributes->Stamina -= 1;
		FVector location = hit.Location + (hit.Normal.Rotation().Vector() * 45.0f);
		location.Z -= 90;
		SetActorLocation(location);
		FRotator normal = hit.Normal.Rotation();
		normal.Yaw += 180;
		SetActorRotation(normal);
		GetCharacterMovement()->Velocity.Set(0, 0, 0);
	}
	else
	{
		SetClimbing(false);
	}
}

FHitResult AHero::WallCheck()
{
	FVector start = GetActorLocation();
	start.Z += 90;
	FRotator rot = GetActorRotation();
	FVector end = start + (rot.Vector() * 100.0f);
	FHitResult hit = Trace->Line(start, end, 2.0f, false);
	return hit;
}

void AHero::SetClimbing(bool value)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (value)
		{
			Attributes->State = EState::Climbing;
			GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
			GetCharacterMovement()->MaxFlySpeed = 150.0f;
			GetCharacterMovement()->Velocity.Set(0, 0, 0);
		}
		else
		{
			Attributes->State = EState::Idle;
			GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->Velocity.Set(0, 0, 0);
			FRotator rt = GetActorRotation();
			rt.Pitch = 0;
			SetActorRotation(rt);
		}
	}
	else ServerSetClimbing(value);
}

void AHero::ServerSetClimbing_Implementation(bool value)
{
	SetClimbing(value);
}

void AHero::CycleCameras()
{
	firstPerson = !firstPerson;
	ResetCamera();
}

void AHero::ResetCamera()
{
	if (firstPerson)
	{
		WorldMapCamera->SetActive(false);
		TPCamera->SetActive(false);
		FPCamera->SetActive(true);
	}
	else
	{
		WorldMapCamera->SetActive(false);
		FPCamera->SetActive(false);
		TPCamera->SetActive(true);
	}
}

void AHero::StartInteract()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		
		if (AActor* hitActor = GetTraceHitActor())
		{
			Print(hitActor->GetName());
			if (ASpawn* itemObject = Cast<ASpawn>(hitActor))
			{
				Inventory->AddItem(itemObject->Item);
				itemObject->DestroyItem();
			}
			else if (AContainer* hitContainer = Cast<AContainer>(hitActor))
			{
				Container = hitContainer;
				OpenContainer(hitContainer);
			}
		}
	}
	else { ServerInteract(); }
}

void AHero::ServerInteract_Implementation()
{
	StartInteract();
}

AActor* AHero::GetTraceHitActor()
{
	FVector start;
	FRotator rot;
	if(AController* controller = GetController())
	{
		controller->GetPlayerViewPoint(start, rot);
		FVector end = start + (rot.Vector() * 600.0f);
		AActor* hitActor = Trace->Line(start, end, 0.0f, false).GetActor();
		return hitActor;
	}
	return nullptr;
}

void AHero::UseItem(UItem* item)
{
	if (GetLocalRole() == ROLE_Authority) item->UseItem(this);
	else ServerUseItem(item);
}

void AHero::TraceHud()
{
	if (AActor* hitActor = GetTraceHitActor())
	{
		if (ASpawn* spawn = Cast<ASpawn>(hitActor))
		{
			WriteWorldInfo(spawn->Item->PrintItemData());
			return;
		}
		else if (AContainer* container = Cast<AContainer>(hitActor))
		{
			WriteWorldInfo(container->PrintContainerData());
			return;
		}
	}
	ClearWorldInfo();
}

void AHero::ServerUseItem_Implementation(UItem* item)
{
	UseItem(item);
}

void AHero::DropInventory()
{
	FVector Location = GetActorLocation();;
	FRotator Rotation = GetActorRotation();
	FActorSpawnParameters SpawnInfo;

	AContainer* lootBag = GetWorld()->SpawnActor<AContainer>(Location, Rotation, SpawnInfo);
	lootBag->Container->SetStaticMesh(LootBagMesh);

	for (int i = 0; i < Inventory->Slots.Num(); i++)
	{
		lootBag->Inventory->Slots[i] = Inventory->Slots[i];
	}

	Inventory->Slots.Reset(Inventory->nSlots);
}

void AHero::Die()
{
	Attributes->State = EState::Dead;
	GetWorldTimerManager().ClearTimer(RegenerationHandle);
	GetWorldTimerManager().ClearTimer(ClientTickTimer);
	DropBag();
	StartRagdoll();
}

void AHero::DestroyCorpse()
{
	GetWorldTimerManager().ClearTimer(RespawnHandle);
	Player->Respawn();
}

void AHero::ServerSetFieldOfView_Implementation(float value)
{
	ClientSetFieldOfView(value);
}

void AHero::ClientSetFieldOfView_Implementation(float value)
{
	FPCamera->FieldOfView = value;
	TPCamera->FieldOfView = value;
}

void AHero::SetBlocking_Implementation(bool value)
{
	Attributes->Blocking = value;
}

void AHero::SetAttacking_Implementation(bool value)
{
	Attributes->Attacking = value;
}

void AHero::SetSprinting_Implementation(bool value)
{
	Attributes->Sprinting = value;
}
