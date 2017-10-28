#ifndef A3SEPARATION_H
#define A3SEPARATION_H

#include "Steering.h"

class KinematicUnit;

const float DECAY_COEF_SEP = 0.1f;

class A3Separation : public Steering
{
public:
	A3Separation(KinematicUnit* pMover);
	~A3Separation() {};

	virtual Steering* getSteering();

	float getDistance(KinematicUnit* target);
	float getDistance(Vector2D target);

private:
	KinematicUnit* mpMover;
	Vector2D mAveragePosition;
};

#endif