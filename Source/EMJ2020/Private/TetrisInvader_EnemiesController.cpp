// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisInvader_EnemiesController.h"

// Sets default values
ATetrisInvader_EnemiesController::ATetrisInvader_EnemiesController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_sceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(m_sceneComponent);
    m_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    m_audioComponent->SetupAttachment(RootComponent);
    m_audioComponent->bAutoActivate = false;

    currentMoveDownCooldown = 0;
    initialCount = 0;
    moveTime = 0;
    isPlaying = false;
    isAllEnemiesDied = false;
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
    currentFireTime = 0;
}

// Called every frame
void ATetrisInvader_EnemiesController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (isPlaying)
    {
        moveTime += DeltaTime;
        currentMoveDownCooldown += DeltaTime;
        currentFireTime += DeltaTime;

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

            isAllEnemiesDied = (m_enemies.Num() == 0);

            for (ATetrisInvader_Enemy* Enemy : m_enemies)
            {
                Enemy->AddActorWorldOffset(movement, true);
            }
        }

        if (currentFireTime > fireTime && m_enemies.Num() > 0)
        {
            currentFireTime = 0;
            UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BPTetrisInvader_EnemyBullet")));

            UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
            if (!SpawnActor)
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
                return;
            }

            UClass* SpawnClass = SpawnActor->StaticClass();
            if (SpawnClass == NULL)
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
                return;
            }

            UWorld* World = GetWorld();
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, m_enemies[FMath::RandRange(0, m_enemies.Num() - 1)]->GetActorLocation(), GetActorRotation(), SpawnParams);
            m_audioComponent->Play();
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
    currentMoveTime = initialMoveTime - ((1 - ((float) m_enemies.Num() / initialCount * moveSpeedRatio)) * initialMoveTime);
    UE_LOG(LogClass, Warning, TEXT("currentMoveTime: %f"), currentMoveTime);
}

