#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "UnitManager.h"

PlayerMoveToMessage::PlayerMoveToMessage( const Vector2D& pos )
:GameMessage(PLAYER_MOVETO_MESSAGE)
,mPos(pos)
{
}

PlayerMoveToMessage::~PlayerMoveToMessage()
{
}

void PlayerMoveToMessage::process()
{
	//gpGame->getPlayerUnit()->arrive(mPos);
	gpGame->getUnitManager()->GetUnit(0)->arrive(mPos);
}

