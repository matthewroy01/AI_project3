#ifndef A3WANDER_H
#define A3WANDER_H

#include "Steering.h"

class KinematicUnit;

const float ANGLE_CHANGE = 0.5f;

class A3Wander : public Steering
{
public:
	A3Wander(KinematicUnit* pMover);
	~A3Wander() {};

	virtual Steering* getSteering();

	float getDistance(Vector2D target);

private:
	KinematicUnit* mpMover;

	Vector2D randPos;
	int randCount = 0, maxCount = 60;
	float mWanderAngle;
};

#endif