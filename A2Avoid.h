#ifndef A2AVOID_H
#define A2AVOID_H

#include "Steering.h"

class KinematicUnit;

class A2Avoid : public Steering
{
public:
	A2Avoid(KinematicUnit* pMover);
	~A2Avoid() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;

	float getDistance(KinematicUnit* target);
};

#endif