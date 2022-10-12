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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceNaxDistance = 2500.0f;

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
	
private:
};
