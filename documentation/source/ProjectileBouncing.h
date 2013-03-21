
#ifndef _PROJECTILEBOUNCING_H_
#define _PROJECTILEBOUNCING_H_

#include "Projectile.h"

/**
 * Author: Jaakko Luttinen
 * ProjectileBouncing is a class for projectiles that have bouncing ability.
 * They have a parameter to indicate how many jumps they should do before 
 * destruction. They also have an elasticity of collisions.
 */
class ProjectileBouncing  :  public virtual Projectile
{
	
public:

	/**
	 * Number of maximum bounces the projectile can take. We don't want it to
	 * jump forever (if lifetime isn't concerned).
	 */
	static const int maximumBounces = 10;

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
	 * @param bounceCount    Number of jumps to take before destruction.
	 * @param elasticity     Percentage (0-1) of remaining energy.
	 */
	ProjectileBouncing( const string &name, const string &description,
	                    int price, int spriteIndex, int soundIndex,
	                    BodyExplosion::EType explosionIndex, float radius,
	                    float mass, float damage, float damageRadius,
	                    int bounceCount, float elasticity );

	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileBouncing( const ProjectileBouncing &copy );
	
	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const 
		{ return new ProjectileBouncing( *this ); };

	/**
	 * Simulates the collision between the capsule and colliding body.
	 * That is, if jumps are left it will bounce, otherwise it will destruct.
	 * @param capsule       The capsule.
	 * @param collidingBody The body to collide with.
	 */
	virtual void collide( BodyProjectile &capsel, Body &collidingBody );

protected:

	/**
	 * Returns the damage the projectile does to a given distance.
	 * @param distance The distance of the damage.
	 * @return The damage.
	 */
	virtual float getDamage( float distance );
	
private:

	/**
	 * Number of bounces the projectile has done.
	 */
	int bouncesDone;
	
	/**
	 * Index of the parameter that tells how many bounces the projectile
	 * should do.
	 */
	int indexBounceCount;
	
	/**
	 * Index of the parameter that tells the elasticity of the bounces.
	 */
	int indexElasticity;
	
};

#endif //_PROJECTILEBOUNCING_H_
