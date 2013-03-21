
#ifndef _WINDOW_MAINMENU_H_
#define _WINDOW_MAINMENU_H_

#include "Window.h"
#include "UIButton.h"

/**
 * Class WindowMainMenu
 * Window that shows the main menu
 * @author Lasse Hakulinen
 */
 
class WindowMainMenu  :  public Window {
	
public:
	
	/**
	 * Constructor
	 * @param &graphics - reference to the graphics
	 * @param &sounds - reference to the sounds
	 */
	WindowMainMenu(Graphics &graphics, Sounds &sounds);
	
	/**
	 * Destructor
	 */
	~WindowMainMenu();

	/**
	 * Show is called automatically when the window is created.
	 */
	void show();
	
	/**
	 * Handles key down events
	 * @param keysym - Event information.
	 */	
	void keyDown(SDL_keysym keysym);
	
	/**
	 * Handles mouse up events
	 * @param button - Event information.
	 */	
	void mouseUp(SDL_MouseButtonEvent button);
	
private:

	UIButton *buttonStart;
	UIButton *buttonCredits;
	UIButton *buttonQuit;

	/**
	 * Redraws everything
	 */
	void redraw();
};

#endif //_WINDOW_MAINMENU_H_
