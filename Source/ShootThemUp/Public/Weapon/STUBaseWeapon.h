// Aleksey Sigachev. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();
	
	virtual void StartFire();
	virtual void StopFire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceNaxDistance = 2500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float BulletSpread = 1.5f;

	virtual void BeginPlay() override;
	void MakeShot();

private:
	UFUNCTION()
	APlayerController* GetPlayerController() const;

	UFUNCTION()
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	UFUNCTION()
	FVector GetMuzzleWorldLocation() const;

	UFUNCTION()
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	UFUNCTION()
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	
	UFUNCTION()
	void MakeDamage(const FHitResult& HitResult);

	FTimerHandle ShotTimerHandle;

	
};
