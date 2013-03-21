
#include <math.h>
#include <iostream>
#include "BodyCannon.h"
#include "BodyProjectile.h"
#include "BodyDebris.h"
#include "Angle.h"

/**
 * Constructs a new cannon.
 * @param planet The planet which the cannon will be put on.
 * @param angle  The angle on the planet.
 * @param owner  The player to own the cannon. Note, the cannon is not given
 *               to player by this function.
 */
BodyCannon::BodyCannon( BodyPlanet &planet, float angle, Player &owner )
	: Body( planet.getWorld(),
	        getLocationX( planet.getLocation().getX(), planet.getRadius(),
	                      planet.getAngle() + angle ),
	        getLocationY( planet.getLocation().getY(), planet.getRadius(),
	                      planet.getAngle() + angle ),
	        .0, .0, false, true ),
	owner( owner )
{

	this->planet = &planet;
	this->ruined = false;
	this->angleOnPlanet = angle;
	this->aimingAngle = 0;
	this->aimingPower = BodyCannon::minimumPower;
	this->active = false;
	
}

/**
 * Destructs the cannon.
 */
BodyCannon::~BodyCannon()
{
	
	//Remove references to this cannon.
	this->owner.removeCannon();
	this->planet->removeCannon( *this );

}

/**
 * Sets the planet of the cannon. If the planet is not from the same world
 * as the cannon, the request is ignored.
 * @param planet The new planet for cannon.
 */
void BodyCannon::setPlanet( BodyPlanet &planet )
{
	
	if ( &planet.getWorld() == &this->world ) {
		
		this->planet->removeCannon( *this );
		this->planet = &planet;
		this->planet->addCannon( *this );
		this->updateLocation();
		
	}
	
}

/**
 * Sets the angle of the cannon on the planet.
 * @param angle Angle on planet (radius).
 */
void BodyCannon::setAngleOnPlanet( float angle )
{
	
	Angle::fix( angle );
	this->angleOnPlanet = angle;
	this->updateLocation();
	
}

/**
 * Sets aiming angle (0-Pi).
 * @param angle The aiming angle.
 */	
void BodyCannon::setAimingAngle( float angle )
{
	
	this->world.playSound(SOUND_TICK);
	this->aimingAngle = angle;
	fix( this->aimingAngle, M_PI );
	
}

/**
 * Sets aiming power (minimumPower-maximumPower).
 * @param power The aiming power.
 */
void BodyCannon::setAimingPower( float power )
{
	
	if ( power < BodyCannon::minimumPower )
		power = BodyCannon::minimumPower;
	else if ( power > BodyCannon::maximumPower )
		power = BodyCannon::maximumPower;

	this->world.playSound(SOUND_TICK);
	this->aimingPower = power;
	
}

/**
 * Shoots the given shot with the angle and power that has been set. The
 * memory allocation of the bullet will be freed by BodyProjectile.
 * @param bullet The projectile to shoot.
 */
void BodyCannon::shoot( Projectile &bullet )
{
	
	const Coordinates &location = this->planet->getLocation();
	float radius = bullet.getRadius() + this->planet->getRadius();
	float angle = this->angleOnPlanet + this->planet->getAngle();
	
	//Make the shooting sound.
	this->world.playSound( bullet.getSound() );
	
	//Create the shot.
	BodyProjectile *shot =
		new BodyProjectile( this->world,
	                      BodyCannon::getLocationX( location.getX(), radius,
	                                                angle ),
	                      BodyCannon::getLocationY( location.getY(), radius,
	                                                angle ),
	                      bullet );

	//Set the velocity of the shot.
	angle += this->aimingAngle - M_PI / 2;
	shot->setVelocity( cos( angle ) * this->aimingPower,
	                   sin( angle ) * this->aimingPower );
	
	//Add action body into world.
	shot->setActionFlag( true );
	this->world.addBody( *shot );
	
}

/**
 * Updates the location of the cannon using the location of the planet and
 * cannon's angle on the planet.
 */
void BodyCannon::updateLocation()
{

	if ( this->planet->isDestroyed() ) {
		
		this->destroy();
		
	}
	else {
		
		BodyCannon::calculateLocation( this->location, *this->planet,
		                               this->angleOnPlanet );
	
	}
	
}

/**
 * Ruins the cannon.
 */
