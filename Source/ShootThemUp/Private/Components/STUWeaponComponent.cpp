// Aleksey Sigachev. All Right Reserved.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapons();
	
	CurrentWeaponIndex = 0;
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
}

void USTUWeaponComponent::StartFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
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

