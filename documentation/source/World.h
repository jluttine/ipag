#ifndef _WORLD_H_
#define _WORLD_H_

class World;

#include <vector>
#include "Graphics.h"
#include "CoordinateSystem.h"
#include "Vector.h"
#include "Body.h"
#include "Sounds.h"
#include "soundList.h"
//#include "BodyPlanet.h"

using std::vector;

/**
 * Author: Jaakko Luttinen
 * World has dimensions, gravitation constant and sound engine. In world
 * there may be lots of bodies.
 */

class World
{
	
public:

	/**
	 * Constructs a new world.
	 * @param width  Width of the world.
	 * @param height Height of the world.
	 * @param sounds Sound engine.
	 */
	World(int width, int height, float gravity, Sounds &sounds);
	
	/**
	 * Destructs the world.
	 */
	~World();

	/**
	 * Returns the coordinate system of the world.
	 * @return Coordinate system of the world.
	 */
	inline const CoordinateSystem& getCoordinateSystem() const 
		{ return this->system; };

	/**	
	 * Tells the gravitational field in a given location.
	 * @param vector Vector to store the gravitational field.
	 * @param x      X coordinate.
	 * @param y      Y coordinate.
	 */
	void getGravitationalField( Vector &vector, float x, float y ) const;
	
	/**
	 * Returns the gravitation constant.
	 * @return Gravitation constant.
	 */
	inline float getGravitationConst() const { return this->gravity; };

	/**
	 * Adds the given body into the world. World will free the memory
	 * allocation.
	 * @param newBody Body to add.
	 */
	void addBody( Body& newBody );
	
	/**
	 * Removes the given body from the world.
	 * @param body Body to remove.
	 */
	void removeBody( Body &body );
	
	/**
	 * Removes the body of given index.
	 * @param index Index of the body to remove.
	 */
	void removeBody( int index );
	
	/**
	 * Removes all bodies from the world.
	 */
	void removeAllBodies();
	
	/**
	 * Tells whether the world has the given body.
	 * @param body Body to check.
	 * @return Whether the world has the given body.
	 */
	bool hasBody( Body &body ) const;

	/**
	 * Returns the body of given index (or NULL).
	 * @param index Index of the body.
	 * @return Body of given index.
	 */	
	Body* getBody( int index );
	
	/**
	 * Returns the closest planet to the given coordinates.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 * @return The closest planet.
	 */
	Body* getNearestPlanet( float x, float y );
	
	/**
	 * Simulates collisions with the given body.
	 * @param targetBody Body to check the collisions with.
	 */
	void simulateCollisions( Body &targetBody );

	/**
	 * Lets bodies do their end of round procedures.
	 * @param step The relative step length 0-1.
	 */	
	void endOfRound( float step );
	
	/**
	 * World takes a step of length timestep.
	 * @param timestep Length of the simulation step.
	 */
	void step( unsigned int timestep );
	
	/**
	 * Draws the world into graphics.
	 * @param graphics Graphics object to draw the world into.
	 */
	void draw(Graphics &graphics) const;
	
	/**
	 * Plays a sound of given index.
	 * @param index Index of the sound.
	 */
	void playSound( int index );
	
	/**
	 * Returns the sound engine.
	 * @return The sound engine.
	 */
	Sounds& getSounds()  { return this->sounds; };

private:

	/**
	 * The bodies in the world. Will clean the memories.
	 */
	vector<Body*> bodies;
	
	/**
	 * Coordinate system of the world.
	 */
	CoordinateSystem system;

	/**
	 * Sound engine.
	 */
	Sounds &sounds;
	
	/**
	 * Gravitation constant.
	 */
	float gravity;
	
};

#endif //_WORLD_H_
