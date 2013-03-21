
#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "ParameterList.h"

/**
 * Class Weapon.
 * Weapon has a shot type and parameters for it, and also a shotcount.
 * @author Lasse Hakulinen
 */

class Weapon {
	
public:

	static const int maximumCount = 99;
	
	/**
	 * Constructor
	 * @param shot - index of the projectile template
	 * @param &parameters - reference to parameters
	 * @param shotcount - number of shots
	 * @infiniteShots - true if there is infinite shots
	 */
	Weapon(int shot, const ParameterList &parameters, int shotcount = 1,
           bool infiniteShots = false);
	
	/**
	 * Shoots one shot.
	 * @return - shot which was fired
	 */
	int shoot();
	
	/**
	 * Adds shots.
	 * @param amount - amount of added shots
	 * @return - the amount of successfully added shots
	 */
	int addShots(int amount);
	
	/**
	 * Adds infinite shots.
	 */
	inline void addInfiniteShots() { this->infiniteShots = true;
                                     this->shotcount = Weapon::maximumCount; };
									
	/**
	 * @return - the index of the weapon's shot
	 */
	inline int getShot() const { return this->shot; };
	
	/**
	 * @return - the amount of shots
	 */
	inline int getShotCount() const { return this->shotcount; };
	
	/**
	 * @return true if there is infinite shots
	 */
	inline bool isInfiniteShots() const  { return this->infiniteShots; };

	/**
	 * Increases a parameter
	 * @param index - index of the parameter
	 * @param steps - steps to increase
	 */
	void increaseParameter(int index, int steps);	
	
	/**
	 * @return - parameters of the weapon
	 */
	inline ParameterList getParameters() const { return this->parameters; };

private:

	ParameterList parameters;

	int shot; //index of the projectiletemplate
	int shotcount;
	
	bool infiniteShots;
	
};

#endif //_WEAPON_H_
