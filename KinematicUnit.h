#pragma once

#include "Kinematic.h"
#include "Steering.h"

/*KinematicUnit - a unit that is derived from the Kinematic class.  Adds behaviors and max speeds and a current Steering.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class Sprite;
class GraphicsBuffer;

extern Steering gNullSteering;//global object - can point to it for a "NULL" Steering

//minmimum forward speed a unit has to have inorder to rotate 
//(keeps unit from spinning in place after stopping
const float MIN_VELOCITY_TO_TURN_SQUARED = 1.0f;

class KinematicUnit: public Kinematic
{
public:
	KinematicUnit( Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity, float maxAcceleration, int height, int width);
	~KinematicUnit();

	//getters and setters
	void setTarget( const Vector2D& target ) { mTarget = target; };
	const Vector2D& getPosition() const { return mPosition; };
	float getMaxVelocity() const { return mMaxVelocity; };
	Vector2D getVelocity() const { return mVelocity; };
	float getMaxAcceleration() const { return mMaxAcceleration; };
	void setVelocity( const Vector2D& velocity ){ mVelocity = velocity; };

	virtual void setNewOrientation();//face the direction you are moving

	//draw yourself to the indicated buffer
	void draw( GraphicsBuffer* pBuffer );
	//move according to the current velocities and update velocities based on current Steering
	void update(float time, float vel, float rad, float ang);

	//initiate behaviors
	void seek( const Vector2D& target );
	void arrive( const Vector2D& target );
	void wander();
	void dynamicSeek( KinematicUnit* pTarget );
	void dynamicFlee( KinematicUnit* pTarget );
	void dynamicArrive( KinematicUnit* pTarget );
	void wanderAndSeek( KinematicUnit* pTarget );
	void wanderAndFlee( KinematicUnit* pTarget );
	void flock();

	// for modes (assignment 2)
	int getTargetRadius() { return mTargetRadius; };
	float getAngularVelocity() { return mAngularVelocity; };

	// for collision
	int getHeight() { return mHeight; };
	int getWidth() { return mWidth; };

	float getCohesion() { return mpCurrentSteering->getWCohesion(); }
	float getSeparation() { return mpCurrentSteering->getWSeparation(); }
	float getAllignment() { return mpCurrentSteering->getWVelocityMatch(); }

private:
	Sprite* mpSprite;
	Steering* mpCurrentSteering;
	Vector2D mTarget;//used only for Kinematic seek and arrive
	float mMaxVelocity;
	float mMaxAcceleration;
	int mTargetRadius;
	float mAngularVelocity;

	void setSteering( Steering* pSteering );

	int mHeight, mWidth;
};