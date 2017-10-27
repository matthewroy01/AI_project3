#include "A2SeekOrFlee.h"
#include "KinematicUnit.h"
#include "Game.h"

A2SeekOrFlee::A2SeekOrFlee(KinematicUnit *pMover, KinematicUnit* pTarget, bool shouldFlee, int targetRadius)
	:mpMover(pMover)
	, mShouldFlee(shouldFlee)
	, mpTarget(pTarget)
	, mTargetRadius(targetRadius)
{
	mApplyDirectly = true;
}

Steering* A2SeekOrFlee::getSteering()
{
	// overright the target radius here for the sake of this assignment
	mTargetRadius = mpMover->getTargetRadius();

	if (mIsFleeing || getDistance() < mTargetRadius)
	{
		// flee
		if (mShouldFlee)
		{
			std::cout << "flee" << std::endl;
			mLinear = mpMover->getPosition() - mpTarget->getPosition();
		}
		else
		{
			std::cout << "seek" << std::endl;
			mLinear = mpTarget->getPosition() - mpMover->getPosition();
		}

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mIsFleeing = true;

		mpMover->setNewOrientation();
		mAngular = mpMover->getOrientation();
	}

	return this;
}

float A2SeekOrFlee::getDistance()
{
	//std::cout << sqrt(pow(mpMover->getPosition().getX() - mpTarget->getPosition().getX(), 2.0f) + pow(mpMover->getPosition().getY() - mpTarget->getPosition().getY(), 2.0f)) << std::endl;
	return sqrt(pow(mpMover->getPosition().getX() - mpTarget->getPosition().getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - mpTarget->getPosition().getY(), 2.0f));
}