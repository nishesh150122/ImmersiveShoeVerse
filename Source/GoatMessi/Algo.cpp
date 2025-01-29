#include "Algo.h"

UOk::UOk()
{
	// Set the backface culling flag to true by default
	bReceivesDecals = true;
}

void UOk::OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport)
{
	// Call the parent function to update the transform
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);

	// Check if the transform update was not due to teleportation
	if (UpdateTransformFlags != EUpdateTransformFlags::None)
	{
		// The transform was updated due to movement of the mesh
		// Use the updated transform to get the new position and orientation of the mesh
		FVector MeshLocation = GetComponentLocation();
		FRotator MeshRotation = GetComponentRotation();

		// Use the mesh position and orientation to update the polygon normals
		SetRelativeLocationAndRotation(MeshLocation, MeshRotation);
	}

	// Get the view direction from the camera
	const FVector ViewDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetViewRotation().Vector();

	// Calculate the dot product of the view direction and the polygon's normal
	float DotProduct = FVector::DotProduct(GetForwardVector(), ViewDirection);

	// If the dot product is negative, the polygon is facing away from the camera
	// and can be culled
	if (DotProduct < 0.0f)
	{
		SetVisibility(false);

		// Log a message indicating that the polygon has been culled
		UE_LOG(LogTemp, Warning, TEXT("Polygon culled"));
	}
	else
	{
		SetVisibility(true);
	}
}
