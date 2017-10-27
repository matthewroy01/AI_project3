#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "ChangeModeMessage.h"
#include "Game.h"
#include "UnitManager.h"

ChangeModeMessage::ChangeModeMessage(int mode)
	:GameMessage(CHANGE_MODE_MESSAGE),
	mMode(mode)
{
}

ChangeModeMessage::~ChangeModeMessage()
{
}

void ChangeModeMessage::process()
{
	GET_GAME->getUnitManager()->ChangeCurrentMode(mMode);
}