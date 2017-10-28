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
		target->getTopLeft().getX() < mpMover->getPosition().getX() + mpMover->getWidth() &&
		target->getTopLeft().getX() + target->getWidth() > mpMover->getPosition().getX() &&
		target->getTopLeft().getY() < mpMover->getPosition().getY() + mpMover->getHeight() &&
		target->getTopLeft().getY() + target->getHeight() > mpMover->getPosition().getY())
	{
		return true;
	}
	return false;
}

bool A2AvoidWalls::getRaycast(KinematicUnit* target)
{
	// calculate the ray using the first formula
	Vector2D point = mpMover->getPosition();
	float scalar = 100.0f;
	Vector2D direction = mpMover->getVelocity();
	// there isn't an overload for multiplying a scalar for a vector and I've had little success so here it is manually
	Vector2D scalarTimesDirection = Vector2D(direction.getX() * scalar, direction.getY() * scalar);

	// the result of the first formula
	Vector2D raycast = point + scalarTimesDirection;

	// calculate the line of the box (?) using the second formula
	GET_GAME->getUnitManager()->GetWall(0);

	return true;
}