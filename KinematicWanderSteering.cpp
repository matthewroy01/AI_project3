#include "KinematicWanderSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include <math.h>

KinematicWanderSteering::KinematicWanderSteering(KinematicUnit *pMover, KinematicUnit *pTarget, bool shouldFlee, float targetRadius)
:mpMover(pMover),
mpTarget(pTarget),
mShouldFlee(shouldFlee)
{
	mApplyDirectly = true;
	mTargetRadius = targetRadius;
	mShouldFlee = false;
}

Steering* KinematicWanderSteering::getSteering()
{
	if (isFleeing || getDistance() < mTargetRadius)
	{
		// flee
		mLinear = mpMover->getPosition() - mpTarget->getPosition();
		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
		isFleeing = true;
	}
	else
	{
		// wander
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() + (genRandomBinomial() * MAX_WANDER_ROTATION);
		//mpMover->setOrientation(mAngular);
	}

	// stop fleeing if you are a safe distance away
	if (getDistance() < mTargetRadius * 5)
	{
		isFleeing = false;
	}

	return this;
}

float KinematicWanderSteering::getDistance()
{
	std::cout << sqrt(pow(mpMover->getPosition().getX() - mpTarget->getPosition().getX(), 2.0f) + pow(mpMover->getPosition().getY() - mpTarget->getPosition().getY(), 2.0f)) << std::endl;
	return sqrt(pow(mpMover->getPosition().getX() - mpTarget->getPosition().getX(), 2.0f)
			  + pow(mpMover->getPosition().getY() - mpTarget->getPosition().getY(), 2.0f));
}