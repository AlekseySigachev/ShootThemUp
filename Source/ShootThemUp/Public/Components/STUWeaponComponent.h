// Aleksey Sigachev. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

class ASTUBaseWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();
	
	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount);
	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEqipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* EquipAnimMontage;

	
private:	
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;
	
	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	UPROPERTY()
	int32 CurrentWeaponIndex = 0;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	void AttachToWeaponSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void SpawnWeapons();

	UFUNCTION()
	void EquipWeapon(int32 WeaponIndex);

	virtual  void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	
	void OnEqiupFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip(ASTUBaseWeapon* AmmoEmptyWeapon);
	void ChangeClip();
	

};
