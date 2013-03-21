
#ifndef _PROJECTILESHOOTINGBOUNCING_H_
#define _PROJECTILESHOOTINGBOUNCING_H_

#include "ProjectileShooting.h"
#include "ProjectileBouncing.h"

/**
 * Author: Jaakko Luttinen
 * ProjectileShootingBouncing is a class for projectiles that have both
 * shooting and bouncing abilities.
 */
class ProjectileShootingBouncing
	:  public ProjectileShooting, public ProjectileBouncing
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
	 * @param bounceCount    Number of jumps to take before destruction.
	 * @param elasticity     Percentage (0-1) of remaining energy.
	 */
	ProjectileShootingBouncing( const string &name, const string &description,
	                            int price, int spriteIndex, int soundIndex,
	                            BodyExplosion::EType explosionIndex,
	                            float radius, float mass, float damage,
	                            float damageRadius,
	                            const Projectile &ammunition, int shotCount,
	                            int shotDelay, float shotVelocity,
	                            int bounceCount, float elasticity );
	                            
	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileShootingBouncing( const ProjectileShootingBouncing& copy );
	
	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const
		{ return new ProjectileShootingBouncing( *this ); };

	/**
	 * Forms a string to describe the damage of the projectile.
	 * @param text String to store the damage description.
	 */
	virtual void getDamageText( std::string &text ) const;

private:
	
};

#endif //_PROJECTILESHOOTINGBOUNCING_H_
