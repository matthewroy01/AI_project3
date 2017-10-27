#ifndef A2SEEKORFLEE
#define A2SEEKORFLEE

#include "Steering.h"

class KinematicUnit;

class A2SeekOrFlee : public Steering
{
public:
	A2SeekOrFlee(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee, int targetRadius);
	~A2SeekOrFlee() {};

	virtual Steering* getSteering();
	float getDistance();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	bool mShouldFlee;
	int mTargetRadius;

	bool mIsFleeing = false;
};

#endif