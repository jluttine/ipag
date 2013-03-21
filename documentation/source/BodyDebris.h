#ifndef _BODY_DEBRIS_H_
#define _BODY_DEBRIS_H_

#include "BodyMovable.h"

/**
 * BodyDebris represents dirt flying in the air after an expolsion. It does
 * not interact with other particles. A single object is a single particle so
 * you probably want to create a few of these at once.
 * @author Tapio Auvinen
 */

class BodyDebris : public BodyMovable {
public:

	/**
	 * Constructor.
	 * @param &world Reference to game world
	 * @param x location, world coordinates
	 * @param y location, world coordinates
	 * @param fireAmount probablity that a single created particle is in
	 *                   fire. [0..1] 0 means a dull gray debris field and
	 *                   1 an explosion.
	 */
	BodyDebris(World &world, float x, float y, float fireAmount);
	
	/**
	 * Destructor
	 */
	~BodyDebris();

	/**
	 * Draws it's own image on screen.
	 * @param &graphics Reference to graphics
	 */
	void draw(Graphics &graphics);
	
private:
	float imagePhase;  //A random frame is selected from the bitmap to add
	                   //diversity
};

#endif
