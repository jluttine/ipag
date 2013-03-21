
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

class Projectile;

#include "Player.h"
#include "Item.h"
#include "ParameterList.h"
#include "BodyExplosion.h"
#include "BodyProjectile.h"

using std::string;

/**
 * Author: Jaakko Luttinen
 * Projectile is a class for functionality and properties of a projectile.
 * It has a getCopy -fuction to make it easy to use with subclasses.
 * BodyProjectile is the "capsule" for projectile. This way the projectile
 * may be in the world and interact with other bodies.
 */
class Projectile  :  public Item
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
	 */
	Projectile( const string &name, const string &description, int price,
	            int spriteIndex, int soundIndex,
	            BodyExplosion::EType explosionIndex, float radius, float mass,
	            float damage, float damageRadius );
	
	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	Projectile( const Projectile &copy );

	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const  { return new Projectile( *this ); };
	
	/**
	 * Returns the radius.
	 * @return Radius.
	 */
	inline float getRadius() const  { return this->radius; };
	
	/**
	 * Returns the mass.
	 * @return Mass.
	 */
	inline float getMass() const  { return this->mass; };
	
	/**
	 * Returns the index of the sprite.
	 * @return Index of the sprite.
	 */
	inline int getSprite() const  { return this->spriteIndex; };
	
	/**
	 * Returns the index of the firing sound.
	 * @return Index of the firing sound.
	 */
	inline int getSound() const { return this->soundIndex; };
	
	/**
	 * Sets the shooter of the projectile.
	 * @param shooter The player who has shot the projectile.
	 */
	inline void setShooter( Player *shooter )  { this->shooter = shooter; };
	
	/**
	 * Tells the shooter.
	 * @return The player who shot the projectile.
	 */
	inline Player* getShooter()  { return this->shooter; };

	/**
	 * Simulates the timestep for the capsule.
	 * @param timestep The step length in ms.
	 * @param capsule  The capsule, that is the projectile in the world.
	 */
	virtual void step( int timestep, BodyProjectile &capsule );
	
	/**
	 * Simulates the collision between the capsule and colliding body.
	 * @param capsule       The capsule.
	 * @param collidingBody The body to collide with.
	 */
	virtual void collide( BodyProjectile &capsule, Body &collidingBody );
	
	/**
	 * Forms a string to describe the damage of the projectile.
	 * @param text String to store the damage description.
	 */
	virtual void getDamageText( std::string &text ) const;
	
	/**
	 * Returns the parameter list of the projectile.
	 * @return Parameter list.
	 */
	inline const ParameterList& getParameterList() const
		{ return this->parameters; };
	
	/**
	 * Sets the parameter value using the given parameter list.
	 * @param parameters Parameter list having the desired values.
	 */
	inline void setParameters( const ParameterList &parameters )
		{ this->parameters.setParameters( parameters ); };

protected:

	/**
	 * Maximum lifetime of a projectile (ms).
	 */
	static const int maximumLivingTime = 30000;
	
	/**
	 * Creates an explosion.
	 * @param capsule           The capsule.
	 * @param collidingLocation The coordinates of the explosion.
	 * @param velocity          Velocity of the explosion, if wanted.
	 */
	virtual void explode( const BodyProjectile &capsule,
	                      const Coordinates &collidingLocation,
	                      const Vector *velocity = NULL );
	
	/**
	 * Does the damages. Damage is linear inside the damage radius.
	 * @param capsule           The capsule.
	 * @param collidingLocation The coordinates of the collision.
	 */
	virtual void doDamages( const BodyProjectile &capsule,
	                        const Coordinates &collidingLocation );
	
	/**
	 * Returns the damage the projectile does to a given distance.
	 * @param distance The distance of the damage.
	 * @return The damage.
	 */
	virtual float getDamage( float distance );
	
	/**
	 * Calculates the actual colliding location between capsule and colliding
	 * body. The colliding location must be on the surface of colliding body.
	 * @param location      The coordinates to store the location.
	 * @param capsule       The capsule.
	 * @param collidingBody The body to collide with.
	 */
	void getCollidingLocation( Coordinates &location,
	                           const BodyProjectile &capsule,
	                           const Body &collidingBody ) const;

	/**
	 * Parameters of the projectile.
	 */
	ParameterList parameters;

	/**
	 * Time the projectile has lived.
	 */
	int timeLived;
	
	/**
	 * Maximum damage of the projectile.
	 */
	float damage;

private:

	/**
	 * Index of the sprite.
	 */
	int spriteIndex;
	
	/**
	 * Index of the firing sound.
	 */
	int soundIndex;
	
	/**
	 * Index of the explosion.
	 */
	BodyExplosion::EType explosionIndex;

	/**
	 * Radius of the projectile.
	 */
	float radius;
	
	/**
	 * Mass of the projectile.
	 */
	float mass;
	
	/**
	 * Radius of the damage. Damage is linear inside the radius.
	 */
	float damageRadius;
	
	/**
	 * The player who shot the projectile. Does NOT free the memory
	 * allocation.
	 */
	Player *shooter;

};

#endif //_PROJECTILE_H_
