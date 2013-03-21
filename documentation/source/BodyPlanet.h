
#ifndef BODYPLANET_H
#define BODYPLANET_H

class BodyPlanet;

#include <vector>
#include "Body.h"
#include "BodyCannon.h"
#include "Graphics.h"
#include "Sprite.h"

/**
 * Author: Jaakko Luttinen
 * BodyPlanet is a class for planets. Planets are non-moving, rotating
 * circle-shaped bodies with mass. There are three different sizes and four
 * different looks. Planet has also "End of round" -procedures: it rotates a
 * bit.
 */
class BodyPlanet : public Body {

public:

	typedef enum {SMALL, MEDIUM, LARGE} ESize;
	typedef enum {MARS, ALIEN, EARTH, ICE} EType;

	/**
	 * Constructs a new planet.
	 * @param world           The world which the planet is created into.
	 * @param x               X-coordinate in the world.
	 * @param y               Y-coordinate in the world.
	 * @param size            One of the three sizes.
	 * @param type            One of the four types.
	 * @param angularVelocity Tells the "End of round" angle rotation.
	 */
	BodyPlanet( World &world, float x, float y, ESize size, EType type,
	            float angularVelocity );
	
	/**
	 * Destructs the planet.
	 */
	virtual ~BodyPlanet();

	/**
	 * Rotates the planet. Also tells the cannons on its surface to update
	 * their locations.
	 * @param angle The angle to rotate (radian).
	 */	
	void rotate( float angle );
	
	/**
	 * Tells the angle of the planet's axis.
	 * @return The angle of the planet's axis.
	 */
	inline float getAngle() const  { return this->angle; };
	
	/**
	 * At the end of round, planet will rotate a bit. This function may be
	 * called many times to create a fluent rotation. Step will determine the
	 * relative rotation (0-1).
	 * @param step Relative step length (0-1). The sum is eventually 1.
	 */
	virtual void endOfRound( float step )
		{ this->rotate( step * this->rotatingAngle ); };

	/**
	 * Raises the flag to show that the planet is destroyed and should be
	 * removed from the world. Will also destroy all the cannons on its
	 * surface.
	 */	
	virtual void destroy();

	/**
	 * Tells whether the planet has the given cannon on its surface.
	 * @param cannon A cannon to look for.
	 * @return Tells whether the planet has the given cannon on its surface.
	 */	
	bool hasCannon(BodyCannon &cannon) const;
	
	/**
	 * Adds the given cannon to planet's surface.
	 * @param cannon A cannon to add.
	 */
	void addCannon(BodyCannon &cannon);
	
	/**
	 * Removes a cannon from planet by index.
	 * @param index Index of the cannon to remove.
	 */
	void removeCannon(int index);
	
	/**
	 * Removes the cannon from planet.
	 * @param cannon The cannon to remove.
	 */
	void removeCannon( BodyCannon &cannon);
	
	/**
	 * Removes all cannons from the planet.
	 */
	void removeAllCannons();
	
	/**
	 * Does drawing procedures.
	 * @param graphics The graphics object to draw to.
	 */
	void draw( Graphics &graphics );
	
private:

	/**
	 * Current angle of the axis.
	 */
	float angle;
	
	/**
	 * End of round rotation.
	 */
	float rotatingAngle;
	
	/**
	 * Cannons on planet's surface. Does NOT free the memory allocations.
	 * World will do that.
	 */
	vector<BodyCannon*> cannons;
	
	/**
	 * The sprite.
	 */
	Sprite *image;

};

#endif
