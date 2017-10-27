#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "UnitDeleteRandomMessage.h"
#include "UnitManager.h"

UnitDeleteRandomMessage::UnitDeleteRandomMessage()
	:GameMessage(UNIT_DELETE_RANDOM_MESSAGE)
{
}

UnitDeleteRandomMessage::~UnitDeleteRandomMessage()
{
}

void UnitDeleteRandomMessage::process()
{
	gpGame->deleteRandomUnit();
}