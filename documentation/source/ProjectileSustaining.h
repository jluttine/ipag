
#ifndef _PROJECTILESUSTAINING_H_
#define _PROJECTILESUSTAINING_H_

#include "Projectile.h"

/**
 * Author: Jaakko Luttinen
 * ProjectileSustaining is a class for projectiles that create the effect
 * of sustained fire. In fact, the actual projectile is kept unmoved with
 * no interaction and it will launch some new projectiles with given
 * intervals and a slight dispersion.
 */
class ProjectileSustaining  :  public Projectile
{

public:
	
	/**
	 * Constructs a new projectile.
	 * @param name            Name of the projectile.
	 * @param description     Description of the projectile.
	 * @param price           Price of the projectile.
	 * @param ammunition      The projectiles to shoot.
	 * @param count           Number of projectiles to shoot.
	 * @param delay           Time delay between two shots.
	 * @param dispersingAngle The angle of dispersion to give some unaccuracy.
	 */
	ProjectileSustaining( const string &name, const string &description,
	                      int price, const Projectile &ammunition, int count,
	                      int delay, float dispersingAngle );
	
	/**
	 * Constructs a projectile with same properties.
	 * @param copy The projectile to use as a copy.
	 */
	ProjectileSustaining( const ProjectileSustaining &copy );
	
	/**
	 * Returns a dynamic copy. Makes it possible to get a copy without knowing
	 * which subclass the object actually represents. Every subclass must
	 * overwrite this function.
	 * @return Dynamic copy of itself.
	 */	
	virtual Projectile* getCopy() const
		{ return new ProjectileSustaining( *this ); };
	
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

	/**
	 * Simulates the collision between the capsule and colliding body.
	 * @param capsule       The capsule.
	 * @param collidingBody The body to collide with.
	 */
	virtual void collide( BodyProjectile &capsel, Body &collidingBody );
	
private:
	
	/**
	 * Number of shots to fire.
	 */
	int shotCount;
	
	/**
	 * Number of shots fired.
	 */
	int shotsFired;
	
	/**
	 * Delay between two shots.
	 */
	int shotDelay;
	
	/**
	 * Time since last shot.
	 */
	int timeElapsed;
	
	/**
	 * Projectile template to use to create the shot projectiles.
	 */
	const Projectile &ammunition;
	
	/**
	 * Velocity for shots.
	 */
	Vector shotVelocity;
	
	/**
	 * Flag to indicate that this projectile has really been shot, it's not
	 * just in a weapon crate or something.
	 */
	bool isShot;
	
	/**
	 * Angle of dispersion to create the effect of slight unaccuracy.
	 */
	float dispersingAngle;
	
};

#endif //_PROJECTILESUSTAINING_H_
