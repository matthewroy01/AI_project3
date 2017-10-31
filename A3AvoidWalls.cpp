#include "A3AvoidWalls.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"
#include "WallUnit.h"
#include "GraphicsSystem.h"

#include <math.h>

A3AvoidWalls::A3AvoidWalls(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;
	mPointFound = false;
}

Steering* A3AvoidWalls::getSteering()
{
	if (gpGame->getShouldAvoidWalls() == true)
	{
		for (int i = 0; i < gpGame->getUnitManager()->getNumberOfWalls(); i++)
		{
			// do the raycast and return the point of collision
			Vector2D colPoint = getRaycast(gpGame->getUnitManager()->GetWall(i));

			// check to see if the point of collision lines up with any of the edges of the walls
			if (colPoint != NULL)
			{
				if (colPoint.getX() == gpGame->getUnitManager()->GetWall(i)->getTopLeft().getX())
				{
					// seek left
					mLinear = Vector2D(colPoint.getX() - ESCAPE_STRENGTH, colPoint.getY()) - mpMover->getPosition();
				}
				else if (colPoint.getX() == gpGame->getUnitManager()->GetWall(i)->getBottomRight().getX())
				{
					// seek right
					mLinear = Vector2D(colPoint.getX() + ESCAPE_STRENGTH, colPoint.getY()) - mpMover->getPosition();
				}
				else if (colPoint.getY() == gpGame->getUnitManager()->GetWall(i)->getTopLeft().getY())
				{
					// seek up
					mLinear = Vector2D(colPoint.getX(), colPoint.getY() - ESCAPE_STRENGTH) - mpMover->getPosition();
				}
				else if (colPoint.getY() == gpGame->getUnitManager()->GetWall(i)->getBottomRight().getY())
				{
					// seek down
					mLinear = Vector2D(colPoint.getX(), colPoint.getY() + ESCAPE_STRENGTH) - mpMover->getPosition();
				}
				std::cout << "avoid wall" << std::endl;
			}
		}
	}

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();

	return this;
}

Vector2D A3AvoidWalls::getRaycast(WallUnit* target)
{
	mPoint = mpMover->getOrientationAsVector();
	mPoint.normalize();
	mPoint *= POINT_DIST;
	
	/*-----------------------------------------------------------------------------------------*/
	// code from Calum with permission, who showed me a tutorial for this but he lost the link
	/*-----------------------------------------------------------------------------------------*/
	{
		// the end point of the array
		float endOfRay[4] = { -mPoint.getX(), mPoint.getX(), -mPoint.getY(), mPoint.getY() };
		// the dimensions of the current box
		float currentBox[4] = {
						mpMover->getPosition().getX() - target->getTopLeft().getX(),
						target->getBottomRight().getX() - mpMover->getPosition().getX(),
						mpMover->getPosition().getY() - target->getTopLeft().getY(),
						target->getBottomRight().getY() - mpMover->getPosition().getY()
		};

		// we will return this to check to see if we are in the box
		float result = (float)-INT_MAX;

		// for each wall, check with ray
		for (int i = 0; i < gpGame->getUnitManager()->getNumberOfWalls(); i++)
		{
			float t = currentBox[i] / endOfRay[i];
			if (endOfRay[i] < 0 && result < t)
				result = t;
		}

		// return the point of collision or return null
		if (result <= 1 && result >= 0)
			return Vector2D(result * mPoint.getX() + mpMover->getPosition().getX(), result * mPoint.getY() + mpMover->getPosition().getY());
		else
			return NULL;
	}
}

float A3AvoidWalls::getDistance(Vector2D target)
{
	// return the distance between the mover and the target
	return sqrt(pow(mpMover->getPosition().getX() - target.getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target.getY(), 2.0f));
}