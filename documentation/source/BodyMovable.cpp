
//#include <math.h>
#include "BodyMovable.h"

/**
 * Constructs a new body.
 * @param world              The world which the body will be put into.
 *                           Note, constructor does NOT add the body into
 *                           the world automatically.
 * @param x                  X-coordinate of the body's center in the world.
 * @param y                  Y-coordinate of the body's center in the world.
 * @param radius             The radius of the body.
 * @param mass               The mass of the body.
 * @param emitGravitation    Tells whether body emits gravitational field.
 * @param collidable         Tells whether body is collidable.
 * @param destroyOnCollision Tells whether body should destroy on collision.
 */
BodyMovable::BodyMovable( World &world, float x, float y, float radius,
                          float mass, bool emitGrav, bool collidable,
                          bool destroyOnCollision )
	: Body( world, x, y, radius, mass, emitGrav, collidable )
{

	this->destroyOnCollision = destroyOnCollision;
	
	velocity.set( 0, 0 );

}

/**
 * Simulates the collision. Either destroys the body or sets the velocity to
 * zero.
 * @collidingBody The body to collide with.
 */
void BodyMovable::collide( Body &collidingBody )
{

	if ( this->destroyOnCollision )
		this->destroy();
	else
		this->velocity.set( 0, 0 );

}


/**
 * Moves body by the given timestep. Simulates the collisions.
 * @param timestep The timestep to simulate in milliseconds.
 */
void BodyMovable::step( unsigned int timestep )
{

	Vector gravitation;

	this->location.add( this->velocity.getX() * timestep,
	                    this->velocity.getY() * timestep );

	//If body has mass, gravitational field will affect it.	
	if ( this->getMass() ) {
	
		this->world.getGravitationalField( gravitation,
		                                   this->location.getX(),
		                                   this->location.getY() );
		                                   
		gravitation.scale( timestep );
		this->velocity += gravitation;
		
	}
	
	//Because the body has moved, new collisions may have occured.
	this->world.simulateCollisions( *this );
	
}

/**
 * Returns the direction angle as phase (0-1).
 * @return The phase is direction of the velocity scaled to 0-1.
 */
float BodyMovable::getPhase() const
{
	
	return this->velocity.getAngle() / (2*M_PI);
	
}

