// Aleksey Sigachev. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
	ASTUAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AI", DisplayName = "Behaviour")
	UBehaviorTree* BehaviourTreeAsset;
protected:
	virtual void OnDeath() override;
	
private:
};
