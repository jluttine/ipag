
#ifndef _SHIELD_H_
#define _SHIELD_H_

#include <math.h>

/**
 * Author: Jaakko Luttinen
 * Shield is a class for shield that has an armor value and absorbs damage.
 */
class Shield
{
	
public:

	/**
	 * Price of one armor.
	 */
	static const int armorPrice = 5000;
	
	/**
	 * Maximum absorption.
	 */
	static const float maximumAbsorption = 1.0;
	
	/**
	 * Absorption per one armor.
	 */
	static const float armorStepAbsorption = 0.08;

	/**
	 * Constructs a new shield.
	 */
	Shield()  { this->armor = 0; };
	
	/**
	 * Returns the price of an armor increment.
	 * @param increase Armor increment.
	 * @return Price of the increment.
	 */
	int getIncreasePrice( int increase ) const;

	/**
	 * Increases the armor and returns the cost.
	 * @param increase Armor increment.
	 * @return Cost of the increment.
	 */
	int increase( int increase );
	
	/**
	 * Clears all armor.
	 */
	void clear()  { this->armor = 0; };
	
	/**
	 * Returns armor value.
	 * @return Armor value.
	 */
	inline int getArmor() const  { return this->armor; };
	
	/**
	 * Returns absorption.
	 * @return Absorption (0-1).
	 */
	float getAbsorption() const;
	
	/**
	 * Calculates the absorbed value of the damage.
	 * @param damage Damage to absorb.
	 * @return Absorbed damage value.
	 */
	inline float absorbDamage( float damage ) const
		{ return ( 1.0 - this->getAbsorption() ) * damage; };

private:

	/**
	 * Armor value 0->
	 */
	int armor;
	
};

#endif //_SHIELD_H_
