#ifndef A3BLEND_H
#define A3BLEND_H

#include "Steering.h"

class A3Cohesion;
class A3GroupAllignment;
class A3Separation;
class A3VelocityMatch;
class A2Wander;
class A3AvoidWalls;

class KinematicUnit;

class A3Blend : public Steering
{
public:
	A3Blend(KinematicUnit* pMover);
	~A3Blend();

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;

	A3Cohesion* mpCohesion;
	A3GroupAllignment* mpGroupAllignment;
	A3Separation* mpSeparation;
	A3VelocityMatch* mpVelocityMatch;
	A2Wander* mpWander;
	A3AvoidWalls* mpAvoidWalls;
	
};

#endif