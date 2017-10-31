#include "Game.h"
#include "GameMessageManager.h"
#include "ToggleAvoidWallsMessage.h"

ToggleAvoidWallsMessage::ToggleAvoidWallsMessage()
	:GameMessage(END_GAME_MESSAGE)
{
}

ToggleAvoidWallsMessage::~ToggleAvoidWallsMessage()
{
}

void ToggleAvoidWallsMessage::process()
{
	GET_GAME->setShouldAvoidWalls(!GET_GAME->getShouldAvoidWalls());
}