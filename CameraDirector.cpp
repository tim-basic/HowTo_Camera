// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "EngineGlobals.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// float to define starting point of count down
	const float TimeBetweenCameraChanges = 2.0f;
	// float to define the value used to blend scenes.
	const float SmoothBlendTime = 0.75f;

	// minuses 2.0 with DeltaTime;
	TimeToNextCameraChange -= DeltaTime;
	//convert TimeToNext... to an FString to be used in the following function, which logs a debug message
	FString var = FString::SanitizeFloat(TimeToNextCameraChange);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, var);

	// if TimeToNextCameraChange is less than/equal to 0
	if (TimeToNextCameraChange <= 0.0f)
	{
		// Adds Between change time
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// Don't really know what this does.
		// Find the actor that handles control for the local player.
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		// If OurPlayerController != NULL
		if (OurPlayerController)
		{
			// If OPC->GetViewTarget() != CameraOne and CameraOne is not a NULL pointer
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{	
				// Set camera view to camera one
				// blend to camera one.
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}

			// else if not OPC != CameraTwo and CameraTwo not a NULL pointer...
			else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			{
				// Blend smoothly to camera two.
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
		}
	}

}

