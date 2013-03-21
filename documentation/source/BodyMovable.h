
#ifndef _BODYMOVABLE_H_
#define _BODYMOVABLE_H_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Vector.h"
#include "Body.h"

/**
 * Author: Jaakko Luttinen
 * BodyMovable is class for moving bodies. Body has a velocity and if it has
 * mass it will be affected by gravitational field. Body may also be set to
 * destroy on collision.
 */
class BodyMovable : public Body
{
	
public:

	/**
	 * Constructs a new body.
	 * @param world              The world which the body will be put into.
	 *                           Note, constructor does NOT add the body into
	 *                           the world automatically.
	 * @param x                  X-coordinate of the body's center in the
	 *                           world.
	 * @param y                  Y-coordinate of the body's center in the
	 *                           world.
	 * @param radius             The radius of the body.
	 * @param mass               The mass of the body.
	 * @param emitGravitation    Tells whether body emits gravitational field.
	 * @param collidable         Tells whether body is collidable.
	 * @param destroyOnCollision Tells whether body should destroy on
	 *                           collision.
	 */
	BodyMovable( World &world, float x, float y, float radius, float mass,
	             bool emitGrav, bool collidable, bool destroyOnCollision );

	/**
	 * Sets velocity.
	 * @param x x-component of the velocity.
	 * @param y y-component of the velocity.
	 */
	inline void setVelocity( float x, float y )
		{ this->velocity.set( x, y ); };
	
	/**
	 * Tells the velocity of the body.
	 * @return The velocity of the body.
	 */
	inline const Vector& getVelocity() const  { return this->velocity; };

	/**
	 * Simulates the collision. Either destroys the body or sets the velocity
	 * to zero.
	 * @collidingBody The body to collide with.
	 */
	virtual void collide( Body &collidingBody );

	/**
	 * Returns the direction angle as phase (0-1).
	 * @return The phase is direction of the velocity scaled to 0-1.
	 */
	virtual float getPhase() const;
	
	/**
	 * Moves body by the given timestep. Simulates the collisions.
	 * @param timestep The timestep to simulate in milliseconds.
	 */
	virtual void step( unsigned int timestep );
	
private:

	/**
	 * The velocity of the body.
	 */
	Vector velocity;
	
	/**
	 * Tells whether the body destroys on collision.
	 */
	bool destroyOnCollision;

};

#endif //_PARTICLEMOVABLE_H_
