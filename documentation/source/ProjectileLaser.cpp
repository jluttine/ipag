
#include "ProjectileLaser.h"

/**
 * Constructs a new projectile.
 * @param name           Name of the projectile.
 * @param description    Description of the projectile.
 * @param price          Price of the projectile.
 * @param spriteIndex    Index of the sprite.
 * @param soundIndex     Index of the firing sound.
 * @param explosionIndex Index of the explosion type.
 * @param radius         Radius of the projectile.
 * @param damage         Maximum damage of the projectile.
 * @param damageRadius   Radius of the damage.
 * @param lightSpeed     The speed that projectile moves.
 */
ProjectileLaser::ProjectileLaser( const string &name,
                                  const string &description, int price,
                                  int spriteIndex, int soundIndex,
                                  BodyExplosion::EType explosionIndex,
                                  float radius, float damage,
                                  float damageRadius, float lightSpeed )
	: Projectile( name, description, price, spriteIndex, soundIndex,
	              explosionIndex, radius, 0, damage, damageRadius )
{

	this->lightSpeed = lightSpeed;
	this->speedCorrected = false;
	
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileLaser::ProjectileLaser( const ProjectileLaser &copy )
	: Projectile( copy )
{
	
	this->lightSpeed = copy.lightSpeed;
	this->speedCorrected = false;

}
	
/**
 * Simulates the timestep for the capsule.
 * @param timestep The step length in ms.
 * @param capsule  The capsule, that is the projectile in the world.
 */
void ProjectileLaser::step( int timestep, BodyProjectile &capsule )
{
	
	if ( !this->speedCorrected ) {
		
		Vector velocity = capsule.getVelocity();
		float length = velocity.getLength();

		if ( length > 0 ) {
			velocity.scale( this->lightSpeed / length );
			capsule.setVelocity( velocity.getX(), velocity.getY() );
		}
	
		this->speedCorrected = true;
		
	}
	
}

