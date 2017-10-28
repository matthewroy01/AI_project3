#ifndef A3COHESION_H
#define A3COHESION_H

#include "Steering.h"

class KinematicUnit;

class A3Cohesion : public Steering
{
public:
	A3Cohesion(KinematicUnit* pMover);
	~A3Cohesion() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};

#endif