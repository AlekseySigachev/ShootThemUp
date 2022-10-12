// Aleksey Sigachev. All Right Reserved.


#include "Components/STUWeaponComponent.h"

#include "Animations/STUEquipFinishedAnimNotify.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapons();
	
	CurrentWeaponIndex = 0;
	InitAnimations();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Character) return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachToWeaponSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void USTUWeaponComponent::AttachToWeaponSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent,
                                               const FName& SocketName)
{
	if(!Weapon || !SceneComponent) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachToWeaponSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);		
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachToWeaponSocket(CurrentWeapon, Character->GetMesh(), WeaponEqipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontaget(EquipAnimMontage);
}

void USTUWeaponComponent::StartFire()
{
	if(!CanFire()) return;
	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon()
{
	if(!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::PlayAnimMontaget(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	Character->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations()
{
	if(!EquipAnimMontage) return;
	const auto NotifyEvents = EquipAnimMontage->Notifies;
	for(auto NotifyEvent : NotifyEvents)
	{
		auto EquipFinishNotify = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify);
		if(EquipFinishNotify)
		{
			EquipFinishNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEqiupFinished);
			break;
		}
	}
}

void USTUWeaponComponent::OnEqiupFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character || Character->GetMesh() != MeshComponent) return;
	
	EquipAnimInProgress = false;
}

bool USTUWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress;
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	
	Weapons.Empty();
}

