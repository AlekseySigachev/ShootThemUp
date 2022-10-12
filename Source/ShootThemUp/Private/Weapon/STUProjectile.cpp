// Aleksey Sigachev. All Right Reserved.


#include "Weapon/STUProjectile.h"

#include "AudioDevice.h"
#include "Kismet/GameplayStatics.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);

	SetRootComponent(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>
		(TEXT("ProjectileMovementComponent"));
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(ProjectileMovementComponent)
	check(CollisionComponent)
	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	//SetLifeSpan(LifeSeconds);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;
	ProjectileMovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		DamageAmount,
		GetActorLocation(),
		DamageRadius, UDamageType::StaticClass(),
		{GetOwner()},
		this,
		GetController(),
		DoFullDamage);

	DrawDebugSphere(
		GetWorld(),
		GetActorLocation(),
		DamageRadius,
		24,
		FColor::Red,
		false,
		LifeSeconds);

	Destroy();
}

AController* ASTUProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
