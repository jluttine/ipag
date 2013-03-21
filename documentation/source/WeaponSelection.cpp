#include <iostream>
#include "WeaponSelection.h"

/**
 * Class WeaponSelection.
 * Players weaponselection which has all the weapons and functions
 * to handle them.
 * @author Lasse Hakulinen
 */


/**
 * Constructor
 */
WeaponSelection::WeaponSelection(){
	this->selection = -1;
}

/**
 * Destructor
 */
WeaponSelection::~WeaponSelection(){
	this->removeAllWeapons();
}


/**
 * Adds shots to weaponselection
 * @param projectile - index of the projectile
 * @param amount - amount of added shots
 * @param &parameters - parameters of the added shots
 * @return - the amount of successfully added shots
 */
int WeaponSelection::addShots(int shot, int amount,
                              const ParameterList &parameters){
	
	int added = 0;
	bool isDone = false;
	
	for (unsigned int i=0; i < this->weapons.size(); i++){
		
		if (this->weapons[i]->getShot() == shot){
			added = this->weapons[i]->addShots(amount);
			
			if (this->weapons[i]->getShotCount() <= 0){
				this->removeWeaponIndex(i);
			}
			isDone = true;
			break;
		}
	}

	// if shots are added but the right weapon doesn't exist yet
	if (!isDone && amount > 0){
		this->createWeapon(shot, amount, false, parameters);
		added = this->getShotCount(shot);
	}
		
	if (this->weapons.size() > 0){
		this->selection = 0;
	}
	else {
		this->selection = -1;
	}
	
	return added;
}

/**
 * Adds infinite shots
 * @param projectile - index of the projectile
 * @param &parameters - parameters of the added shots
 */
void WeaponSelection::addInfiniteShots(int shot,
                                       const ParameterList &parameters){

	bool isDone = false;
	
	for (unsigned int i=0; i < this->weapons.size(); i++){
		
		if (this->weapons[i]->getShot() == shot){
			this->weapons[i]->addInfiniteShots();
			isDone = true;
			break;
		}
	}
	if (!isDone){
		this->createWeapon(shot, 1, true, parameters);
	}
	
	if (this->weapons.size() > 0){
		this->selection = 0;
	}
	else {
		this->selection = -1;
	}
}

/**
 * Creates a new weapon
 * @param shot - index of the shot
 * @param amout - amount of the shots
 * @param infinite - true if weapon has infinite shots
 * @param &parameters - reference to weapons parameters
 */
void WeaponSelection::createWeapon(int shot, int amount, bool infinite,
                                   const ParameterList &parameters){
	
	Weapon *newWeapon = new Weapon(shot, parameters, amount, infinite);
	this->weapons.push_back(newWeapon);

}
	
/**
 * @param shot - shot which count is wanted
 * @return - the count of wanted shot
 */
int WeaponSelection::getShotCount(int shot) const{
	
	for (unsigned int i=0; i < this->weapons.size(); i++){
		
		if (this->weapons[i]->getShot() == shot){
			return this->weapons[i]->getShotCount();
			break;
		}
	}
	return 0;
}

/**
 * Removes all weapons.
 */
void WeaponSelection::clear() {
	
	this->removeAllWeapons();
}

/**
 * Removes one weapon by index and frees memory allocated by the weapon
 * @param index - index of the weapon to remove
 */
void WeaponSelection::removeWeaponIndex(int index){

	Weapon *oldWeapon;
		
	if (index < 0 || index >= (int)this->weapons.size()){
		std::cerr << "WeaponSelection::removeWeaponIndex: invalid index "
                  << index << std::endl;
				
		return;
	}

	oldWeapon = this->weapons[index];
	this->weapons.erase( this->weapons.begin() + index);
	delete oldWeapon;
	
	// updates selection if needed
	if (index < this->selection){
		this->selection--;
	}
	else if (index == this->selection && index >= (int)this->weapons.size()){
		this->selection = 0;
	}
}

/**
 * Removes one weapon from the selection and
 * frees memory allocated by the weapon
 * @param shot - index of the shot which weapon is removed
 */
void WeaponSelection::removeWeaponType(int shot){
	
	for (unsigned int i=0; i < this->weapons.size(); i++){
		
		if (this->weapons[i]->getShot() == shot){
			this->removeWeaponIndex(i);
			break;
		}
	}
}
		
/**
 * Removes all weapons and frees memory allocated by them
 */
void WeaponSelection::removeAllWeapons(){
	
	for (int i = this->weapons.size() - 1; i >= 0; i--){
		this->removeWeaponIndex(i);
	}
}


/**
 * Fires one shot with currently selected weapon
 */
int WeaponSelection::shoot(){
	int shot;

	if (this->weapons.size() == 0){
		return -1;
	}

	shot = this->weapons[this->selection]->shoot();
	if (this->weapons[this->selection]->getShotCount() <= 0){
		this->removeWeaponIndex(this->selection);
	}

	return shot;
}

/**
 * @return - amount of weapons
 */
int WeaponSelection::getWeaponCount() const {
	
	return this->weapons.size();
}

/**
 * @param shot - index of the shot to check
 * @return true if shot has infinite shots
 */
bool WeaponSelection::hasInfiniteShots(int shot) const {
	
	for (unsigned int i=0; i < this->weapons.size(); i++){
		
		if (this->weapons[i]->getShot() == shot){
			return this->weapons[i]->isInfiniteShots();
			break;
		}
	}
	return false;

}

/**
 * @return - a pointer to selected weapon
 */
const Weapon* WeaponSelection::getSelectedWeapon() const {
	
	if (this->selection < 0 || this->selection >= (int)this->weapons.size()){
		return NULL;
	}
		
	return this->weapons[this->selection];
	
}

/**
 * Selects a weapon.
 * @param change - change in selection
 * @return - a pointer to selected weapon
 */
const Weapon* WeaponSelection::selectWeapon(int change){

	int size = this->weapons.size();

	if (size == 0){
		return NULL;
	}
	change %= size;
	this->selection += change;
	
	if (this->selection < 0){
		this->selection += size;
	}
	else if (this->selection >= size){
		this->selection -= size;
	}
	
	return this->weapons[this->selection];
}

/**
 * Sets the selected weapon
 * @param index - index to which the selected weapon is changed
 * @return - a pointer to selected weapon
 */
const Weapon* WeaponSelection::setSelectedWeapon(int index){
	
	return this->selectWeapon(index - this->selection);
}

/**
 * Increases the parameters of selected weapon
 * @param index - index of the parameter
 * @param steps - steps to increase
 */
void WeaponSelection::increaseParameter(int index, int steps){
	
	if (this->selection < 0 || this->selection >= (int)this->weapons.size()){

		std::cerr << "WeaponSelection::increaseParameter: invalid selection"
                  << index << std::endl;
	}

	else {
		this->weapons[this->selection]->increaseParameter(index, steps);
	}
}
