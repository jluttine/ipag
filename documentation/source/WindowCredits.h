#ifndef _WINDOWCREDITS_H_
#define _WINDOWCREDITS_H_

#include "Window.h"
#include "UIButton.h"
#include "UIText.h"


/**
 * Class WindowCredits.
 * Shows the developers of the game.
 * @author Lasse Hakulinen
 */

class WindowCredits : public Window {
	
public:

	/**
	 * @param &graphics - reference to the graphics
	 * @param &sounds - reference to the sounds
	 */
	WindowCredits(Graphics &graphics, Sounds &sounds);
	
	/**
	 * Destructor
	 */
	~WindowCredits();

	/**
	 * Shows the windowCredits
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
	 * @param keysym - key that is pressed
	 */
	virtual void keyDown(SDL_keysym keysym);
	
	/**
	 * Handles mouse up events
	 * @param button - button that is pressed
	 */
	virtual void mouseUp(SDL_MouseButtonEvent button);
	
private:
			
	
	//UI components
	UIText *textTitle;
	UIText *textDevelopers, *textSpecial, *textMade;

	UIButton *buttonBack;

};

#endif //_WINDOWCREDITS_H_
