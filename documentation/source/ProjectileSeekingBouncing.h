
#ifndef _PROJECTILESEEKINGBOUNCING_H_
#define _PROJECTILESEEKINGBOUNCING_H_

#include "ProjectileSeeking.h"
#include "ProjectileBouncing.h"

/**
 * Author: Jaakko Luttinen
 * ProjectileSeekingBouncing is a class for projectiles that have both
 * seeking and bouncing abilities.
 */
class ProjectileSeekingBouncing
	:  public ProjectileSeeking, public ProjectileBouncing
{
	
public:

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
	ProjectileSeekingBouncing( const string &name, const string &description,
	                           int price, int spriteIndex, int soundIndex,
	                           BodyExplosion::EType explosionIndex,
	                           float radius, float mass, float damage,
	                           float damageRadius, int timeToTarget,
	                           float acceleration, int bounceCount,
	                           float elasticity );

	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileSeekingBouncing( const ProjectileSeekingBouncing &copy );
	
	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const
		{ return new ProjectileSeekingBouncing( *this ); };

	/**
	 * Forms a string to describe the damage of the projectile.
	 * @param text String to store the damage description.
	 */
	virtual void getDamageText( std::string &text ) const;

private:
	
};

#endif //_PROJECTILESEEKINGBOUNCING_H_
