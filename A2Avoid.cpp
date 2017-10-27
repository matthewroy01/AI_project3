#include "A2Avoid.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"

A2Avoid::A2Avoid(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;
}

Steering* A2Avoid::getSteering()
{
	for (int i = 1; i < GET_GAME->getUnitManager()->getNumberOfUnits(); i++)
	{
		if (getDistance(GET_GAME->getUnitManager()->GetUnit(i)) < 50 && mpMover != GET_GAME->getUnitManager()->GetUnit(i))
		{
 			// flee
			std::cout << "avoid" << std::endl;
			mLinear = mpMover->getPosition() - GET_GAME->getUnitManager()->GetUnit(i)->getPosition();

			mLinear.normalize();
			mLinear *= mpMover->getMaxVelocity();

			mpMover->setNewOrientation();
			mAngular = mpMover->getOrientation();

			return this;
		}
	}

	mLinear = Vector2D(0,0);
	mAngular = 0;
	return this;
}

float A2Avoid::getDistance(KinematicUnit* target)
{
	//std::cout << sqrt(pow(mpMover->getPosition().getX() - mpTarget->getPosition().getX(), 2.0f) + pow(mpMover->getPosition().getY() - mpTarget->getPosition().getY(), 2.0f)) << std::endl;
	return sqrt(pow(mpMover->getPosition().getX() - target->getPosition().getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target->getPosition().getY(), 2.0f));
}