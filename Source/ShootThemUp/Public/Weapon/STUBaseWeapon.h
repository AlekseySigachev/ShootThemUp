// Aleksey Sigachev. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon",
		meta = (EditConditionHides = "!Infinite"), meta = (EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();
	
	virtual void StartFire();
	virtual void StopFire();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceNaxDistance = 2500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo{15, 10, false};
	
	UFUNCTION()
	APlayerController* GetPlayerController() const;

	UFUNCTION()
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	UFUNCTION()
	FVector GetMuzzleWorldLocation() const;

	UFUNCTION()
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	UFUNCTION()
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	
	virtual void BeginPlay() override;
	virtual void MakeShot();

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	void ChangeClip();
	void LogAmmo();
	
private:
	FAmmoData CurrentAmmo;
};
