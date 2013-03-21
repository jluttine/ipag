
#ifndef _PROJECTILESEEKING_H_
#define _PROJECTILESEEKING_H_

#include "Projectile.h"
#include "BodyCannon.h"

/**
 * Author: Jaakko Luttinen
 * Seeking projectile selects a target and tries to steer straight towards
 * the target.
 */
class ProjectileSeeking  :  public virtual Projectile
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
	 * @param damage         Maximum damage of the projectile.
	 * @param damageRadius   Radius of the damage.
	 * @param timeToTarget   Time to activate.
	 * @param acceleration   The acceleration of steering.
	 */
	ProjectileSeeking( const string &name, const string &description,
	                   int price, int spriteIndex, int soundIndex,
	                   BodyExplosion::EType explosionIndex, float radius,
	                   float mass, float damage, float damageRadius,
	                   int timeToTarget, float acceleration );
	                   
	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileSeeking( const ProjectileSeeking &copy );
	
	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const
		{ return new ProjectileSeeking( *this ); };

	/**
	 * Simulates the timestep for the capsule. If the targeting time has
	 * elapsed a target will be selected and the projectile directed
	 * straightly towards it.
	 * @param timestep The step length in ms.
	 * @param capsule  The capsule, that is the projectile in the world.
	 */
	virtual void step( int timestep, BodyProjectile &capsule );

private:

	/**
	 * Selects a new target. Target is the closest not ruined cannon that is
	 * not owned by the shooter.
	 * @param capsule The capsule.
	 */
	void selectTarget( const BodyProjectile &capsule );

	/**
	 * The selected target.
	 */
	const BodyCannon *target;
	
	/**
	 * Index of the parameter that tells the time to start targeting.
	 */
	int indexTargetingTime;

	/**
	 * The acceleration of steering.
	 */	
	float acceleration;
	
};

#endif //_PROJECTILESEEKING_H_
