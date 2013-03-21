#include <iostream>
#include <string>
#include "WindowShop.h"
#include "images.h"

using std::cerr;
using std::endl;


/**
 * Class WindowShop.
 * Lets every player to buy weapons and shields for the game.
 * @author Lasse Hakulinen
 */

/**
 * @param &graphics - reference to the graphics
 * @param &sounds - reference to the sounds
 * @param &gameEngine - reference to the gameEngine
 */
WindowShop::WindowShop(Graphics &graphics, Sounds &sounds,
                       GameEngine &gameEngine)
                       : Window(graphics, sounds), gameEngine(gameEngine){
		
				
	int i;
	this->activePlayerIndex = 0;
	
	//Misc texts
	this->textTitle = new UIText(*this, "SHOP", 500, 70);
	this->textPlayer = new UIText(*this, 100, 150);
	this->textMoney = new UIText(*this, 300, 150);
	
	//Buttons and text field for buying armor.
	this->textArmor = new UIText(*this, "Shield", 100, 210);
	this->buttonSellArmor = new UIButton(*this, "  -  ", 275, 210);
	this->textArmorAbsorption = new UIText(*this, "0%", 330, 210);
	this->buttonBuyArmor = new UIButton(*this, "  +  ", 355, 210);
	this->textArmorPrice = new UIText(*this, "0", 430, 210);
	
	//Buttons and text fields for buying weapons.
	this->projectileCount = this->gameEngine.getProjectileTemplateCount();
	this->buttonsBuy = new UIButton*[this->projectileCount];
	this->buttonsSell = new UIButton*[this->projectileCount];
	this->buttonsProjectile = new UIButton*[this->projectileCount];
	this->textsProjectileCount = new UIText*[this->projectileCount];
	this->textsProjectilePrice = new UIText*[this->projectileCount];
	
	for ( i = 0; i < this->projectileCount; i++ ) {
	
		this->buttonsProjectile[i] = new UIButton(*this,
            this->gameEngine.getProjectileTemplate(i)->getName(),
            100, 250 + 20 * i);
			
		this->buttonsSell[i] = new UIButton(*this,"  -  ",275, 250 + 20 * i);
		this->textsProjectileCount[i] = new UIText(*this,"0",330, 250 + 20*i);
		this->buttonsBuy[i] = new UIButton(*this, "  +  ", 355, 250 + 20 * i);
		this->textsProjectilePrice[i] = new UIText(*this,"0",430, 250 + 20*i);
		
		this->addComponent(this->buttonsProjectile[i]);
		this->addComponent(this->buttonsBuy[i]);
		this->addComponent(this->textsProjectileCount[i]);
		this->addComponent(this->buttonsSell[i]);
		this->addComponent(this->textsProjectilePrice[i]);
			
	}
	
	this->textDescriptionTitle = new UIText(*this, 600, 210);
	this->textDescriptionName = new UIText(*this, 600, 250);
	this->textDescriptionPrice = new UIText(*this, 600, 270);
	this->textDescriptionDamage = new UIText(*this, 600, 290);
	this->textDescription = new UIText(*this, 600, 320);
	this->updateDescriptionField(-1); //No item selected...
		
	//Buttons
	this->buttonNextPlayer = new UIButton(*this, "Next player", 800, 650);
	this->buttonQuit = new UIButton(*this, "Back to Main menu", 70, 650);
	
	this->buttonRandomWeapons = new UIButton(*this,
	                                  "Make a random selection", 600, 450);
	                                  
	this->buttonClearAll = new UIButton(*this, "Clear all", 600, 490);
	
	addComponent(this->textTitle);
	addComponent(this->textPlayer);
	addComponent(this->textMoney);
	addComponent(this->textDescriptionTitle);
	addComponent(this->textDescriptionName);
	addComponent(this->textDescriptionPrice);
	addComponent(this->textDescriptionDamage);
	addComponent(this->textDescription);
	addComponent(this->buttonNextPlayer);
	addComponent(this->buttonQuit);
	addComponent(this->buttonRandomWeapons);
	addComponent(this->buttonClearAll);

	//Armor UI-components.
	addComponent(this->textArmor);
	addComponent(this->textArmorAbsorption);
	addComponent(this->buttonBuyArmor);
	addComponent(this->buttonSellArmor);
	addComponent(this->textArmorPrice);
	
}

/**
 * Frees all memory allocated by WindowShop
 */
