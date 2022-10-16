// Aleksey Sigachev. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
public:
	/**
	 *@return 
	 */
	ASTURifleWeapon();
	
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VFX")
	USTUWeaponFXComponent* WeaponFXComponent;
	
	UFUNCTION()
	void MakeDamage(const FHitResult& HitResult);
	
	virtual  void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	virtual void BeginPlay() override;
	
private:
	FTimerHandle ShotTimerHandle;
};
