// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisInvader_Enemy.h"
#include "EngineUtils.h"
#include "TetrisInvader_EnemiesController.generated.h"

UCLASS()
class EMJ2020_API ATetrisInvader_EnemiesController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisInvader_EnemiesController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		float initialMoveTime;
	UPROPERTY(EditAnywhere)
		float moveX;
	UPROPERTY(EditAnywhere)
		float moveY;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ToggleMoveDown();
	void RemoveEnemy(ATetrisInvader_Enemy*);

private:
	UPROPERTY()
		USceneComponent* m_sceneComponent;
	UPROPERTY(EditAnywhere)
		TArray<ATetrisInvader_Enemy*> m_enemies;
	UPROPERTY(Transient)
		TArray<ATetrisInvader_Enemy*> m_deadEnemies;
	UPROPERTY(Transient)
		bool moveRight;
	UPROPERTY(Transient)
		float moveDown;
	UPROPERTY(Transient)
		float currentMoveTime;
	UPROPERTY(Transient)
		float currentMoveDownCooldown;
	UPROPERTY(Transient)
		int initialCount;
	UPROPERTY(Transient)
		float moveTime;
};
