#include "A3VelocityMatch.h"

#include "KinematicUnit.h"

A3VelocityMatch::A3VelocityMatch(KinematicUnit* mover)
{
	mpMover = mover;
}

Steering* A3VelocityMatch::getSteering()
{
	return this;
}