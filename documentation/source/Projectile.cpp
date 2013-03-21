
#include <iostream>
#include "Projectile.h"
#include "BodyCannon.h"

/**
 * Constructs a new projectile.
 * @param name           Name of the projectile.
 * @param description    Description of the projectile.
 * @param price          Price of the projectile.
 * @param spriteIndex    Index of the sprite.
 * @param soundIndex     Index of the firing sound.
 * @param explosionIndex Index of the explosion type.
 * @param radius         Radius of the projectile.
 * @param mass           Mass of the projectile.
 * @param damage         Maximum damage of the projectile.
 * @param damageRadius   Radius of the damage.
 */
Projectile::Projectile( const string &name, const string &description,
                        int price, int spriteIndex, int soundIndex,
                        BodyExplosion::EType explosionIndex, float radius,
                        float mass, float damage, float damageRadius )
	: Item( name, description, price )
{
	
	this->spriteIndex = spriteIndex;
	this->soundIndex = soundIndex;
	this->explosionIndex = explosionIndex;
	this->radius = radius;
	this->mass = mass;
	this->damage = damage;
	this->damageRadius = damageRadius;
	this->shooter = NULL;
	this->timeLived = 0;
	
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
Projectile::Projectile( const Projectile &copy )
	: Item( copy ), parameters( copy.parameters )
{
	
	this->spriteIndex = copy.spriteIndex;
	this->soundIndex = copy.soundIndex;
	this->explosionIndex = copy.explosionIndex;
	this->radius = copy.radius;
	this->mass = copy.mass;
	this->damage = copy.damage;
	this->damageRadius = copy.damageRadius;
	this->shooter = NULL;
	this->timeLived = 0;
	
}

/**
 * Simulates the collision between the capsule and colliding body.
 * @param capsule       The capsule.
 * @param collidingBody The body to collide with.
 */
void Projectile::collide( BodyProjectile &capsule, Body &collidingBody )
{
	
	Coordinates collidingLocation( capsule.getLocation() );
	this->getCollidingLocation( collidingLocation, capsule, collidingBody );
	
	this->explode( capsule, collidingLocation );
	this->doDamages( capsule, collidingLocation );

	capsule.destroy();

}

/**
 * Simulates the timestep for the capsule.
 * @param timestep The step length in ms.
 * @param capsule  The capsule, that is the projectile in the world.
 */
void Projectile::step( int timestep, BodyProjectile &capsule )
{
	
	this->timeLived += timestep;
	
	if ( this->timeLived >= Projectile::maximumLivingTime )
		capsule.destroy();
	
}


/**
 * Calculates the actual colliding location between capsule and colliding
 * body. The colliding location must be on the surface of colliding body.
 * @param location      The coordinates to store the location.
 * @param capsule       The capsule.
 * @param collidingBody The body to collide with.
 */
void Projectile::getCollidingLocation( Coordinates &location,
                                       const BodyProjectile &capsule,
                                       const Body &collidingBody ) const
{
	
	Vector vectorCenters( collidingBody.getLocation().getDistanceX(
		                      capsule.getLocation().getX() ),
	                      collidingBody.getLocation().getDistanceY(
	                      	capsule.getLocation().getY() ) );
	               
	vectorCenters.scale( collidingBody.getRadius()
	                     / vectorCenters.getLength() );
	
	collidingBody.getLocation().getRelativeCoordinates( location,
	                                                    vectorCenters.getX(),
	                                                    vectorCenters.getY());
	
}

/**
 * Forms a string to describe the damage of the projectile.
 * @param text String to store the damage description.
 */
void Projectile::getDamageText( std::string &text ) const
{
	
	char buffer[80];
	sprintf( buffer, "%d", ( int )this->damage );
	text = buffer;
	
}

/**
 * Creates an explosion.
 * @param capsule           The capsule.
 * @param collidingLocation The coordinates of the explosion.
 * @param velocity          Velocity of the explosion, if wanted.
 */
void Projectile::explode( const BodyProjectile &capsule,
                          const Coordinates &collidingLocation,
                          const Vector *velocity )
{
	
	//Create an explosion and put it into the world.
	BodyExplosion *explosionBody = new BodyExplosion(capsule.getWorld(),
	                                                 collidingLocation.getX(),
	                                                 collidingLocation.getY(),
	                                                 this->explosionIndex);
	                                                  
	explosionBody->setActionFlag( capsule.getActionFlag() );
	capsule.getWorld().addBody( *explosionBody );
	if ( velocity ) {
		explosionBody->setVelocity( velocity->getX(), velocity->getY() );
	}
	
}

/**
 * Does the damages. Damage is linear inside the damage radius.
 * @param capsule           The capsule.
 * @param collidingLocation The coordinates of the collision.
 */
void Projectile::doDamages( const BodyProjectile &capsule,
                            const Coordinates &collidingLocation )
{
	
	Body *body;
	BodyCannon *cannon;
	float damage;
	int i;
	
	for ( i = 0; ( body = capsule.getWorld().getBody( i ) ) != NULL; i++ ) {

		cannon = dynamic_cast<BodyCannon*>(body);
		if ( cannon ) {

			damage =
				this->getDamage( cannon->getLocation().getDistance(
					collidingLocation.getX(),
					collidingLocation.getY() ) );
					
			if ( damage )
				cannon->getOwner().doDamage( this->shooter, damage );
			
		}
			
	}
	
}

/**
 * Returns the damage the projectile does to a given distance.
 * @param distance The distance of the damage.
 * @return The damage.
 */
float Projectile::getDamage( float distance )
{
	
	if ( distance >= this->damageRadius )
		return .0;
		
	if ( distance < .0 )
		distance = .0;
		
	return this->damage - this->damage / this->damageRadius * distance;
	
}
