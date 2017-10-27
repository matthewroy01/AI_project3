#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "UnitCreateSeekMessage.h"
#include "UnitManager.h"

UnitCreateSeekMessage::UnitCreateSeekMessage()
	:GameMessage(UNIT_CREATE_SEEK_MESSAGE)
{
}

UnitCreateSeekMessage::~UnitCreateSeekMessage()
{
}

void UnitCreateSeekMessage::process()
{
	gpGame->createSeekUnit();
}