void BodyCannon::ruin()
{
	
	if ( this->ruined )
		return;
	
	this->ruined = true;
	
	//Shoot some debris in the air
	const Coordinates &location = this->planet->getLocation();
	float radius = this->planet->getRadius() + 5;
	float baseAngle = this->angleOnPlanet + this->planet->getAngle();
	float angle, power;
	
	for (int i=0; i<20; i++) {
		
		BodyDebris *debris =
			new BodyDebris( this->world,
		                  getLocationX(location.getX(), radius, baseAngle),
		                  getLocationY( location.getY(), radius, baseAngle),
		                  .5); 			
		                                     
		angle = baseAngle + (float)rand() / RAND_MAX * M_PI - M_PI / 2;
		power = .20 + (float)rand() / RAND_MAX * .20;
		
		debris->setVelocity(cos(angle) * power, sin(angle) * power);
		debris->setActionFlag(true);
		
		this->world.addBody(*debris);
		
	}
	
}

/**
 * Visualizes the cannon to the given graphics system. Also draws energy bar
 * and sight if active.
 * @param graphics The graphics system.
 */
void BodyCannon::draw(Graphics &graphics)
{
	if ( this->ruined )
		graphics.drawRect(location, 7, 7, 64, 64, 64);
	else {
		
		unsigned char r, g, b;
		
		//The cannon itself
		this->owner.getColor( r, g, b );
		graphics.drawRect(location, 7, 7, r, g, b);
		
		//Enegry bar location
		float angle = this->angleOnPlanet + this->planet->getAngle() + M_PI;
		Coordinates energyBar(this->location);
		energyBar.add(cos(angle) * 10, sin(angle) * 10);
		
		//Energy bar color
		int red, green;
		float i = owner.getIntegrity();
		red = (int)(512 - i * 5.12);
		green = (int)(i * 5.12);
		
		red = red > 255 ? 255 : red;  //R max = 255
		red = red < 0 ? 0 : red;      //R min = 0
		green = green > 255 ? 255 : green;  //G max = 255
		green = green < 0 ? 0 : green;      //G min = 0
		
		//Draw energy bar
		graphics.drawRect(energyBar, 4, 4, red, green, 0);
	}
	
	
	if ( this->active ) {
	
		float angle = this->aimingAngle + this->angleOnPlanet
		              + this->planet->getAngle() - M_PI / 2;
		
		Coordinates aim1(this->location);
		Coordinates aim2(this->location);
		aim1.add(cos(angle) * aimingPower * 60, sin(angle) * aimingPower * 60);
		aim2.add(cos(angle) * aimingPower * 120, sin(angle) * aimingPower *120);
		
		graphics.drawSprite(IMAGE_CROSSHAIR, aim1);
		graphics.drawSprite(IMAGE_CROSSHAIR, aim2);
	}
}



/**
 * Returns the x-coordinate of the cannon. x is the x-coordinate of circle's
 * center point. radius is the radius of the circle. angle is the angle of
 * cannon's location. 
 * @param x      X-coordinate of the circle.
 * @param radius Radius of the circle.
 * @param angle  Angle to point on surface.
 */
float BodyCannon::getLocationX( float x, float radius, float angle )
{
	
	return x + cos( angle ) * radius;
	
}

/**
 * Returns the y-coordinate of the cannon. y is the y-coordinate of circle's
 * center point. radius is the radius of the circle. angle is the angle of
 * cannon's location. 
 * @param y      Y-coordinate of the circle.
 * @param radius Radius of the circle.
 * @param angle  Angle to point on surface.
 */
float BodyCannon::getLocationY( float y, float radius, float angle )
{
	
	return y + sin( angle ) * radius;
	
}

/**
 * Fixes the number to 0-max. For example, -2 -> max-2, 2*max+1 -> 1.
 */
void BodyCannon::fix( float &number, float max )
{	

	number = fmod( number, max );	

	if (number < 0 )
		number += max;

}

/**
 * Calculates the coordinates on the surface of a planet. The angle is
 * given.
 * @param location      The coordinates to store the location.
 * @param planet        The planet.
 * @param angleOnPlanet Angle on planet (radius).
 */
void BodyCannon::calculateLocation( Coordinates &location,
                                    const BodyPlanet &planet,
                                    float angleOnPlanet )
{
	
	location = planet.getLocation();
	float angle = angleOnPlanet + planet.getAngle();
		
	location.set( BodyCannon::getLocationX( location.getX(),
	                                        planet.getRadius(),
	                                        angle ),
	              BodyCannon::getLocationY( location.getY(),
	                                        planet.getRadius(),
	                                        angle ) );
	
}

