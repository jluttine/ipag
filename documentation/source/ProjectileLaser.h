
#ifndef _PROJECTILELASER_H_
#define _PROJECTILELASER_H_

#include "Projectile.h"

/**
 * Author: Jaakko Luttinen
 * ProjectileLaser is a class for projectiles that move at a fast constant
 * speed. Gravity does not effect laser shots.
 */
class ProjectileLaser  :  public Projectile
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
	 * @param damage         Maximum damage of the projectile.
	 * @param damageRadius   Radius of the damage.
	 * @param lightSpeed     The speed that projectile moves.
	 */
	ProjectileLaser( const string &name, const string &description, int price,
	                 int spriteIndex, int soundIndex,
	                 BodyExplosion::EType explosionIndex, float radius,
	                 float damage, float damageRadius, float lightSpeed );

	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileLaser( const ProjectileLaser &copy );
	
	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const
		{ return new ProjectileLaser( *this ); };

	/**
	 * Simulates the timestep for the capsule.
	 * @param timestep The step length in ms.
	 * @param capsule  The capsule, that is the projectile in the world.
	 */
	virtual void step( int timestep, BodyProjectile &capsel );

private:

	/**
	 * The constant speed that the projectile moves.
	 */
	float lightSpeed;
	
	/**
	 * Flag to tell whether the speed has already been corrected to light
	 * speed.
	 */
	bool speedCorrected;
	
};

#endif //_PROJECTILELASER_H_
