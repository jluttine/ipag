
#ifndef _BODYPROJECTILE_H_
#define _BODYPROJECTILE_H_

class BodyProjectile;

#include "BodyMovable.h"
#include "Projectile.h"
#include "Sprite.h"

/**
 * Author: Jaakko Luttinen
 * BodyProjectile is a class for projectiles in the world. Because bodies
 * must always be in some world, but projectiles must exist outside the
 * world too, we have a separate Projectile class. This class is only a
 * "capsule" for the projectile to be in the world. Almost everything is
 * still done in the Projectile class.
 */
class BodyProjectile  :  public BodyMovable
{
	
public:

	/**
	 * Constructs a new projectile in the world.
	 * @param world The world for the projectile.
	 * @param x     X-coordinate.
	 * @param y     Y-coordinate.
	 * @param shot  The actual shot.
	 */
	BodyProjectile( World &world, float x, float y, Projectile &shot );
	
	/**
	 * Destructs the projectile.
	 */
	virtual ~BodyProjectile();

	/**
	 * Tells the phase of the projectile. That is the angle of the velocity in
	 * scale 0-1.
	 * @return The phase (0-1).
	 */
	virtual float getPhase() const;
	
	/**
	 * Projectile takes a step.
	 * @param timestep Length of the step in ms.
	 */
	virtual void step( unsigned int timestep );
	
	/**
	 * Simulates the collision.
	 * @param collidingBody The body to collide with.
	 */
	virtual void collide( Body &collidingBody );

	/**
	 * Does drawing.
	 * @param graphics The graphics object to draw to.
	 */
	virtual void draw( Graphics &graphics );
	
private:

	/**
	 * The actual projectile. Pointer is never NULL and its memory allocation
	 * must be freed.
	 */
	Projectile *shot;
	
	/**
	 * The sprite.
	 */
	Sprite *image;
	
};

#endif //_BODYPROJECTILE_H_
