
#include "ProjectileSplittingBouncing.h"

/**
 * Constructs a new projectile.
 * @param name                Name of the projectile.
 * @param description         Description of the projectile.
 * @param price               Price of the projectile.
 * @param spriteIndex         Index of the sprite.
 * @param soundIndex          Index of the firing sound.
 * @param explosionIndex      Index of the explosion type.
 * @param radius              Radius of the projectile.
 * @param mass                Mass of the projectile.
 * @param damage              Maximum damage of the projectile.
 * @param damageRadius        Radius of the damage.
 * @param splittingProjectile Projectile template for splitting
 *                            projectiles.
 * @param splitCount          Number of splitting projectiles.
 * @param splitAngle          Angle of split.
 * @param timeToSplit         Time to split.
 * @param splittingVelocity   Velocity boost for splitting projectiles.
 * @param bounceCount         Number of jumps to take before destruction.
 * @param elasticity          Percentage (0-1) of remaining energy.
 */
ProjectileSplittingBouncing
	::ProjectileSplittingBouncing( const string &name,
	                               const string &description, int price,
	                               int spriteIndex, int soundIndex,
	                               BodyExplosion::EType explosionIndex,
	                               float radius, float mass, float damage,
	                               float damageRadius,
	                               Projectile &splittingProjectile,
	                               int splitCount, float splitAngle,
	                               int timeToSplit, float splittingVelocity,
	                               int bounceCount, float elasticity )
	: Projectile( name, description, price, spriteIndex, soundIndex,
	              explosionIndex, radius, mass, damage, damageRadius ),
	  ProjectileSplitting( name, description, price, spriteIndex, soundIndex,
	                       explosionIndex, radius, mass, damage, damageRadius,
	                       splittingProjectile, splitCount, splitAngle,
	                       timeToSplit, splittingVelocity ),
	  ProjectileBouncing( name, description, price, spriteIndex, soundIndex,
	                      explosionIndex, radius, mass, damage, damageRadius,
	                      bounceCount, elasticity )
{
	
	
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileSplittingBouncing
	::ProjectileSplittingBouncing( const ProjectileSplittingBouncing &copy )
	: Projectile( copy ),
	  ProjectileSplitting( copy ),
	  ProjectileBouncing( copy )
{
	
	
}

/**
 * Forms a string to describe the damage of the projectile.
 * @param text String to store the damage description.
 */
void ProjectileSplittingBouncing::getDamageText( std::string &text ) const
{
	
	ProjectileSplitting::getDamageText( text );
	
}
