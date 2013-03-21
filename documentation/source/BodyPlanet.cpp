
#include <vector>
#include <math.h>
#include "BodyPlanet.h" 
#include "BodyCannon.h"
#include "Body.h"

#include "images.h"
#include "Graphics.h"

using std::cerr;
using std::endl;

/**
 * Constructs a new planet.
 * @param world           The world which the planet is created into.
 * @param x               X-coordinate in the world.
 * @param y               Y-coordinate in the world.
 * @param size            One of the three sizes.
 * @param type            One of the four types.
 * @param angularVelocity Tells the "End of round" angle rotation.
 */
BodyPlanet::BodyPlanet( World &world, float x, float y, ESize size,
                        EType type, float angularVelocity )
: Body( world, x, y, 0, 0, true, true )
{
	this->image = NULL;
	
	switch (size) {
		case SMALL: 
			this->setRadius(40);
			this->setMass(40);
			
			if (type == MARS)
				this->image = new Sprite(IMAGE_PLANET_01S);
			else if (type == ALIEN)
				this->image = new Sprite(IMAGE_PLANET_02S);
			else if (type == EARTH)
				this->image = new Sprite(IMAGE_PLANET_03S);
			else if (type == ICE)
				this->image = new Sprite(IMAGE_PLANET_04S);
			
			break;
		
		case MEDIUM: 
			this->setRadius(50);
			this->setMass(60);
			
			if (type == MARS)
				this->image = new Sprite(IMAGE_PLANET_01M);
			else if (type == ALIEN)
				this->image = new Sprite(IMAGE_PLANET_02M);
			else if (type == EARTH)
				this->image = new Sprite(IMAGE_PLANET_03M);
			else if (type == ICE)
				this->image = new Sprite(IMAGE_PLANET_04M);

			break;
		
		case LARGE: 
			this->setRadius(60);
			this->setMass(80);
			
			if (type == MARS)
				this->image = new Sprite(IMAGE_PLANET_01L);
			else if (type == ALIEN)
				this->image = new Sprite(IMAGE_PLANET_02L);
			else if (type == EARTH)
				this->image = new Sprite(IMAGE_PLANET_03L);
			else if (type == ICE)
				this->image = new Sprite(IMAGE_PLANET_04L);
			
			break;
	}
	
	this->angle = rand() / RAND_MAX * M_PI * 2;
	this->rotatingAngle = angularVelocity;
}

/**
 * Destructs the planet.
 */
BodyPlanet::~BodyPlanet()
{
	
	this->removeAllCannons();
	
	if (this->image != NULL)
		delete this->image;
	
}

/**
 * Rotates the planet. Also tells the cannons on its surface to update
 * their locations.
 * @param angle The angle to rotate (radian).
 */	
void BodyPlanet::rotate( float angle )
{
	
	unsigned int i;
	
	this->angle += angle;
	
	for ( i = 0; i < this->cannons.size(); i++ )
		this->cannons[i]->updateLocation();
	
	this->image->setAngle(this->angle);
}

/**
 * Raises the flag to show that the planet is destroyed and should be
 * removed from the world. Will also destroy all the cannons on its
 * surface.
 */	
void BodyPlanet::destroy()
{
	
	unsigned int i;
	
	for ( i = 0; i < this->cannons.size(); i++ )
		this->cannons[i]->destroy();
		
	Body::destroy();
	
}

/**
 * Tells whether the planet has the given cannon on its surface.
 * @param cannon A cannon to look for.
 * @return Tells whether the planet has the given cannon on its surface.
 */	
bool BodyPlanet::hasCannon(BodyCannon &cannon) const
{
	
	unsigned int i;
	
	for (i=0; i < this->cannons.size(); i++){
		if (this->cannons[i] == &cannon){
			return true;
		}
	}
	return false;
}

/**
 * Adds the given cannon to planet's surface.
 * @param cannon A cannon to add.
 */
void BodyPlanet::addCannon(BodyCannon &cannon)
{
	
	if (!this->hasCannon(cannon)){
		this->cannons.push_back(&cannon);
	}
}

/**
 * Removes a cannon from planet by index.
 * @param index Index of the cannon to remove.
 */
void BodyPlanet::removeCannon(int index)
{

	if (index < 0 || index >= (int)this->cannons.size()) {
		std::cerr << "BodyPlanet::removeCannon: Invalid index " << index
		          << std::endl;
	}
	else {
		this->cannons.erase(this->cannons.begin() + index);
	}
}	

/**
 * Removes the cannon from planet.
 * @param cannon The cannon to remove.
 */
void BodyPlanet::removeCannon( BodyCannon &cannon)
{
	
	unsigned int i;
	
	for (i=0; i < this->cannons.size(); i++){
		if (this->cannons[i] == &cannon){
			return this->removeCannon(i);
		}
	}
}

/**
 * Removes all cannons from the planet.
 */
void BodyPlanet::removeAllCannons()
{
	
	int i;
	
	for (i = this->cannons.size() - 1; i >= 0; i--){
		this->removeCannon(i);
	}
}

/**
 * Does drawing procedures.
 * @param graphics The graphics object to draw to.
 */
void BodyPlanet::draw(Graphics &graphics)
{
	
	this->image->drawRotated(graphics, this->location);
}
