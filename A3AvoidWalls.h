#ifndef A3AVOIDWALLS_H
#define A3AVOIDWALLS_H

#include "Steering.h"

class KinematicUnit;
class WallUnit;

const float POINT_DIST = 200;
const float DECAY_COEF_AW = 2.0f;
const float ESCAPE_STRENGTH = 150.0f;

class A3AvoidWalls : public Steering
{
public:
	A3AvoidWalls(KinematicUnit* pMover);
	~A3AvoidWalls() {};

	virtual Steering* getSteering();

	Vector2D getRaycast(WallUnit* target);
	float getDistance(Vector2D target);

private:
	KinematicUnit* mpMover;

	Vector2D mPoint;

	bool mPointFound;
};

#endif