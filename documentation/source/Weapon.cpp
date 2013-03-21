
#include <iostream>
#include "Weapon.h"

/**
 * Class Weapon.
 * Weapon has a shot type and parameters for it, and also a shotcount.
 * @author Lasse Hakulinen
 */


/**
 * Constructor.
 * @param shot - index of the projectile template
 * @param &parameters - reference to parameters
 * @param shotcount - number of shots
 * @infiniteShots - true if there is infinite shots
 */
Weapon::Weapon(int shot, const ParameterList &parameters, int shotcount,
               bool infinite) : parameters(parameters) {
		
	this->shot = shot;
	this->shotcount = shotcount;		
	this->infiniteShots = false;
	if (infinite){
		this->addInfiniteShots();
	}
}

/**
 * Shoots one shot.
 * @return - shot which was fired
 */
int Weapon::shoot() {

	if (!this->infiniteShots && this->addShots(-1) != -1){
		std::cerr << "Weapon::shoot You don't have any shots\n";
	}

	return this->shot;	
}

/**
 * Adds shots.
 * @param amount - amount of added shots
 * @return - the amount of successfully added shots
 */
int Weapon::addShots(int amount){
	
	int added;
	
	if (this->infiniteShots){
		return 0;
	}

	if (-amount >= this->shotcount){
		added = -this->shotcount;
		this->shotcount = 0;
		return added;
	}
	
	if (this->shotcount + amount >= this->maximumCount){
		added = this->maximumCount - this->shotcount;
		this->shotcount = this->maximumCount;
		return added;
	}
	this->shotcount += amount;
	return amount;
}

/**
 * Increases a parameter
 * @param index - index of the parameter
 * @param steps - steps to increase
 */
void Weapon::increaseParameter(int index, int steps) {
	
	this->parameters.increaseParameterValue(index, steps);
	
}

