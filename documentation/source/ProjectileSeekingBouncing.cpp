
#include "ProjectileSeekingBouncing.h"

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
 * @param damage         Maximum damage of the projectile-
 * @param damageRadius   Radius of the damage.
 * @param timeToTarget   Time to activate.
 * @param bounceCount    Number of bounces to take before destruction.
 * @param elasticity     Elasticity of bounces.
 */
ProjectileSeekingBouncing
	::ProjectileSeekingBouncing( const string &name,
	                             const string &description, int price,
	                             int spriteIndex, int soundIndex,
	                             BodyExplosion::EType explosionIndex,
	                             float radius, float mass, float damage,
	                             float damageRadius, int timeToTarget,
	                             float acceleration, int bounceCount,
	                             float elasticity )
	: Projectile( name, description, price, spriteIndex, soundIndex,
	              explosionIndex, radius, mass, damage, damageRadius ),
	  ProjectileSeeking( name, description, price, spriteIndex, soundIndex,
	                     explosionIndex, radius, mass, damage, damageRadius,
	                     timeToTarget, acceleration ),
	  ProjectileBouncing( name, description, price, spriteIndex, soundIndex,
	                      explosionIndex, radius, mass, damage, damageRadius,
	                      bounceCount, elasticity )
{
	
	
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileSeekingBouncing
	::ProjectileSeekingBouncing( const ProjectileSeekingBouncing &copy )
	: Projectile( copy ),
	  ProjectileSeeking( copy ),
	  ProjectileBouncing( copy )
{
	
	
}
	
/**
 * Forms a string to describe the damage of the projectile.
 * @param text String to store the damage description.
 */
void ProjectileSeekingBouncing::getDamageText( std::string &text ) const
{
	
	Projectile::getDamageText( text );
	
}
