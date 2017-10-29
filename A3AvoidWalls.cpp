#include "A3AvoidWalls.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"
#include "WallUnit.h"
#include "GraphicsSystem.h"

A3AvoidWalls::A3AvoidWalls(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;
}

Steering* A3AvoidWalls::getSteering()
{
	for (int i = 0; i < gpGame->getUnitManager()->getNumberOfWalls(); i++)
	{
		// check for the collision type to see if any steering should be applied
		if (getRaycast(gpGame->getUnitManager()->GetWall(i)))
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

bool A3AvoidWalls::getRaycast(WallUnit* target)
{
	// calculate the ray using the first formula
	Vector2D point = mpMover->getPosition();
	float scalar = 100.0f;
	Vector2D direction = mpMover->getVelocity();

	// multiply by a distance
	direction = direction * scalar;

	// the result of the first formula
	Vector2D raycast = point + direction;

	int t = 0;

	// calculate the line of the box (?) using the second formula
	for (int i = 0; i < gpGame->getUnitManager()->getNumberOfWalls(); i++)
	{
		gpGame->getUnitManager()->GetWall(i)->getTopLeft() + ((gpGame->getUnitManager()->GetWall(i)->getTopRight() - gpGame->getUnitManager()->GetWall(i)->getTopLeft()) * t);
		gpGame->getUnitManager()->GetWall(i)->getTopLeft() + ((gpGame->getUnitManager()->GetWall(i)->getBottomLeft() - gpGame->getUnitManager()->GetWall(i)->getTopLeft()) * t);
		gpGame->getUnitManager()->GetWall(i)->getTopLeft() + ((gpGame->getUnitManager()->GetWall(i)->getTopRight() - gpGame->getUnitManager()->GetWall(i)->getBottomRight()) * t);
		gpGame->getUnitManager()->GetWall(i)->getTopLeft() + ((gpGame->getUnitManager()->GetWall(i)->getBottomLeft() - gpGame->getUnitManager()->GetWall(i)->getBottomRight()) * t);
	}
	GET_GAME->getUnitManager()->GetWall(0);

	return true;
}