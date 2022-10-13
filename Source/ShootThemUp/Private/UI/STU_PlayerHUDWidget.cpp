// Aleksey Sigachev. All Right Reserved.


#include "UI/STU_PlayerHUDWidget.h"

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"


float USTU_PlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USTUHealthComponent>(Component);
	if(!HealthComponent) return 0.0f;
	return HealthComponent->GetHealthPercent();
}

bool USTU_PlayerHUDWidget::GetWeaponUiData(FWeaponUIData& UIData) const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return false;

	const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	if(!WeaponComponent) return false;
	return WeaponComponent->GetWeaponUIData(UIData);
}