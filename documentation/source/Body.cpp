
#include <iostream>
#include <stdio.h>
#include "Body.h"
#include "math.h"

/**
 * Constructs a new body.
 * @param world           The world which the body will be put into. Note,
 *                        constructor does NOT add the body into the world
 *                        automatically.
 * @param x               X-coordinate of the body's center in the world.
 * @param y               Y-coordinate of the body's center in the world.
 * @param radius          The radius of the body.
 * @param mass            The mass of the body.
 * @param emitGravitation Tells whether body emits gravitational field.
 * @param collidable      Tells whether body is collidable.
 */
Body::Body( World &world, float x, float y, float radius, float mass,
            bool emitGravitation, bool collidable )
	: world( world ), location( world.getCoordinateSystem(), x, y )
{

	this->radius = radius;
	this->mass = mass;
	this->emitGravitation = emitGravitation;
	this->destroyed = false;
	this->collidable = collidable;
	this->actionFlag = false;
	this->sprite = -1;  //Default, no sprite.

}

/**
 * Destructs the body.
 */
Body::~Body() {

}


/**
 * Tells whether the body and given body collide. Two bodies will collide
 * if all the following circumstances are met:
 * 1) Bodies are in the same world.
 * 2) At least one of the bodies is collidable.
 * 3) None of the bodies is destroyed.
 * 4) The circles of the bodies collide in the world.
 * @param testBody The body to determine the collision with.
 * @return Tells whether the bodies collide.
 */
bool Body::collisionDetection( Body &testBody ) const
{

	if ( &this->world == &testBody.world &&
	     ( this->collidable || testBody.collidable ) &&
	     !this->destroyed && !testBody.destroyed )
	{
		return this->location.getDistance( testBody.location.getX(),
		                                   testBody.location.getY() )
		       <= ( this->radius + testBody.radius );
	}
	else {
		return false;
	}
	
}

/**
 * Tells the gravitational field the body creates in a specific location.
 * @param vector The vector to store the gravitational field.
 * @param x      The x-coordinate of the location.
 * @param y      The y-coordinate of the location.
 */
void Body::getGravitationalField( Vector &vector, float x, float y )
{

	int i, j;
	float distance, dx, dy;
	float field, fx, fy;

	vector.set( 0.0, 0.0 );
	
	if ( this->emitGravitation && this->mass != .0 ) {
	
		//The gravitational field will be calculated from four closest versions.
		for ( i = -1; i <= 1; i += 2 ) {

			for ( j = -1; j <= 1; j+= 2 ) {
			
				dx = this->location.getDistanceX( x, i );
				dy = this->location.getDistanceY( y, j );
				distance = sqrt( dx * dx + dy * dy );
				
				field = -this->world.getGravitationConst() * mass
				        / ( distance * distance );
				fx = field * dx / distance;
				fy = field * dy / distance;
				
				vector.add( fx, fy );
			
			}
		
		}
	
	}
	
}

/**
 * Visualizes the body to the given graphics system.
 * @param graphics The graphics system.
 */
void Body::draw(Graphics &graphics) {

	if ( this->sprite >= 0 )
		graphics.drawAnimated( this->sprite, this->location, this->getPhase() );

}
