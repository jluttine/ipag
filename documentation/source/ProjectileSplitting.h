
#ifndef _PROJECTILESPLITTABLE_H_
#define _PROJECTILESPLITTABLE_H_

#include "Projectile.h"
#include "Angle.h"

/**
 * Author: Jaakko Luttinen
 * ProjectileSplitting is a class for projectiles that split into multiple
 * shots. Splitting angle and time may be set as parameters.
 */
class ProjectileSplitting  :  public virtual Projectile
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
	 */
	ProjectileSplitting( const string &name, const string &description,
	                     int price, int spriteIndex, int soundIndex,
	                     BodyExplosion::EType explosionIndex, float radius,
	                     float mass, float damage, float damageRadius,
	                     Projectile &splittingProjectile, int splitCount,
	                     float splitAngle, int timeToSplit,
	                     float splittingVelocity );

	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileSplitting( const ProjectileSplitting &copy );

	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const
		{ return new ProjectileSplitting( *this ); };

	/**
	 * Forms a string to describe the damage of the projectile.
	 * @param text String to store the damage description.
	 */
	virtual void getDamageText( std::string &text ) const;

	/**
	 * Simulates the timestep for the capsule.
	 * @param timestep The step length in ms.
	 * @param capsule  The capsule, that is the projectile in the world.
	 */
	virtual void step( int timestep, BodyProjectile &capsel );

private:

	/**
	 * Projectile template to use to create the splitting projectiles.
	 */
	Projectile &splittingProjectile;
	
	/**
	 * Number of splitting projectiles.
	 */
	int splitCount;
	
	/**
	 * Velocity boost for splitting projectiles.
	 */
	float splittingVelocity;

	/**
	 * Index of the parameter that tells the splitting time.
	 */
	int indexSplittingTime;
	
	/**
	 * Index of the parameter that tells the splitting angle.
	 */
	int indexSplittingAngle;
	
};

#endif //_PROJECTILESPLITTABLE_H_
