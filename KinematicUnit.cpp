#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Steering.h"
#include "KinematicSeekSteering.h"
#include "KinematicArriveSteering.h"
#include "KinematicWanderSteering.h"
#include "DynamicSeekSteering.h"
#include "DynamicArriveSteering.h"
#include "A2Blend.h"
#include "A2Wander.h"
#include "A2SeekOrFlee.h"
#include "A3Blend.h"
#include "UnitManager.h"

using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration, int height, int width)
:Kinematic( position, orientation, velocity, rotationVel)
,mpSprite(pSprite)
,mpCurrentSteering(NULL)
,mMaxVelocity(maxVelocity)
,mMaxAcceleration(maxAcceleration)
,mHeight(height)
,mWidth(width)
{
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw(*pBuffer, mPosition.getX(), mPosition.getY(), 3.1415f/2 + getOrientationFromVelocity(mOrientation, mVelocity) /*mOrientation*/);
}

void KinematicUnit::update(float time, float vel, float rad, float ang)
{
	// set values according to mode
	mMaxVelocity = vel;
	mTargetRadius = rad;
	mAngularVelocity = ang;

	Steering* steering;
	if( mpCurrentSteering != NULL )
	{
		steering = mpCurrentSteering->getSteering();
	}
	else
	{
		steering = &gNullSteering;
	}

	if( steering->shouldApplyDirectly() )
	{
		//not stopped
		if( getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED )
		{
			setVelocity( steering->getLinear() );
			setOrientation( steering->getAngular() );
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity( 0.0f );
		steering->setAngular( 0.0f );
	}

	//move the unit using current velocities
	Kinematic::update( time );
	//calculate new velocities
	calcNewVelocities( *steering, time, mMaxVelocity, 25.0f );
	//move to oposite side of screen if we are off
	GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	//setNewOrientation();
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{ 
	mOrientation = getOrientationFromVelocity( mOrientation, mVelocity ); 
}

void KinematicUnit::seek(const Vector2D &target)
{
	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering( this, target );
	setSteering( pSeekSteering );
}

void KinematicUnit::arrive(const Vector2D &target)
{
	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering( this, target );
	setSteering( pArriveSteering );
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering( this, gpGame->getUnitManager()->GetUnit(0), true, 100);
	setSteering( pWanderSteering );
}

void KinematicUnit::dynamicSeek( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering(this, gpGame->getUnitManager()->GetUnit(0));
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicFlee( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, gpGame->getUnitManager()->GetUnit(0), true );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicArrive( KinematicUnit* pTarget )
{
	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering( this, gpGame->getUnitManager()->GetUnit(0));
	setSteering( pDynamicArriveSteering );
}

void KinematicUnit::wanderAndSeek(KinematicUnit* pTarget)
{
	A2Blend* pA2Blend = new A2Blend(this, pTarget, false);
	setSteering(pA2Blend);
}

void KinematicUnit::wanderAndFlee (KinematicUnit* pTarget)
{
	A2Blend* pA2Blend = new A2Blend(this, pTarget, true);
	setSteering(pA2Blend);
}

void KinematicUnit::flock()
{
	A3Blend* pA3Blend = new A3Blend(this);
	setSteering(pA3Blend);
}

void KinematicUnit::changeCohesion(bool add)
{
	mpCurrentSteering->changeWeight(0, 0.1f, add);
}

void KinematicUnit::changeSeparation(bool add)
{
	mpCurrentSteering->changeWeight(1, 0.1f, add);
}

void KinematicUnit::changeAllignment(bool add)
{
	mpCurrentSteering->changeWeight(2, 0.1f, add);
}