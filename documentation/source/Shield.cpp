
#include "Shield.h"

/**
 * Returns the price of an armor increment.
 * @param increase Armor increment.
 * @return Price of the increment.
 */
int Shield::getIncreasePrice( int increase ) const
{
	
	if ( this->armor + increase < 0 )
		increase = -this->armor;

	return increase * Shield::armorPrice;
}

/**
 * Returns absorption.
 * @return Absorption (0-1).
 */
float Shield::getAbsorption() const
{
	
	if ( this->armor > 0 )
	{
		return Shield::maximumAbsorption
		       * ( 1 - pow( 1-Shield::armorStepAbsorption, this->armor ) );
	}
	else
		return 0;
	
}

/**
 * Increases the armor and returns the cost.
 * @param increase Armor increment.
 * @return Cost of the increment.
 */
int Shield::increase( int increase )
{
	
	if ( this->armor + increase < 0 )
		increase = -this->armor;
		
	this->armor += increase;
	
	return increase * Shield::armorPrice;
	
}
