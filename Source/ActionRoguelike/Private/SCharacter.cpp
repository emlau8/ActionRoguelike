// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("Blackhole", IE_Pressed, this, &ASCharacter::Blackhole);
	
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector() * Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)
	
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	
}

void ASCharacter::Blackhole()
{
	PlayAnimMontage(BlackholeAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::Blackhole_TimeElapsed, 0.2f);
	
}

void ASCharacter::Dash()
{
	PlayAnimMontage(DashAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::Dash_TimeElapsed, 0.2f);
	
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	// Get Spawn Projectile Location
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	// Trace Start from the camera location
	FVector TraceStart = CameraComp->GetComponentLocation();
	// Extend Trace 100000 units forward
	FVector TraceEnd = TraceStart + (CameraComp->GetForwardVector()* 100000);

	// Perform line trace to interact with environment
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore the character itself
	QueryParams.bTraceComplex = true; // Do a precise trace
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECC_Visibility);
	// Set Debug Line Color
	FColor LineColor = bHit ? FColor::Green : FColor::Red;
	// Set the target location
	FVector TargetLocation = bHit ? HitResult.Location : TraceEnd;
	
	// Calculate the direction vector
	FVector Direction = (TargetLocation - HandLocation).GetSafeNormal();

	// Create the NewRotation
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	
	// Set Transform for spawning projectile
	FTransform SpawnTM = FTransform(NewRotation,HandLocation);
	
	//Hand Collision Override
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	// Spawn Projectile
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

	// Draw Debug Lines 
	//DrawDebugLine(GetWorld(), HandLocation, TraceEnd, LineColor, false, 2.0f, 0, 2.0f);
}

void ASCharacter::Blackhole_TimeElapsed()
{
	// Get Spawn Projectile Location
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	// Trace Start from the camera location
	FVector TraceStart = CameraComp->GetComponentLocation();
	// Extend Trace 100000 units forward
	FVector TraceEnd = TraceStart + (CameraComp->GetForwardVector()* 100000);

	// Perform line trace to interact with environment
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore the character itself
	QueryParams.bTraceComplex = true; // Do a precise trace
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECC_Visibility);
	// Set Debug Line Color
	FColor LineColor = bHit ? FColor::Green : FColor::Red;
	// Set the target location
	FVector TargetLocation = bHit ? HitResult.Location : TraceEnd;
	
	// Calculate the direction vector
	FVector Direction = (TargetLocation - HandLocation).GetSafeNormal();

	// Create the NewRotation
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	
	// Set Transform for spawning projectile
	FTransform SpawnTM = FTransform(NewRotation,HandLocation);
	
	//Hand Collision Override
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	// Spawn Projectile
	GetWorld()->SpawnActor<AActor>(BlackholeClass, SpawnTM, SpawnParams);

	// Draw Debug Lines 
	//DrawDebugLine(GetWorld(), HandLocation, TraceEnd, LineColor, false, 2.0f, 0, 2.0f);
}

void ASCharacter::Dash_TimeElapsed()
{
	// Get Spawn Projectile Location
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	// Trace Start from the camera location
	FVector TraceStart = CameraComp->GetComponentLocation();
	// Extend Trace 100000 units forward
	FVector TraceEnd = TraceStart + (CameraComp->GetForwardVector()* 100000);

	// Perform line trace to interact with environment
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore the character itself
	QueryParams.bTraceComplex = true; // Do a precise trace
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECC_Visibility);
	// Set Debug Line Color
	FColor LineColor = bHit ? FColor::Green : FColor::Red;
	// Set the target location
	FVector TargetLocation = bHit ? HitResult.Location : TraceEnd;
	
	// Calculate the direction vector
	FVector Direction = (TargetLocation - HandLocation).GetSafeNormal();

	// Create the NewRotation
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	
	// Set Transform for spawning projectile
	FTransform SpawnTM = FTransform(NewRotation,HandLocation);
	
	//Hand Collision Override
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	// Spawn Projectile
	GetWorld()->SpawnActor<AActor>(DashClass, SpawnTM, SpawnParams);

	// Draw Debug Lines 
	//DrawDebugLine(GetWorld(), HandLocation, TraceEnd, LineColor, false, 2.0f, 0, 2.0f);
}
