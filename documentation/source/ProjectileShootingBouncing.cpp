
#include "ProjectileShootingBouncing.h"

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
 * @param ammunition     Projectile template to shoot.
 * @param shotCount      Maximum ammunition. After all ammunition has been
 *                       fired, projectile will destruct.
 * @param shotDelay      Delay between two shots in ms.
 * @param shotVelocity   Shooting velocity for shots.
 * @param bounceCount    Number of jumps to take before destruction.
 * @param elasticity     Percentage (0-1) of remaining energy.
 */
ProjectileShootingBouncing
	::ProjectileShootingBouncing( const string &name,
	                              const string &description, int price,
	                              int spriteIndex, int soundIndex,
	                              BodyExplosion::EType explosionIndex,
	                              float radius, float mass, float damage,
	                              float damageRadius,
	                              const Projectile &ammunition, int shotCount,
	                              int shotDelay, float shotVelocity,
	                              int bounceCount, float elasticity )
	: Projectile( name, description, price, spriteIndex, soundIndex,
	              explosionIndex, radius, mass, damage, damageRadius ),
	  ProjectileShooting( name, description, price, spriteIndex, soundIndex,
	                      explosionIndex, radius, mass, damage, damageRadius,
	                      ammunition, shotCount, shotDelay, shotVelocity ),
	  ProjectileBouncing( name, description, price, spriteIndex, soundIndex,
	                      explosionIndex, radius, mass, damage, damageRadius,
	                      bounceCount, elasticity )
{
	
	
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileShootingBouncing
	::ProjectileShootingBouncing( const ProjectileShootingBouncing& copy )
	: Projectile( copy ),
	  ProjectileShooting( copy ),
	  ProjectileBouncing( copy )
{
	
	
}

/**
 * Forms a string to describe the damage of the projectile.
 * @param text String to store the damage description.
 */
void ProjectileShootingBouncing::getDamageText( std::string &text ) const
{

	std::string temp;
	Projectile::getDamageText( temp );
	text += temp;
	text += " and ";
	ProjectileShooting::getDamageText( temp );
	text += temp;
	
}
