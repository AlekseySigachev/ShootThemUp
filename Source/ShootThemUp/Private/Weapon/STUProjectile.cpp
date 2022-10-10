// Aleksey Sigachev. All Right Reserved.


#include "Weapon/STUProjectile.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	SetRootComponent(CollisionComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(ProjectileMovementComponent)
	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
	SetLifeSpan(5.0f);
}



