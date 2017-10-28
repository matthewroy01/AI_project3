#include "A3Cohesion.h"

#include "KinematicUnit.h"

A3Cohesion::A3Cohesion(KinematicUnit* mover)
{
	mpMover = mover;
}

Steering* A3Cohesion::getSteering()
{


	return this;
}