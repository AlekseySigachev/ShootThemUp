// Aleksey Sigachev. All Right Reserved.


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/STUWeaponFXComponent.h"


ASTURifleWeapon::ASTURifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}

void ASTURifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot,
		TimeBetweenShots, true);
	MakeShot();
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
	if(!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}
	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 2.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5, 12, FColor::Blue, false, 5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	else
	{
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd,	FColor::Red, false, 3.0f, 0, 2.0f);
	}
	DecreaseAmmo();
}
bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) return false;
		
	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceNaxDistance;
	return true;
}

void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if(!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(),
		GetPlayerController(), this);
	UE_LOG(LogTemp, Display, TEXT("Bone is: %s"), *HitResult.BoneName.ToString());
}
