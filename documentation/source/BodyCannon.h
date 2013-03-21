
#ifndef _BODYCANNON_H_
#define _BODYCANNON_H_

class BodyCannon;

#include "Body.h"
#include "Player.h"
#include "BodyPlanet.h"
#include "Projectile.h"

/**
 * Author: Jaakko Luttinen
 * BodyCannon is a class for players' cannons. Cannons are on the surface of
 * a planet. Cannon's aiming power and angle may be set and then the cannon
 * may be ordered to shoot a given projectile. BodyCannon is owned by a
 * player. When player is killed the cannon is not destroyed but ruined.
 */
class BodyCannon  :  public Body
{
	
public:

	/**
	 * The minimum aiming power.
	 */
	static const float minimumPower = 0.2;
	
	/**
	 * The maximum aiming power.
	 */
	static const float maximumPower = 0.7;
	
	/**
	 * Calculates the coordinates on the surface of a planet. The angle is
	 * given.
	 * @param location      The coordinates to store the location.
	 * @param planet        The planet.
	 * @param angleOnPlanet Angle on planet (radius).
	 */
	static void calculateLocation( Coordinates &location,
	                               const BodyPlanet &planet,
	                               float angleOnPlanet );

	/**
	 * Constructs a new cannon.
	 * @param planet The planet which the cannon will be put on.
	 * @param angle  The angle on the planet.
	 * @param owner  The player to own the cannon. Note, the cannon is not
	 *               given to player by this function.
	 */
	BodyCannon( BodyPlanet &planet, float angle, Player &owner );
	
	/**
	 * Destructs the cannon.
	 */
	virtual ~BodyCannon();
	
	/**
	 * Sets the planet of the cannon. If the planet is not from the same world
	 * as the cannon, the request is ignored.
	 * @param planet The new planet for cannon.
	 */
	void setPlanet( BodyPlanet &planet );
	
	/**
	 * Sets the angle of the cannon on the planet.
	 * @param angle Angle on planet (radius).
	 */
	void setAngleOnPlanet( float angle );
	
	/**
	 * Tells the planet cannon is on.
	 * @return The planet which the cannon is on.
	 */
	inline const BodyPlanet& getPlanet() const  { return *this->planet; };
	
	/**
	 * Tells the cannon's angle on the planet.
	 * @return The angle on the planet.
	 */
	inline float getAngleOnPlanet() const  { return this->angleOnPlanet; };
	
	/**
	 * Tells the player who owns the cannon.
	 * @return The player who owns the cannon.
	 */
	inline Player& getOwner()  { return this->owner; };

	/**
	 * Sets aiming angle (0-Pi).
	 * @param angle The aiming angle.
	 */	
	void setAimingAngle( float angle );
	
	/**
	 * Sets aiming power (minimumPower-maximumPower).
	 * @param power The aiming power.
	 */
	void setAimingPower( float power );
	
	/**
	 * Tells aiming angle.
	 * @return The aiming angle.
	 */
	inline float getAimingAngle() const  { return this->aimingAngle; };
	
	/**
	 * Tells aiming power.
	 * @return The aiming power.
	 */
	inline float getAimingPower() const  { return this->aimingPower; };

	/**
	 * Shoots the given shot with the angle and power that has been set. The
	 * memory allocation of the bullet will be freed by BodyProjectile.
	 * @param bullet The projectile to shoot.
	 */
	void shoot( Projectile &bullet );
	
	/**
	 * Sets the cannon active state. Active cannon has sight drawn.
	 * @param active Tells whether the cannon is active.
	 */
	inline void setActive( bool active )  { this->active = active; };
	
	/**
	 * Updates the location of the cannon using the location of the planet and
	 * cannon's angle on the planet.
	 */
	void updateLocation();
	
	/**
	 * Ruins the cannon.
	 */
	void ruin();
	
	/**
	 * Tells whether the cannon is ruined.
	 * @return Tells whether the cannon is ruined.
	 */
	inline bool isRuined() const  { return this->ruined; };

	/**
	 * Visualizes the cannon to the given graphics system. Also draws energy
	 * bar and sight if active.
	 * @param graphics The graphics system.
	 */
	virtual void draw(Graphics &graphics);

private:

	/**
	 * The player who owns the cannon.
	 */
	Player &owner;
	
	/**
	 * The planet whose surface the cannon is on. Do NOT free the memory.
	 * World will do that.
	 */
	BodyPlanet *planet;
	
	/**
	 * The angle on planet.
	 */
	float angleOnPlanet;
	
	/**
	 * The aiming angle (0-Pi).
	 */
	float aimingAngle;
	
	/**
	 * The aiming power (minimumPower-maximumPower).
	 */
	float aimingPower;
	
	/**
	 * Tells whether the cannon is ruined.
	 */
	bool ruined;
	
	/**
	 * Tells whether the cannon is active.
	 */
	bool active;

	/**
	 * The sprite index of the crosshair.
	 */
	int crosshair;
	
	/**
	 * Returns the x-coordinate of the cannon. x is the x-coordinate of
	 * circle's center point. radius is the radius of the circle. angle is the
	 * angle of cannon's location. 
	 * @param x      X-coordinate of the circle.
	 * @param radius Radius of the circle.
	 * @param angle  Angle to point on surface.
	 */
	static float getLocationX( float x, float radius, float angle );

	/**
	 * Returns the y-coordinate of the cannon. y is the y-coordinate of
	 * circle's center point. radius is the radius of the circle. angle is the
	 * angle of cannon's location. 
	 * @param y      Y-coordinate of the circle.
	 * @param radius Radius of the circle.
	 * @param angle  Angle to point on surface.
	 */
	static float getLocationY( float y, float radius, float angle );
	
	/**
	 * Fixes the number to 0-max. For example, -2 -> max-2, 2*max+1 -> 1.
	 */
	static void fix( float &number, float max );

};

#endif //_BODYCANNON_H_
