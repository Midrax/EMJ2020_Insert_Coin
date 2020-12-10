// Fill out your copyright notice in the Description page of Project Settings.

#include "TetrisInvader_Enemy.h"
#include "TetrisInvader_EnemiesController.h"

// Sets default values
ATetrisInvader_Enemy::ATetrisInvader_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_meshComponent = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMesh"));
	m_meshComponent->SetEnableGravity(false);
	m_meshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	SetRootComponent(m_meshComponent);

	m_boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	m_boxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	m_boxComponent->SetGenerateOverlapEvents(true);
	m_boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATetrisInvader_Enemy::BeginOverlap);
	m_boxComponent->SetupAttachment(RootComponent);

	m_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	m_audioComponent->SetupAttachment(RootComponent);
	m_audioComponent->bAutoActivate = false;
}

void ATetrisInvader_Enemy::SetController(ATetrisInvader_EnemiesController* controller)
{
	m_controller = controller;
}

// Called when the game starts or when spawned
void ATetrisInvader_Enemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATetrisInvader_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void ATetrisInvader_Enemy::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Overlap
	//UE_LOG(LogClass, Warning, TEXT("%s: Got overlap with %s! (%s)"), *GetActorLabel(), *OtherActor->GetActorLabel(), *OtherActor->GetClass()->GetDescription());
	if (OtherActor->IsA(ATetrisInvader_Bullet::StaticClass()))
	{
		if (Cast<ATetrisInvader_Bullet>(OtherActor)->playerBullet)
		{
			UE_LOG(LogClass, Warning, TEXT("HIT!"));
			OtherActor->Destroy();
			m_controller->RemoveEnemy(this);
			m_meshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
			m_meshComponent->SetSimulatePhysics(true);
			m_meshComponent->AddImpulse(FVector(impulse.X, RandomSign() * impulse.Y, impulse.Z));
			m_meshComponent->AddTorqueInRadians(FVector(RandomSign() * torque.X, RandomSign() * torque.Y, RandomSign() * torque.Z));
			UMaterialInterface* Material = m_meshComponent->GetMaterial(0);
			UMaterialInstanceDynamic* matInstance = m_meshComponent->CreateDynamicMaterialInstance(0, Material);

			if (matInstance != nullptr)
				matInstance->SetScalarParameterValue("Darken", 0.9f);
			m_audioComponent->Play();
		}
	}
	else if (OtherActor->ActorHasTag(FName(TEXT("Bound"))))
	{
		m_controller->ToggleMoveDown();
	}
}

float ATetrisInvader_Enemy::RandomSign()
{
	return FMath::RandRange(0, 2) == 0 ? -1.f : 1.f;
}

