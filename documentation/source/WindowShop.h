#ifndef _WINDOWSHOP_H_
#define _WINDOWSHOP_H_

#include "Window.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameEngine.h"


/**
 * Class WindowShop.
 * Lets every player to buy weapons and shields for the game.
 * @author Lasse Hakulinen
 */

class WindowShop : public Window {
	
public:

	/**
	 * @param &graphics - reference to the graphics
	 * @param &sounds - reference to the sounds
	 * @param &gameEngine - reference to the gameEngine
	 */
	WindowShop(Graphics &graphics, Sounds &sounds, GameEngine &gameEngine);
	
	/**
	 * Frees all memory allocated by WindowShop
	 */
	~WindowShop();

	/**
	 * Shows the windowShop
	 */
	void show();
	
	/**
	 * Redraws the screen
	 */
	void redraw();
	
	/**
	 * Takes one timestep
	 * @param timestep - timestep to take
	 */
	virtual void step(int timestep);
	
	/**
	 * Handles key down events
	 * @param keysym - Event information.
	 */
	virtual void keyDown(SDL_keysym keysym);
	
	/**
	 * Handles mouse up events
	 * @param button - Event information.
	 */
	virtual void mouseUp(SDL_MouseButtonEvent button);
	
private:

	#define STARTINGMONEY 100000
		
	/**
	 * Updates all fields in windowShop
	 */
	void updateFields();
	
	/**
	 * Updates descriptionField
	 * @param projectile - index of the projectile which
	 *                     description is wanted
	 */
	void updateDescriptionField(int projectile);

	/**
	 * Closes windowShop
	 */	
	void startGame();
	
	/**
	 * Resets all properties of a player
	 * @param player - player whose properties is reseted
	 */
	void resetPlayerProperties(Player* player);

	GameEngine &gameEngine;	
	unsigned int activePlayerIndex;
	int projectileCount;
	
	//UI components
	UIText *textTitle;
	UIText *textPlayer;
	UIText *textMoney;
	UIText *textDescription, *textDescriptionTitle, *textDescriptionName;
	UIText *textDescriptionPrice, *textDescriptionDamage;
	UIText *textArmor, *textArmorPrice, *textArmorAbsorption;
	UIText **textsProjectileCount, **textsProjectilePrice;

	UIButton *buttonBuyArmor, *buttonSellArmor;
	UIButton **buttonsBuy;
	UIButton **buttonsSell;
	UIButton **buttonsProjectile;
	UIButton *buttonNextPlayer;
	UIButton *buttonQuit;
	UIButton *buttonRandomWeapons, *buttonClearAll;
};

#endif //_WINDOWSHOP_H_
