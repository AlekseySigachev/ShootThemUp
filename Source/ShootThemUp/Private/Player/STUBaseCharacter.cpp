// Aleksey Sigachev. All Right Reserved.


#include "Player/STUBaseCharacter.h"
#include "Components/InputComponent.h"
#include "Components/STUCharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SprintArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);
	//CameraComponent->bUsePawnControlRotation = true;

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("Health Component");
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(HealthTextComponent);
	//OnTakeAnyDamage.AddDynamic(this, &ASTUBaseCharacter::OnTakeAnyDamageHandle);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto Health = HealthComponent->GetHealth();
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

	TakeDamage(0.1f, FDamageEvent{}, Controller, this);

}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::TurnAround);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnEndRunning);
}

bool ASTUBaseCharacter::IsRunning() const
{
	return  WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetMovementDirection() const
{
	if(GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
	if(Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
	
}

void ASTUBaseCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount * MouseSpeed);
}

void ASTUBaseCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount * MouseSpeed);
}

void ASTUBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void ASTUBaseCharacter::OnEndRunning()
{
	WantsToRun = false;
}

