
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseComponent.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogJoyComponent, All, All)

UCLASS( ClassGroup=(Custom), meta=(ChildCannotTick), Abstract )
class JOYWAYTEST_API UBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseComponent(const FObjectInitializer& ObjectInitializer);
protected:
	void LogFloat(const float Value, const FString& Description);
	void LogString(const FString& Description);
	virtual void SetDefaults();
public:	

		
};
