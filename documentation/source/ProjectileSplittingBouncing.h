
#ifndef _PROJECTILESPLITTINGBOUNCING_H_
#define _PROJECTILESPLITTINGBOUNCING_H_

#include "ProjectileSplitting.h"
#include "ProjectileBouncing.h"

/**
 * Author: Jaakko Luttinen
 * ProjectileSplittingBouncing is a class for projectiles that have both
 * splitting and bouncing abilities.
 */
class ProjectileSplittingBouncing
	:  public ProjectileSplitting, public ProjectileBouncing
{

public:
	
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
	ProjectileSplittingBouncing( const string &name,
	                             const string &description,
	                             int price, int spriteIndex, int soundIndex,
	                             BodyExplosion::EType explosionIndex,
	                             float radius, float mass, float damage,
	                             float damageRadius,
	                             Projectile &splittingProjectile,
	                             int splitCount,
	                             float splitAngle, int timeToSplit,
	                             float splittingVelocity, int bounceCount,
	                             float elasticity );
	                             
	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileSplittingBouncing( const ProjectileSplittingBouncing &copy );

	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const
		{ return new ProjectileSplittingBouncing( *this ); };

	/**
	 * Forms a string to describe the damage of the projectile.
	 * @param text String to store the damage description.
	 */
	virtual void getDamageText( std::string &text ) const;
	
};

#endif //_PROJECTILESPLITTINGBOUNCING_H_
