// Aleksey Sigachev. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "STUProjectile.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjectile();

	void SetShotDirection(const FVector& Direction)
	{
		ShotDirection = Direction;
	}
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	virtual void BeginPlay() override;

private:
	FVector ShotDirection;
};
