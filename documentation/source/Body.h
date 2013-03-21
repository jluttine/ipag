
#ifndef _BODY_H_
#define _BODY_H_

class Body;

#include "Coordinates.h"
#include "World.h"
#include "Graphics.h"

/**
 * Author: Jaakko Luttinen
 * Body is a class for all the bodies in the world. All bodies are
 * considered as circle shaped. Bodies can have mass and they can emit
 * gravitational field. Body is always in some world and it cannot be
 * changed. World will clean the memory allocation of the body. Body has a
 * visualization.
 */
class Body
{

public:

	/**
	 * Constructs a new body.
	 * @param world           The world which the body will be put into. Note,
	 *                        constructor does NOT add the body into the world
	 *                        automatically.
	 * @param x               X-coordinate of the body's center in the world.
	 * @param y               Y-coordinate of the body's center in the world.
	 * @param radius          The radius of the body.
	 * @param mass            The mass of the body.
	 * @param emitGravitation Tells whether body emits gravitational field.
	 * @param collidable      Tells whether body is collidable.
	 */
	Body( World &world, float x, float y, float radius, float mass,
	      bool emitGravitation, bool collidable );
	
	/**
	 * Destructs the body.
	 */
	virtual ~Body();
	
	/**
	 * Body cannot remove itself from the world, so it must raise a flag which
	 * will be read by the world. World then removes the body and frees body's
	 * memory allocation.
	 */
	inline virtual void destroy()  { this->destroyed = true; };

	/**
	 * Tells whether the body is destroyed and should be removed from the
	 * world.
	 * @return Tells whether the body is destroyed.
	 */	
	inline bool isDestroyed() const  { return this->destroyed; };

	/**
	 * Game engine may use action flag to determine whether the body is an
	 * action body and should be waited to finish its action. After all action
	 * bodies are destroyed the game itself will continue.
	 * @param action Tells whether the body is an action body.
	 */
	inline void setActionFlag( bool action )  { this->actionFlag = action; };
	
	/**
	 * Tells whether the body has action flag set.
	 * @return Tells whether body has action flag set.
	 */
	inline bool getActionFlag() const  { return this->actionFlag; };

	/**
	 * Two bodies may collide only if the other or both bodies are collidable.
	 * No collision will occur if both are non-collidable.
	 * @param collidable Tells whether the body is collidable.
	 */
	inline void setCollidable( bool collidable )
		{ this->collidable = collidable; };
	
	/**
	 * Tells whether the body is collidable.
	 * @return Tells whether the body is collidable.
	 */
	inline bool isCollidable() const  { return this->collidable; };
	
	/**
	 * Sets the radius of the body.
	 * @param radius The radius of the body.
	 */
	inline void setRadius( float radius )  { this->radius = radius; };
	
	/**
	 * Tells the radius of the body.
	 * @return The radius of the body.
	 */
	inline float getRadius() const  { return this->radius; };
	
	/**
	 * Sets the mass of the body. If mass is zero, no gravitational field will
	 * affect the body.
	 * @param mass The mass of the body.
	 */
	inline void setMass( float mass )  { this->mass = mass; };
	
	/**
	 * Tells the mass of the body.
	 * @return The mass of the body.
	 */
	inline float getMass() const  { return this->mass; };

	/**
	 * Tells whether the body emits gravitational field.
	 * @return Tells whether the body emits gravitational field.
	 */
	inline bool emitsGravitation() { return this->emitGravitation; };

	/**
	 * Tells the phase of the body (0-1). What the phase exactly tells, is
	 * undefined and may be used differently by subclasses. Phase will be used
	 * in drawing the sprite.
	 * @return The phase of the body (0-1).
	 */
	virtual inline float getPhase() const  { return .0; };

	/**
	 * Tells the world which the body is in.
	 * @return Tells the world which the body is in.
	 */
	inline World& getWorld() const  { return this->world; };

	/**
	 * Sets the location of the body.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 */	
	inline void setLocation( float x, float y )
		{ this->location.set( x, y ); };
	
	/**
	 * Tells the location of the body.
	 * @return Location of the body.
	 */
	inline const Coordinates& getLocation() const  { return this->location; };
	
	/**
	 * Tells whether the body and given body collide. Two bodies will collide
	 * if all the following circumstances are met:
	 * 1) Bodies are in the same world.
	 * 2) At least one of the bodies is collidable.
	 * 3) None of the bodies is destroyed.
	 * 4) The circles of the bodies collide in the world.
	 * @param testBody The body to determine the collision with.
	 * @return Tells whether the bodies collide.
	 */
	bool collisionDetection( Body &testBody ) const;

	/**
	 * When two bodies collide (determined by collisionDetection function)
	 * their collide functions are called to simulate the collision.
	 * @param collidingBody The other body in collision.
	 */
	virtual void collide( Body &collidingBody )  { };
	
	/**
	 * Tells the gravitational field the body creates in a specific location.
	 * @param vector The vector to store the gravitational field.
	 * @param x      The x-coordinate of the location.
	 * @param y      The y-coordinate of the location.
	 */
	void getGravitationalField( Vector &vector, float x, float y );
	
	/**
	 * This function will be called with short delays to simulate the body in
	 * the world.
	 * @param timestep Delay since last call in milliseconds.
	 */
	virtual void step( unsigned int timestep )  {   };
	
	/**
	 * This function will be called after a round in game. Body may do its
	 * procedures.
	 * @param step The step length (0-1). This function may called many times
	 *             to make simulation fluent. For example, four calls with
	 *             parameters 0.2, 0.2, 0.3 and 0.3 will make a whole 1.0 end
	 *             of round.
	 */
	virtual void endOfRound( float step )  { };
	
	/**
	 * Visualizes the body to the given graphics system.
	 * @param graphics The graphics system.
	 */
	virtual void draw( Graphics &graphics );

protected:

	/**
	 * The index of the sprite.
	 */
	int sprite;

	/**
	 * The world which the body is in.
	 */
	World &world;
	
	/**
	 * The location of the body.
	 */
	Coordinates location;

private:

	/**
	 * The mass of the body.
	 */
	float mass;
	
	/**
	 * The radius of the body.
	 */
	float radius;

	/**
	 * As long as at least one action body is in the world, action phase
	 * continues.
	 */
	bool actionFlag;
	
	/**
	 * Tells whether body emits gravtitational field.
	 */
	bool emitGravitation;
	
	/**
	 * Tells whether body is collidable. Two bodies may collide if the other
	 * or both bodies are collidable.
	 */
	bool collidable;
	
	/**
	 * Tells whether body is destroyed and should be removed from the world.
	 */
	bool destroyed;

};

#endif //_BODY_H_
