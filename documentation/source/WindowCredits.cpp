
#include "WindowCredits.h"
#include "images.h"


/**
 * Class WindowCredits.
 * Shows the developers of the game.
 * @author Lasse Hakulinen
 */

/**
 * @param &graphics - reference to the graphics
 * @param &sounds - reference to the sounds
 */
WindowCredits::WindowCredits(Graphics &graphics, Sounds &sounds)
	: Window(graphics, sounds) {		
	
	this->textTitle = new UIText(*this, "INTERPLANETARY ARTILLERY GAME",
	                             400, 80);
	                             
	this->textDevelopers = new UIText(*this,
    "Developers:\n\nJaakko Luttinen\nTapio Auvinen\nLasse Hakulinen",
    200, 200);
			
	this->textSpecial = new UIText(*this,
    "Artwork: Jaakko Luttinen\nSounds: Lasse Hakulinen", 200, 350);
		
	this->textMade = new UIText(*this, "Made in Otaniemi 2005", 200, 550);
	
	this->buttonBack = new UIButton(*this, "Back to Main menu", 80, 650);
	
	addComponent(this->textTitle);
	addComponent(this->textDevelopers);
	addComponent(this->textSpecial);
	addComponent(this->textMade);
	addComponent(this->buttonBack);
	
}

/**
 * Frees all memory allocated by WindowCredits
 */
WindowCredits::~WindowCredits(){
	
	delete this->textTitle;
	delete this->textDevelopers;
	delete this->textSpecial;
	delete this->textMade;
	delete this->buttonBack;
		
}

/**
 * Shows the windowCredits
 */
void WindowCredits::show(){

	redraw();
}

/**
 * Redraws the screen
 */
void WindowCredits::redraw() {
	
	this->graphics.clear();  //Clear screen
	this->graphics.drawSprite(IMAGE_BACKGROUND, 0, 0);
	this->update();          //Draw components
	this->graphics.update(); //Update screen
}


/**
 * Takes one timestep
 * @param timestep - timestep to take
 */
void WindowCredits::step(int timestep) {

}

/**
 * Handles key down events
 * @param keysym - key that is pressed
 */
void WindowCredits::keyDown(SDL_keysym keysym){
	
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
void WindowCredits::mouseUp(SDL_MouseButtonEvent button){

	//Find out if a button was hit
	UIComponent *component = findComponent(button.x, button.y);
		
	if (component == buttonBack) {
		this->sounds.playSound(SOUND_CLICK);
		this->close(0);
	}
	
	redraw();
}
