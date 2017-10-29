#include "A2AvoidWalls.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"
#include "WallUnit.h"
#include "GraphicsSystem.h"

A2AvoidWalls::A2AvoidWalls(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;
}

Steering* A2AvoidWalls::getSteering()
{
	for (int i = 0; i < gpGame->getUnitManager()->getNumberOfWalls(); i++)
	{
		// check for the collision type to see if any steering should be applied
		if (getBoxOnBox(gpGame->getUnitManager()->GetWall(i)))
		{
			// flee
			std::cout << "avoid wall" << std::endl;
			mLinear = Vector2D(gpGame->getGraphicsSystem()->getWidth() / 2, gpGame->getGraphicsSystem()->getHeight() / 2) - mpMover->getPosition();

			mLinear.normalize();
			mLinear *= mpMover->getMaxVelocity();

			mpMover->setNewOrientation();
			mAngular = mpMover->getOrientation();

			return this;
		}
	}

	mLinear = Vector2D(0, 0);
	mAngular = 0;
	return this;
}

bool A2AvoidWalls::getBoxOnBox(WallUnit* target)
{
	if (
		mpMover->getPosition().getX() > target->getTopLeft().getX() &&
		mpMover->getPosition().getX() < target->getTopRight().getX() &&
		mpMover->getPosition().getY() > target->getTopLeft().getY() &&
		mpMover->getPosition().getY() < target->getBottomRight().getY()
		)
		/*target->getTopLeft().getX() < mpMover->getPosition().getX() + mpMover->getWidth() &&
		target->getTopLeft().getX() + target->getWidth() > mpMover->getPosition().getX() &&
		target->getTopLeft().getY() < mpMover->getPosition().getY() + mpMover->getHeight() &&
		target->getTopLeft().getY() + target->getHeight() > mpMover->getPosition().getY())*/
	{
		return true;
	}
	return false;
}