#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "UnitManager.h"
#include "ChangeModeValueMessage.h"

ChangeModeValueMessage::ChangeModeValueMessage(int modeNum, bool add)
	:GameMessage(CHANGE_MODE_VALUE_MESSAGE),
	mModeNum(modeNum),
	mAdd(add)
{
}

ChangeModeValueMessage::~ChangeModeValueMessage()
{
}

void ChangeModeValueMessage::process()
{
	switch (mModeNum)
	{
		case 0 :
		{
			GET_GAME->getUnitManager()->changeAllVelocity(mAdd);
			break;
		}
		case 1 :
		{
			GET_GAME->getUnitManager()->changeAllRadius(mAdd);
			break;
		}
		case 2 :
		{
			GET_GAME->getUnitManager()->changeAllAngular(mAdd);
			break;
		}
		default:
		{
			std::cout << "ERROR: invalid mode value." << std::endl;
		}
	}
}