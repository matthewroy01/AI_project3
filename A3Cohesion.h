#ifndef A3COHESION_H
#define A3COHESION_H

#include "Steering.h"

class KinematicUnit;

const float DECAY_COEF_COH = 0.1f;

class A3Cohesion : public Steering
{
public:
	A3Cohesion(KinematicUnit* pMover);
	~A3Cohesion() {};

	virtual Steering* getSteering();

	float getDistance(KinematicUnit* target);
	float getDistance(Vector2D target);

private:
	KinematicUnit* mpMover;
	Vector2D mAveragePosition;
};

#endif