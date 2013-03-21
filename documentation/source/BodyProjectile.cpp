
#include "BodyProjectile.h"
#include "images.h"

/**
 * Constructs a new projectile in the world.
 * @param world The world for the projectile.
 * @param x     X-coordinate.
 * @param y     Y-coordinate.
 * @param shot  The actual shot.
 */
BodyProjectile::BodyProjectile( World &world, float x, float y,
                                Projectile &shot )
	: BodyMovable( world, x, y, shot.getRadius(), shot.getMass(), false,
	               false, false )
{
	
	this->shot = &shot;
	
	if ( this->shot->getSprite() >= 0 )
		this->image = new Sprite( this->shot->getSprite() );
	else
		this->image = NULL;
	
}

/**
 * Destructs the projectile.
 */
BodyProjectile::~BodyProjectile()
{
	
	//Projectile clears the memory allocation of the shot "inside".
	delete this->shot;

	if (this->image){
	  delete this->image;
	}
	
}

/**
 * Tells the phase of the projectile. That is the angle of the velocity in
 * scale 0-1.
 * @return The phase (0-1).
 */
float BodyProjectile::getPhase() const
{
	
	return this->getVelocity().getAngle() / ( 2 * M_PI );
	
}

/**
 * Projectile takes a step.
 * @param timestep Length of the step in ms.
 */
void BodyProjectile::step( unsigned int timestep )
{
	
	this->shot->step( timestep, *this );
	
	BodyMovable::step( timestep );
	
}

/**
 * Simulates the collision.
 * @param collidingBody The body to collide with.
 */
void BodyProjectile::collide( Body &collidingBody )
{
	
	this->shot->collide( *this, collidingBody );

}

/**
 * Does drawing.
 * @param graphics The graphics object to draw to.
 */
void BodyProjectile::draw( Graphics &graphics )
{
	
	if ( this->image ) {
		
		this->image->setAngle(this->getVelocity().getAngle());
		this->image->drawRotated(graphics, this->location);
		
	}
	
}
