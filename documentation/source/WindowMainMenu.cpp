#include "images.h"
#include "WindowMainMenu.h"
#include "WindowCredits.h"

/**
 * Class WindowMainMenu
 * Window that shows the main menu
 * @author Lasse Hakulinen
 */

/**
 * Constructor
 * @param &graphics - reference to the graphics
 * @param &sounds - reference to the sounds
 */
WindowMainMenu::WindowMainMenu(Graphics &graphics, Sounds &sounds)
    : Window(graphics, sounds) {
    	
	this->buttonStart = new UIButton(*this, "Start game", 470, 200);
	this->buttonCredits = new UIButton(*this, "Credits", 470, 250);
	this->buttonQuit = new UIButton(*this, "Quit", 470, 300);
	
	addComponent(this->buttonStart);
	addComponent(this->buttonCredits);
	addComponent(this->buttonQuit);
}

/**
 * Destructor
 */
WindowMainMenu::~WindowMainMenu() {
	delete this->buttonStart;
	delete this->buttonCredits;
	delete this->buttonQuit;
}

/**
 * Show is called automatically when the window is created.
 */
void WindowMainMenu::show() {
	redraw();
}

/**
 * Redraws everything
 */
void WindowMainMenu::redraw() {
	this->graphics.clear();                            //Clear screen
	this->graphics.drawSprite(IMAGE_BACKGROUND, 0, 0); //Draw sidebar
	this->update();                                    //Draw components
	this->graphics.update();                           //Update screen
}

/**
 * Handles key down events
 * @param keysym - Event information.
 */	
void WindowMainMenu::keyDown(SDL_keysym keysym) {
	switch (keysym.sym) {
		case SDLK_ESCAPE:
			this->close(0);
			break;
			
		case SDLK_RETURN:
			this->close(1);
			break;
			
		default:
			break;
	}
}

/**
 * Handles mouse up events
 * @param button - Event information.
 */	
void WindowMainMenu::mouseUp(SDL_MouseButtonEvent button) {
	
	//Find out if a component was hit
	UIComponent *component = findComponent(button.x, button.y);
	
	if (component == buttonStart) {
		this->sounds.playSound(SOUND_CLICK);
		this->close(1);
	}
	
	// Creates the credits window and deletes it when returning to main menu
	else if (component == buttonCredits) {
		
		Window *window = new WindowCredits(this->graphics, this->sounds);
		
		this->sounds.playSound(SOUND_CLICK);
		window->open();
		
		if (window)
			delete window;
		
		redraw();
	}
	else if (component == buttonQuit) {
		this->sounds.playSound(SOUND_CLICK);
		this->close(0);
	}
}
