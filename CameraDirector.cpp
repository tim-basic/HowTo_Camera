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
	// float to define the value used to 
	const float SmoothBlendTime = 0.75f;
	TimeToNextCameraChange -= DeltaTime;
	FString var = FString::SanitizeFloat(TimeToNextCameraChange);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, var);
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// Find the actor that handles control for the local player.
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				// Cut instantly to camera one.
				OurPlayerController->SetViewTarget(CameraOne);
			}
			else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			{
				// Blend smoothly to camera two.
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
		}
	}

}

