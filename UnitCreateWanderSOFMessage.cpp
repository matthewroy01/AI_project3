#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "UnitCreateWanderSOFMessage.h"
#include "UnitManager.h"

UnitCreateWanderSOFMessage::UnitCreateWanderSOFMessage(bool shouldFlee)
	:GameMessage(UNIT_CREATE_ARRIVE_MESSAGE),
	mShouldFlee(shouldFlee)
{
}

UnitCreateWanderSOFMessage::~UnitCreateWanderSOFMessage()
{
}

void UnitCreateWanderSOFMessage::process()
{
	gpGame->createWanderSOFUnit(mShouldFlee);
}