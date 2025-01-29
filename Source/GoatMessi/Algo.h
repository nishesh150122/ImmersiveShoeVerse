#pragma once
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Algo.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GOATMESSI_API UOk : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UOk();

	// Overridden function to perform backface culling
	virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) override;
};
