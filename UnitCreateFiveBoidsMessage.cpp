#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "UnitCreateFiveBoidsMessage.h"
#include "UnitManager.h"

UnitCreateFiveBoidsMessage::UnitCreateFiveBoidsMessage()
	:GameMessage(CREATE_FIVE_BOIDS_MESSAGE)
{
}

UnitCreateFiveBoidsMessage::~UnitCreateFiveBoidsMessage()
{
}

void UnitCreateFiveBoidsMessage::process()
{
	gpGame->createFiveBoids();
}