WindowShop::~WindowShop(){
	int i;
	
	delete this->textTitle;
	delete this->textPlayer;
	delete this->textMoney;

	delete this->textDescriptionTitle;
	delete this->textDescriptionName;
	delete this->textDescriptionPrice;
	delete this->textDescriptionDamage;
	delete this->textDescription;
	delete this->buttonNextPlayer;
	delete this->buttonQuit;
	delete this->buttonRandomWeapons;
	delete this->buttonClearAll;

	//Armor UI-components.	
	delete this->textArmor;
	delete this->textArmorAbsorption;
	delete this->buttonBuyArmor;
	delete this->buttonSellArmor;
	delete this->textArmorPrice;

	for (i = 0; i < this->projectileCount; i++){
		delete this->buttonsBuy[i];
		delete this->buttonsSell[i];
		delete this->buttonsProjectile[i];
		delete this->textsProjectileCount[i];
		delete this->textsProjectilePrice[i];
	}

	delete[] this->buttonsBuy;
	delete[] this->buttonsSell;
	delete[] this->buttonsProjectile;
	delete[] this->textsProjectileCount;	
	delete[] this->textsProjectilePrice;	
		
}

/**
 * Shows the windowShop
 */
void WindowShop::show(){
	int i;
	Player *player;

	// Resets every player's properties
	for (i = 0; i < this->gameEngine.getPlayerCount(); i++){
		player = this->gameEngine.getPlayer(i);
		this->resetPlayerProperties(player);
	}
	
	//Update components initially
	this->updateFields();

	//Update window
	redraw();
}

/**
 * Redraws the screen
 */
void WindowShop::redraw() {
	this->graphics.clear();  //Clear screen
	this->graphics.drawSprite(IMAGE_BACKGROUND, 0, 0);
	this->update();          //Draw components
	this->graphics.update(); //Update screen
}

/**
 * Updates all fields in windowShop
 */
void WindowShop::updateFields(){

	int i;
	char number[30];
	Player *player = this->gameEngine.getPlayer(this->activePlayerIndex);
	this->textPlayer->setText(player->getName());
	
	if (!player->getAI() && player->getCannon()){	
	
		for ( i = 0; i < this->projectileCount; i++ ) {
			sprintf(number, "%d",
			        player->getWeaponSelection().getShotCount(i));
			        
			this->textsProjectileCount[i]->setText(number);
			
			if (!player->getWeaponSelection().hasInfiniteShots(i)) {
				sprintf(number, "%d",
                     this->gameEngine.getProjectileTemplate(i)->getPrice());
					
				this->textsProjectilePrice[i]->setText(number);
				this->buttonsBuy[i]->setText("  +  ");
				this->buttonsSell[i]->setText("  -  ");
			}
			else {
				this->textsProjectilePrice[i]->setText("");
				this->buttonsBuy[i]->setText("");
				this->buttonsSell[i]->setText("");
			}
		}


		sprintf(number, "%d",
		       (int)(player->getShield().getAbsorption() * 100));
		       
		string temptxt = number;
		temptxt += "%";
		this->textArmorAbsorption->setText(temptxt.c_str());
		sprintf( number, "%d", player->getShield().getArmor());
		sprintf(number, "%d", Shield::armorPrice);
		this->textArmorPrice->setText(number);
		
		this->buttonNextPlayer->setText("START GAME");
		
		//Checks if there are any human players left to do shopping
		for (int i=activePlayerIndex+1;
		     i < this->gameEngine.getPlayerCount(); i++){
		     	
			Player *tempPlayer = this->gameEngine.getPlayer(i);
			
			if (!tempPlayer->getAI()){
				this->buttonNextPlayer->setText("Next player");
				break;
			}
		}
						
		sprintf( number, "Money: %d", player->getMoney() );
		this->textMoney->setText( number );
	}
	
	else {			
		if (player->getAI()){
			player->getAI()->doShopping();
		}
		
		//Select next player
		activePlayerIndex++;
		
		//If this was the last player
		if ((int)activePlayerIndex >= this->gameEngine.getPlayerCount()) {
			activePlayerIndex = 0;
			this->startGame();
			return;
		}
		this->updateFields();
	}

}

/**
 * Updates descriptionField
 * @param projectile - index of the projectile which description is wanted
 */
