#include "Game.h"
#include "GameMessageManager.h"
#include "SaveValuesMessage.h"

SaveValuesMessage::SaveValuesMessage()
	:GameMessage(END_GAME_MESSAGE)
{
}

SaveValuesMessage::~SaveValuesMessage()
{
}

void SaveValuesMessage::process()
{
	GET_GAME->saveValues();
}