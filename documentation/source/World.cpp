
#include <iostream>
#include "World.h"
#include "Body.h"
#include "BodyMovable.h"
#include "BodyPlanet.h"

/**
 * Constructs a new world.
 * @param width  Width of the world.
 * @param height Height of the world.
 * @param sounds Sound engine.
 */
World::World( int width, int height, float gravity, Sounds &sounds )
	: system( width, height ), sounds( sounds )
{

	this->gravity = gravity;

}

/**
 * Destructs the world.
 */
World::~World()
{
	
	this->removeAllBodies();

}

/**
 * Adds the given body into the world. World will free the memory
 * allocation.
 * @param newBody Body to add.
 */
void World::addBody( Body &newBody )
{

	if ( !this->hasBody(newBody) )
		this->bodies.push_back(&newBody);

}

/**
 * Removes the given body from the world.
 * @param body Body to remove.
 */
void World::removeBody( Body &body )
{
	
	for (unsigned int i = 0; i < this->bodies.size(); i++ ) {

		if ( this->bodies[i] == &body )
			return this->removeBody( i );

	}
	
}

/**
 * Removes the body of given index.
 * @param index Index of the body to remove.
 */
void World::removeBody( int index )
{
	
	Body *oldBody;
		
	if ( index < 0 || index >= (int)this->bodies.size() )
		std::cerr << "\nWorld::removeBody: Invalid index " << index;
	else {
		
		oldBody = this->bodies[index];
		this->bodies.erase( this->bodies.begin() + index );
		delete oldBody;
		
	}
	
}

/**
 * Removes all bodies from the world.
 */
void World::removeAllBodies()
{
	
	//Remove bodies in reverse order, so the index won't jump over someone.
	//Also the list doesn't have to do lots of junk.
	for ( int i = (int)this->bodies.size() - 1; i >= 0; i-- )
		this->removeBody( i );
		
}

/**
 * Tells whether the world has the given body.
 * @param body Body to check.
 * @return Whether the world has the given body.
 */
bool World::hasBody( Body &body ) const
{
	
	for ( unsigned int i = 0; i < this->bodies.size(); i++ )
	{
		if ( this->bodies[i] == &body )
			return true;
	}
	
	return false;
	
}

/**
 * Returns the body of given index (or NULL).
 * @param index Index of the body.
 * @return Body of given index.
 */	
Body* World::getBody( int index )
{
	
	if ( index < 0 || index >= (int)this->bodies.size() )
		return NULL;
		
	return this->bodies[index];
	
}

/**
 * Returns the closest planet to the given coordinates.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @return The closest planet.
 */
Body* World::getNearestPlanet( float x, float y )
{
	
	//Put the init value so big that every planet has smaller value.
	float shortestDistance = this->system.getWidth()
	                         + this->system.getHeight();
	float distance;
	BodyPlanet *planet, *closestPlanet = NULL;
	
	//Look for closest planet.
	for ( unsigned int i = 0; i < this->bodies.size(); i++ ) {
		
		planet = dynamic_cast<BodyPlanet*>( this->bodies[i] );
		if ( planet != NULL ) {
			//Calculate distance to planet's surface.
			distance = planet->getLocation().getDistance( x, y )
			           - planet->getRadius();
			if ( distance < shortestDistance ) {
				shortestDistance = distance;
				closestPlanet = planet;				
			}
			
		}
		
	}
	
	return closestPlanet;
	
}

/**
 * Simulates collisions with the given body.
 * @param targetBody Body to check the collisions with.
 */
void World::simulateCollisions( Body &targetBody )
{
	
	for ( unsigned int i = 0; i < this->bodies.size(); i++ ) {
		
		if ( &targetBody != this->bodies[i]
		     && targetBody.collisionDetection( *this->bodies[i] ) )
		{
			
			targetBody.collide( *this->bodies[i] );
			this->bodies[i]->collide( targetBody );
			
		}
		
	}
	
}

/**
 * Lets bodies do their end of round procedures.
 * @param step The relative step length 0-1.
 */	
void World::endOfRound( float step )
{
	
	for ( unsigned int i = 0; i < this->bodies.size(); i++ )
			this->bodies[i]->endOfRound( step );
	
}

/**
 * Plays a sound of given index.
 * @param index Index of the sound.
 */
void World::playSound(int index){

  this->sounds.playSound(index);

}

/**
 * World takes a step of length timestep.
 * @param timestep Length of the simulation step.
 */
void World::step(unsigned int timestep)
{
	
	//First, let every non-destroyed body act.
	for ( unsigned int i = 0; i < this->bodies.size(); i++ ) {
		
		if ( !this->bodies[i]->isDestroyed() )
			this->bodies[i]->step(timestep);
		
	}
		
	//Then remove destroyed bodies.
	for ( int i = this->bodies.size() - 1; i >= 0; i-- ) {
		
		if ( this->bodies[i]->isDestroyed() )
			this->removeBody( i );
			
	}

}

/**	
 * Tells the gravitational field in a given location.
 * @param vector Vector to store the gravitational field.
 * @param x      X coordinate.
 * @param y      Y coordinate.
 */
void World::getGravitationalField( Vector &vector, float x, float y ) const
{
	
	Vector tempGrav;

	vector.set( 0, 0 );
	
	for ( unsigned int i = 0; i < this->bodies.size(); i++ ) {
		
		bodies[i]->getGravitationalField( tempGrav, x, y );
		vector += tempGrav;

	}

}

/**
 * Draws the world into graphics.
 * @param graphics Graphics object to draw the world into.
 */
void World::draw( Graphics &graphics ) const
{
	graphics.drawStarfield();
	
	for ( unsigned int i = 0; i < this->bodies.size(); i++)
		bodies[i]->draw(graphics);
	
}
