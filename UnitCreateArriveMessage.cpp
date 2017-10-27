#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "UnitCreateArriveMessage.h"
#include "UnitManager.h"

UnitCreateArriveMessage::UnitCreateArriveMessage()
	:GameMessage(UNIT_CREATE_ARRIVE_MESSAGE)
{
}

UnitCreateArriveMessage::~UnitCreateArriveMessage()
{
}

void UnitCreateArriveMessage::process()
{
	gpGame->createArriveUnit();
}