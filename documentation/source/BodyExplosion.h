#ifndef _BODY_EXPLOSION_H_
#define _BODY_EXPLOSION_H_

#include "BodyMovable.h"

/**
 * BodyExplosion is a visual effect. It does not do any damage or interact
 * with any object in any way. BodyExplosion destroys itself after timeout.
 * @author Tapio Auvinen
 */
 
class BodyExplosion  :  public BodyMovable {
public:

	/**
	 * Explosion types
	 */
	typedef enum {BIG_NUCLEAR, SMALL_NUCLEAR,
	              BIG_GAS, SMALL_GAS, LASER} EType;
	
	/**
	 * Contsructor.
	 * @param &world Reference to game world
	 * @param x location, world coordinates
	 * @param y location, world coordinates
	 * @param type Style of the explosion. Styles are: BIG_NUCLEAR,
	 *             SMALL_NUCLEAR, BIG_GAS, SMALL_GAS, LASER
	 */
	BodyExplosion(World &world, float x, float y, EType type);
	
	/**
	 * Destructor
	 */
	~BodyExplosion();

	/**
	 * Step() makes the explosion move.
	 * @param timestep timestep in milliseconds
	 */
	void step(unsigned int timestep);
	
	/**
	 * Draws explosion on screen.
	 * @param &graphics Reference to graphics
	 */
	void draw(Graphics &graphics);

private:
	/**
	 * Adds a standard shockwave.
	 */
	void createShockwave();
	
	/**
	 * Draws particle cloud on screen.
	 * @param &graphics Reference to graphics
	 */
	void drawParticles(Graphics &graphics);
	
	typedef struct {
		Coordinates *location;
		float vx;      //Velocity
		float vy;      //Velocity
		int sprite;    //Sprite index
		float phase;   //Animation phase
		int timeLived;
		int lifetime;
		bool active;
	} TParticle;
	
	int lifetime, timeLived; //Lifetime of the object
	EType type;              //Explosion type
	
	TParticle *particles; //Particle cloud
	int numParticles;     //Number of particles
};

#endif //_BODY_EXPLOSION_H_