void WindowShop::updateDescriptionField( int projectileIndex ){	
	
	string text;
	char number[30];
	const Projectile *projectile =
	      this->gameEngine.getProjectileTemplate(projectileIndex);
	
	if (projectile) {
		
		this->textDescriptionTitle->setText("ITEM DESCRIPTION");
		
		text = "Name:   ";
		text += projectile->getName();
		this->textDescriptionName->setText(text.c_str());
		
		text = "Price:  ";
		sprintf(number, "%d", projectile->getPrice());		
		text += number;
		this->textDescriptionPrice->setText(text.c_str());
		
		text = "Damage: ";		
		string temp;
		projectile->getDamageText(temp);
		text += temp;
		this->textDescriptionDamage->setText(text.c_str());
		
		text = projectile->getDescription();
		this->textDescription->setText(text.c_str());
		
	}
	else {
		this->textDescriptionTitle->setText("ITEM DESCRIPTION");
		this->textDescriptionName->setText("Please select a weapon");
		this->textDescriptionPrice->setText("to get description.");
		this->textDescriptionDamage->setText("");
		this->textDescription->setText("");
	}
	
}

/**
 * Takes one timestep
 * @param timestep - timestep to take
 */
void WindowShop::step(int timestep) {
//	this->graphics.update(false);
}

/**
 * Handles key down events
 * @param keysym - key that is pressed
 */
void WindowShop::keyDown(SDL_keysym keysym){
	
	switch (keysym.sym) {
		case SDLK_ESCAPE:
			this->close(0);
			break;
		
		default:
			break;
	}
	
	redraw();
}

/**
 * Handles mouse up events
 * @param button - button that is pressed
 */
void WindowShop::mouseUp(SDL_MouseButtonEvent button){

	//Find out if a button was hit
	UIComponent *component = findComponent(button.x, button.y);
	int i;
	
	
	Player *player = this->gameEngine.getPlayer(this->activePlayerIndex);
	
	if (component == buttonNextPlayer) {		
		this->sounds.playSound(SOUND_CLICK);
		
		//Select next player
		activePlayerIndex++;
		
		//If this was the last player
		if ((int)activePlayerIndex >= this->gameEngine.getPlayerCount()) {
			activePlayerIndex = 0;
			this->startGame();
			return;
		}
		this->updateFields();
	}
	
	else if (component == buttonQuit) {
		this->sounds.playSound(SOUND_CLICK);
		this->close(0);
	}
	
	else if (component == this->buttonRandomWeapons) {
		this->sounds.playSound(SOUND_CLICK);
		Ai *tempAi = new Ai(*player);
		tempAi->doShopping();
		delete tempAi;
		this->updateFields();
	}
	
	else if (component == this->buttonClearAll){
		this->sounds.playSound(SOUND_CLICK);
		this->resetPlayerProperties(player);
		this->updateFields();
	}
	
	else if (component == this->buttonBuyArmor) {
		if (player->buyShieldArmor(1)) {
			this->sounds.playSound(SOUND_CLICK);
			this->updateFields();
		}
		else {
			this->sounds.playSound(SOUND_TICK);
		}
	}
	else if (component == this->buttonSellArmor) {
		if (player->buyShieldArmor(-1)) {
			this->sounds.playSound(SOUND_CASH);
			this->updateFields();
		}
		else {
			this->sounds.playSound(SOUND_TICK);
		}
	}
	
	for (i = 0; i < this->projectileCount; i++) {
		
		if (component == this->buttonsBuy[i]) {
			if ( player->buyShots(i,1) ) {
				this->sounds.playSound(SOUND_CLICK);
				this->updateFields();
			}
			else {
				this->sounds.playSound(SOUND_TICK);
			}
		}
		
		else if (component == this->buttonsSell[i]) {
			if (player->buyShots(i,-1)) {
				this->sounds.playSound(SOUND_CASH);
				this->updateFields();
			}
			else {
				this->sounds.playSound(SOUND_TICK);
			}
		}

		else if (component == this->buttonsProjectile[i]) {
			this->sounds.playSound(SOUND_CLICK);
			this->updateDescriptionField( i );
		}

	}
	
	redraw();
}

/**
 * Closes windowShop
 */	
void WindowShop::startGame(){
	
	this->close(1);
}

/**
 * Resets all properties of a player
 * @param player - player whose properties is reseted
 */
void WindowShop::resetPlayerProperties(Player* player){

	player->setIntegrity(100); // Fixes the cannon
	player->clearWeaponSelection();
	player->clearPoints();
	player->clearArmor();
	player->setMoney(STARTINGMONEY);
	player->addInfiniteShots(0);
	player->addInfiniteShots(1);
}
	
