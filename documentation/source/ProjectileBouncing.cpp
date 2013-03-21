
#include <iostream>
#include "ProjectileBouncing.h"

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
 * @param bounceCount    Number of jumps to take before destruction.
 * @param elasticity     Percentage (0-1) of remaining energy.
 */
ProjectileBouncing::ProjectileBouncing( const string &name,
                                        const string &description,
                                        int price, int spriteIndex,
                                        int soundIndex,
                                        BodyExplosion::EType explosionIndex,
                                        float radius,
                                        float mass, float damage,
                                        float damageRadius, int bounceCount,
                                        float elasticity )
	: Projectile( name, description, price, spriteIndex, soundIndex,
	              explosionIndex, radius, mass, damage, damageRadius )
{

	this->bouncesDone = 0;	
	this->indexBounceCount =
		this->parameters.addParameter( ParameterList::NUMBER, "Bounces", 0, 1,
		                               ProjectileBouncing::maximumBounces + 1,
		                               false );
	this->indexElasticity =
		this->parameters.addParameter( ParameterList::NUMBER, "Elasticity", 30,
		                               5, 15, false );
	
	this->parameters.setParameterValue( this->indexBounceCount, bounceCount );
	this->parameters.setParameterValue( this->indexElasticity,
	                                    ( int )( elasticity * 100 ) );
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileBouncing::ProjectileBouncing( const ProjectileBouncing &copy )
	: Projectile( copy )
{
	
	this->bouncesDone = 0;	
	this->indexBounceCount = copy.indexBounceCount;
	this->indexElasticity = copy.indexElasticity;
	
}

/**
 * Simulates the collision between the capsule and colliding body.
 * That is, if jumps are left it will bounce, otherwise it will destruct.
 * @param capsule       The capsule.
 * @param collidingBody The body to collide with.
 */
void ProjectileBouncing::collide( BodyProjectile &capsule,
                                  Body &collidingBody )
{

	Vector velocityPerpendicularComponent;
	Vector velocity = capsule.getVelocity();
	
	if ( this->bouncesDone
	     < this->parameters.getParameterValue( this->indexBounceCount ) )
	{

		Vector collidingVector(
		 collidingBody.getLocation().getDistanceX(capsule.getLocation().getX()),
		 collidingBody.getLocation().getDistanceY(capsule.getLocation().getY()));
	                        
		velocity.getProjectVector( velocityPerpendicularComponent,
		                           collidingVector );

		//Käännetään kohtisuorakomponentti vastakkaiseksi ottaen kimmoisuus
		//huomioon.
		//Turn the perpendicular component to opposite direction and let
		//the elasticity affect.
		float elasticity =
			sqrt( this->parameters.getParameterValue( this->indexElasticity )
			                                          / 100.0 );
		velocityPerpendicularComponent.scale( -( 1 + elasticity ) );
		velocity += velocityPerpendicularComponent;

		capsule.setVelocity( velocity.getX(), velocity.getY() );

		//Correct location so, that it won't hit the same body immediately
		//again.
		collidingVector.scale( (capsule.getRadius() + collidingBody.getRadius())
		                       / collidingVector.getLength() );
		Coordinates location( collidingBody.getLocation() );
		location.add( collidingVector.getX(), collidingVector.getY() );
		capsule.setLocation( location.getX(), location.getY() );
		
		//Do damages and explode.
		Coordinates collidingLocation( capsule.getLocation() );
		this->getCollidingLocation( collidingLocation, capsule, collidingBody );
		this->doDamages( capsule, collidingLocation );
		this->explode( capsule, collidingLocation );
		
		this->bouncesDone++;
	
	}
	else {
		
		Projectile::collide( capsule, collidingBody );
		
	}
	
}

/**
 * Returns the damage the projectile does to a given distance.
 * @param distance The distance of the damage.
 * @return The damage.
 */
float ProjectileBouncing::getDamage( float distance )
{
	
	float dam = Projectile::getDamage( distance );
	return dam
	       / (this->parameters.getParameterValue(this->indexBounceCount) + 1);
	
}
