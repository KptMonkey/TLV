// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVEnemy.h"


// Sets default values
ATLVEnemy::ATLVEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}


