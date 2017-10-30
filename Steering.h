#pragma once

/*Steering - implementation of Steering class from "Artificial Intelligence for Games" - Millington and Funge
	Mostly modified by adding the mApplyDirectly bool variable to indicate if this Steering should operate as an override on the Kinematic's velocities
	or if it should be additive with those velocities.  Arrive (amoung others) requires direct application to work where as Seek operates by influencing
	the Kinematic's velocities rather than over-riding them.

	Steering is a base class for the various types of steering behaviors which require their own algorithms.  Those algorithms are encoded in the 
	subclass's getSteering function.

	Dean Lawson
	Champlain College
	2011
*/

#include "Vector2D.h"
#include "Kinematic.h"
#include "Trackable.h"
#include "Game.h"

// wander rotation
const float WAS_MAX_WANDER_ROTATION = 1.0f;

// weights
const float W_WANDER = 0.1;
const float W_SEEKORFLEE = 0.6f;
const float W_AVOID_COLLISION = 0.5f;
const float W_AVOID_WALLS = 2.0f;
//const float W_COHESION = 1.0;
const float W_GROUP_ALLIGNMENT = 0.0f;
//const float W_SEPARATION = 0.3f;
//const float W_VELOCITY_MATCH = 1.5f;

class Steering: public Trackable
{
public:
	//constructors and destructors
	Steering(const Vector2D& theLinear = gZeroVector2D, float theAngular = 0.0f, bool applyDirectly = false) :mLinear(theLinear), mAngular(theAngular){};
	Steering( const Steering& rhs ):mLinear(rhs.mLinear), mAngular(rhs.mAngular), mApplyDirectly(rhs.mApplyDirectly){};
	virtual ~Steering(){};

	//accessors
	const Vector2D& getLinear() const { return mLinear; };
	float getAngular() const { return mAngular; };
	void setLinear( const Vector2D& linear ) { mLinear = linear; };
	void setAngular( float angular ) { mAngular = angular; };
	bool shouldApplyDirectly() const { return mApplyDirectly; };

	virtual Steering* getSteering() { return this; };//overridden by sub-classes

	Steering* operator+=(Steering* add);
	Steering* operator*(float left);

	void changeWeight(int mode, float amount, bool add);

	// some weights are here so they can be changed
	float W_COHESION = 1.0f;
	float W_SEPARATION = 0.3f;
	float W_VELOCITY_MATCH = 1.5f;

protected:
	Vector2D mLinear;//linear velocity
	float mAngular;//angular velocity
	bool mApplyDirectly;
	
};