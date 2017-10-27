#include "WanderAndSeek.h"
#include "KinematicUnit.h"
#include "Game.h"

WanderAndSeek::WanderAndSeek(KinematicUnit *pMover, KinematicUnit* pTarget, bool shouldFlee, int targetRadius)
	:mpMover(pMover)
	,mShouldFlee(shouldFlee)
	,mpTarget(pTarget)
	,mTargetRadius(targetRadius)
{
	mApplyDirectly = true;
}

Steering* WanderAndSeek::getSteering()
{
	if (mIsFleeing || getDistance() < mTargetRadius)
	{
		// flee
		if (mShouldFlee)
		{
			mLinear = mpMover->getPosition() - mpTarget->getPosition();
		}
		else
		{
			mLinear = mpTarget->getPosition() - mpMover->getPosition();
		}

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mIsFleeing = true;

		mpMover->setNewOrientation();
		mAngular = mpMover->getOrientation();
	}
	else
	{
		// wander
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() + (genRandomBinomial() * WAS_MAX_WANDER_ROTATION);
	}

	// stop fleeing if you are a safe distance away
	if (getDistance() > mTargetRadius * 2)
	{
		mIsFleeing = false;
	}

	return this;
}

float WanderAndSeek::getDistance()
{
	//std::cout << sqrt(pow(mpMover->getPosition().getX() - mpTarget->getPosition().getX(), 2.0f) + pow(mpMover->getPosition().getY() - mpTarget->getPosition().getY(), 2.0f)) << std::endl;
	return sqrt(pow(mpMover->getPosition().getX() - mpTarget->getPosition().getX(), 2.0f)
			  + pow(mpMover->getPosition().getY() - mpTarget->getPosition().getY(), 2.0f));
}