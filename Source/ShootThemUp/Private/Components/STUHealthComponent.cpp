// Aleksey Sigachev. All Right Reserved.


#include "Components/STUHealthComponent.h"


USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	if(ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}
void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(LogTemp, Display, TEXT("Damage: %f, healt: %f "), Damage, GetHealth())
}

