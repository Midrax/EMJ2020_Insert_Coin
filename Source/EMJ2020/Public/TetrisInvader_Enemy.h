// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TetrisInvader_Bullet.h"
#include "Math/UnrealMathUtility.h"
#include "TetrisInvader_Enemy.generated.h"

class ATetrisInvader_EnemiesController;

UCLASS()
class EMJ2020_API ATetrisInvader_Enemy : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Transient)
		ATetrisInvader_EnemiesController* m_controller;

public:	
	// Sets default values for this actor's properties
	ATetrisInvader_Enemy();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* m_meshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* m_boxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector impulse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector torque;
	float RandomSign();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetController(ATetrisInvader_EnemiesController*);
	// Overlap
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
};
