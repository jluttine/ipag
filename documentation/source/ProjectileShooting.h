
#ifndef _PROJECTILESHOOTING_H_
#define _PROJECTILESHOOTING_H_

#include "Projectile.h"

/**
 * Author: Jaakko Luttinen
 * ProjectileShooting is a class for projectiles that are able to shoot
 * while flying. Projectiles to shoot and shooting delay are both
 * selectable. Projectile has limited ammo and it will destruct after all
 * shots are fired.
 */
class ProjectileShooting  :  public virtual Projectile
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
	 * @param ammunition     Projectile template to shoot.
	 * @param shotCount      Maximum ammunition. After all ammunition has been
	 *                       fired, projectile will destruct.
	 * @param shotDelay      Delay between two shots in ms.
	 * @param shotVelocity   Shooting velocity for shots.
	 */
	ProjectileShooting( const string &name, const string &description,
	                    int price, int spriteIndex, int soundIndex,
	                    BodyExplosion::EType explosionIndex, float radius,
	                    float mass, float damage, float damageRadius,
	                    const Projectile &ammunition, int shotCount,
	                    int shotDelay, float shotVelocity );
	                    
	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileShooting( const ProjectileShooting &copy );
	
	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const
		{ return new ProjectileShooting( *this ); };

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
	 * Selects a new target. Target is the closest cannon not owned by the
	 * owner.
	 * @param capsule The capsule.
	 * @return Selected target.
	 */
	const Body* selectTarget( const BodyProjectile &capsule );

	/**
	 * Projectile templates to use as ammunition.
	 */
	const Projectile &ammunition;
	
	/**
	 * Number of fired shots.
	 */
	int shotsFired;
	
	/**
	 * Number of shots. After all shots have been fired, projectile will
	 * destruct.
	 */
	int shotCount;
	 
	/**
	 * Delay between two shots.
	 */
	int shotDelay;
	  
	/**
	 * Time elapsed since last shot.
	 */
	int timeElapsed;
	
	/**
	 * Velocity for fired shots.
	 */
	float shotVelocity;
	
};

#endif //_PROJECTILESHOOTING_H_
