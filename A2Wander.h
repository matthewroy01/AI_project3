#ifndef A2WANDER_H
#define A2WANDER_H


#include "Steering.h"

class KinematicUnit;

class A2Wander : public Steering
{
	public:
		A2Wander(KinematicUnit* pMover);
		~A2Wander() {};

		virtual Steering* getSteering();

	private:
		KinematicUnit* mpMover;
};

#endif