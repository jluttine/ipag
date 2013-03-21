#include <math.h>

#include "BodyExplosion.h"
#include "images.h"
#include "soundList.h"



/**
 * Contsructor
 * @param type Style of the explosion.
 */
BodyExplosion::BodyExplosion(World &world, float x, float y, EType type)
	: BodyMovable( world, x, y, 0, 0, false, false, false )
{
	this->numParticles = 0;
	this->particles = NULL;
	this->timeLived = 0;
	this->type = type;
	
	switch (type) {
		case BIG_NUCLEAR:
			this->lifetime = 500;
			this->sprite = IMAGE_EXPLOSION_GB;
			createShockwave();
			this->world.playSound(SOUND_EXPLOSION_NB);
			break;
			
		case SMALL_NUCLEAR:
			this->lifetime = 300;
			this->sprite = IMAGE_EXPLOSION_NS;
			this->world.playSound(SOUND_EXPLOSION_NS);
			break;
			
		case BIG_GAS:
			this->lifetime = 500;
			this->sprite = IMAGE_EXPLOSION_GB;
			this->world.playSound(SOUND_EXPLOSION_GB);
			break;
			
		case SMALL_GAS:
			this->lifetime = 500;
			this->sprite = IMAGE_EXPLOSION_GB;
			this->world.playSound(SOUND_EXPLOSION_GS);
			break;
		
		case LASER:
			this->lifetime = 200;
			this->sprite = -1;
			break;
		
		default:
			this->lifetime = 500;
			this->sprite = -1;
	}
}

BodyExplosion::~BodyExplosion() {
	for (int i=0; i<numParticles; i++) {
		delete particles[i].location;
	}
	
	if (this->particles != NULL)
		delete [] this->particles;
}

void BodyExplosion::step(unsigned int timestep) {
	this->timeLived += timestep;
	
	//Move particles
	for (int i = 0; i < this->numParticles; i++) {
		particles[i].timeLived += timestep;
		
		//Advance animation
		particles[i].phase = (float)particles[i].timeLived / particles[i].lifetime;
		
		//Move particle
		particles[i].location->add(particles[i].vx, particles[i].vy);

		if (particles[i].timeLived >= particles[i].lifetime) {
			particles[i].active = false;
		}
	}
	
	//Destroy explosion if time is up
	if (this->timeLived >= this->lifetime)
		this->destroy();
	
	
	//Make it move
	BodyMovable::step(timestep);
}

/**
 * Adds a standard shockwave.
 */
void BodyExplosion::createShockwave() {
	float power, angle;
	
	this->numParticles = 40;
	this->particles = new TParticle[numParticles];
	
	for (int i = 0; i < numParticles; i++) {
		particles[i].location = new Coordinates(this->location);
		particles[i].timeLived = 0;
		particles[i].active = true;
		particles[i].sprite = IMAGE_SMOKE;
		particles[i].phase = 0;

		power = 3 + (float)rand() / RAND_MAX * .5 - .25;
		angle = (float)rand() / RAND_MAX * M_PI * 2;
		
		particles[i].vx = cos(angle) * power;
		particles[i].vy = sin(angle) * power;
		particles[i].lifetime = 400 + rand() % 100;
	}
}

/**
 * Draws explosion on screen.
 */
void BodyExplosion::draw(Graphics &graphics) {
	
	graphics.drawAnimated(this->sprite, this->location,
	                      (float)this->timeLived / this->lifetime);
	drawParticles(graphics);
}

/**
 * Draws particle cloud on screen.
 */
void BodyExplosion::drawParticles(Graphics &graphics) {
	for (int i = 0; i < numParticles; i++) {
		if (particles[i].active) {
			graphics.drawAnimated(particles[i].sprite,
			                      *particles[i].location,
			                      particles[i].phase);
		}
	}
}
