#ifndef _WEAPONSELECTION_H_
#define _WEAPONSELECTION_H_

class WeaponSelection;

#include <vector>
#include "Weapon.h"

using std::vector;

/**
 * Class WeaponSelection.
 * Players weaponselection which has all the weapons and functions
 * to handle them.
 * @author Lasse Hakulinen
 */

class WeaponSelection {
	
public:
	
	/**
	 * Constructor
	 */
	WeaponSelection();
	
	/**
	 * Destructor
	 */
	~WeaponSelection();

	/**
	 * Adds shots to weaponselection
	 * @param projectile - index of the projectile
	 * @param amount - amount of added shots
	 * @param &parameters - parameters of the added shots
	 * @return - the amount of successfully added shots
	 */
	int addShots(int projectile, int amount, const ParameterList &parameters);
	
	/**
	 * Adds infinite shots
	 * @param projectile - index of the projectile
	 * @param &parameters - parameters of the added shots
	 */
	void addInfiniteShots(int projectile, const ParameterList &parameters);
	
	/**
	 * @param shot - shot which count is wanted
	 * @return - the count of wanted shot
	 */
	int getShotCount(int shot) const;
	
	/**
	 * @param shot - index of the shot to check
	 * @return true if shot has infinite shots
	 */
	bool hasInfiniteShots(int shot) const;
	
	/**
	 * Fires one shot with currently selected weapon
	 */
	int shoot();

	/**
	 * @return - a pointer to selected weapon
	 */
	const Weapon* getSelectedWeapon() const;
	
	/**
	 * Selects a weapon.
	 * @param change - change in selection
	 * @return - a pointer to selected weapon
	 */
	const Weapon* selectWeapon(int change);
	
	/**
	 * Sets the selected weapon
	 * @param index - index to which the selected weapon is changed
	 * @return - a pointer to selected weapon
	 */
	const Weapon* setSelectedWeapon(int index);
	
	/**
	 * @return - amount of weapons
	 */
	int getWeaponCount() const;
	
	/**
	 * Increases the parameters of selected weapon
	 * @param index - index of the parameter
	 * @param steps - steps to increase
	 */
	void increaseParameter(int index, int steps);
	
	/**
	 * Removes all weapons.
	 */
	void clear();

private:
	
	/**
	 * Removes one weapon from the selection and
	 * frees memory allocated by the weapon
	 * @param shot - index of the shot which weapon is removed
	 */
	void removeWeaponType(int shot);
	
	/**
	 * Removes one weapon by index and frees memory allocated by the weapon
	 * @param index - index of the weapon to remove
	 */
	void removeWeaponIndex(int index);
	
	/**
	 * Removes all weapons and frees memory allocated by them
	 */
	void removeAllWeapons();
	
	/**
	 * Creates a new weapon
	 * @param shot - index of the shot
	 * @param amout - amount of the shots
	 * @param infinite - true if weapon has infinite shots
	 * @param &parameters - reference to weapons parameters
	 */
	void createWeapon(int shot, int amount, bool infinite,
						const ParameterList &parameters);

	
	vector<Weapon*> weapons;	
	int selection;
	
};
#endif //_WEAPONSELECTION_H_

