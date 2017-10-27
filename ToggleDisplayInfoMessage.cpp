#include "Game.h"
#include "GameMessageManager.h"
#include "ToggleDisplayInfoMessage.h"
#include "UIManager.h"

ToggleDisplayInfoMessage::ToggleDisplayInfoMessage()
	:GameMessage(TOGGLE_DISPLAY_INFO_MESSAGE)
{
}

ToggleDisplayInfoMessage::~ToggleDisplayInfoMessage()
{
}

void ToggleDisplayInfoMessage::process()
{
	GET_GAME->getUIManager()->toggleShouldDisplayInfo();
}