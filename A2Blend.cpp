#include "A2Blend.h"
#include "A2Wander.h"
#include "A2SeekOrFlee.h"
#include "A2Avoid.h"
#include "A2AvoidWalls.h"
#include "UnitManager.h"
#include "Game.h"

A2Blend::A2Blend(KinematicUnit *pMover, KinematicUnit *pTarget, bool shouldFlee)
	:mpMover(pMover),
	mpTarget(pTarget),
	mShouldFlee(shouldFlee)
{
	mApplyDirectly = true;
}

Steering* A2Blend::getSteering()
{
	A2Wander* tmpWander = new A2Wander(mpMover);
	tmpWander->getSteering();

	A2SeekOrFlee* tmpSeekOrFlee = new A2SeekOrFlee(mpMover, mpTarget, mShouldFlee, 100);
	tmpSeekOrFlee->getSteering();

	A2Avoid* tmpAvoid = new A2Avoid(mpMover);
	tmpAvoid->getSteering();

	A2AvoidWalls* tmpAvoidWalls = new A2AvoidWalls(mpMover);
	tmpAvoidWalls->getSteering();

	setAngular((tmpWander->getAngular() * W_WANDER) +
			   (tmpSeekOrFlee->getAngular() * W_SEEKORFLEE) +
			   (tmpAvoid->getAngular() * W_AVOID_COLLISION) +
			   (tmpAvoidWalls->getAngular() * W_AVOID_WALLS));

	setLinear((tmpWander->getLinear() * W_WANDER) +
			  (tmpSeekOrFlee->getLinear() * W_SEEKORFLEE) +
			  (tmpAvoid->getLinear() * W_AVOID_COLLISION) +
			  (tmpAvoidWalls->getLinear() * W_AVOID_WALLS));

	// prevent lots of memory leaks!
	delete tmpWander;
	delete tmpSeekOrFlee;
	delete tmpAvoid;
	delete tmpAvoidWalls;

	return this;
}