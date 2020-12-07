// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisInvader_EnemiesController.h"

// Sets default values
ATetrisInvader_EnemiesController::ATetrisInvader_EnemiesController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_sceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    currentMoveDownCooldown = 0;
    initialCount = 0;
    moveTime = 0;
}

// Called when the game starts or when spawned
void ATetrisInvader_EnemiesController::BeginPlay()
{
	Super::BeginPlay();

    for (TActorIterator<ATetrisInvader_Enemy> CharacterItr(GetWorld()); CharacterItr; ++CharacterItr)
    {
        ATetrisInvader_Enemy* Enemy = *CharacterItr;
        //UE_LOG(LogTemp, Warning, TEXT("Character Initial Location: %s"), *Enemy->GetActorLocation().ToString());
        Enemy->SetController(this);
        m_enemies.Add(Enemy);
    }
    initialCount = m_enemies.Num();
    currentMoveTime = initialMoveTime;
}

// Called every frame
void ATetrisInvader_EnemiesController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    moveTime += DeltaTime;
    currentMoveDownCooldown += DeltaTime;

    if (moveTime > currentMoveTime)
    {
        moveTime = 0;
        FVector movement;
        if (moveDown)
        {
            movement = FVector(0, 0, -moveY);
            moveDown = false;
        }
        else
        {
            if (moveRight)
            {
                movement = FVector(0, moveX, 0);
            }
            else
            {
                movement = FVector(0, -moveX, 0);
            }
        }

        for (ATetrisInvader_Enemy* Enemy : m_deadEnemies)
        {
            m_enemies.Remove(Enemy);
        }

        for (ATetrisInvader_Enemy* Enemy : m_enemies)
        {
            Enemy->AddActorWorldOffset(movement, true);
        }
    }

}

void ATetrisInvader_EnemiesController::ToggleMoveDown()
{
    if (currentMoveDownCooldown > 0.5f)
    {
        moveDown = true;
        moveRight = !moveRight;
        currentMoveDownCooldown = 0.f;
    }
}

void ATetrisInvader_EnemiesController::RemoveEnemy(ATetrisInvader_Enemy* enemy)
{
    if (m_enemies.Contains(enemy))
    {
        //m_enemies.Remove(enemy);
        m_deadEnemies.Add(enemy);
    }
    currentMoveTime = initialMoveTime - ((1 - ((float) m_enemies.Num() / initialCount * 0.6f)) * initialMoveTime);
    UE_LOG(LogClass, Warning, TEXT("currentMoveTime: %f"), currentMoveTime);
}
