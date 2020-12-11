// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisInvader_Enemy.h"
#include "EngineUtils.h"
#include "Components/AudioComponent.h"
#include "TetrisInvader_EnemiesController.generated.h"

UCLASS()
class EMJ2020_API ATetrisInvader_EnemiesController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisInvader_EnemiesController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* m_audioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* m_enemyBullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float introMoveTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float initialMoveTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fireTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float moveX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float moveY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float moveSpeedRatio;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite)
		bool isPlaying;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite)
		bool isAllEnemiesDied;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ToggleMoveDown();
	void RemoveEnemy(ATetrisInvader_Enemy*);

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* m_sceneComponent;
	UPROPERTY(VisibleAnywhere)
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
		float currentFireTime;
	UPROPERTY(Transient)
		float currentMoveDownCooldown;
	UPROPERTY(Transient)
		int initialCount;
	UPROPERTY(Transient)
		float moveTime;

};
