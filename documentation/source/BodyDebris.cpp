#include "BodyDebris.h"
#include "images.h"

/**
 * Constructor
 * @param x location, world coordinates
 * @param y location, world coordinates
 * @param fireAmount probablity that a single created particle is in fire.
 *                   [0..1] 0 means a dull gray debris field and 1 an explosion
 */
BodyDebris::BodyDebris(World &world, float x, float y, float fireAmount)
	: BodyMovable(world, x, y, 4, 10, false, false, true)
{
	if ((float)rand() / RAND_MAX > fireAmount) {
		//Create a gray particle
		this->sprite = IMAGE_DEBRIS;
		
		//Select a random frame to add diversity
		this->imagePhase = (float)rand() / RAND_MAX;
	} else {
		//Create a fireball
		this->sprite = IMAGE_EXPLOSION_GB;
		this->imagePhase = 0;
	}
}

BodyDebris::~BodyDebris() {
}

/**
 * Draws debris on screen.
 */
void BodyDebris::draw(Graphics &graphics) {
	graphics.drawAnimated(this->sprite, this->location, this->imagePhase);
}
