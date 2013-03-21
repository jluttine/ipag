#ifndef _WINDOW_LOCATIONS_H_
#define _WINDOW_LOCATIONS_H_

#include <vector>

#include "Window.h"
#include "GameEngine.h"
#include "UIText.h"
#include "UIButton.h"

/**
 * WindowLocations is a window where players select locations for their
 * cannons. 
 * @author Tapio Auvinen
 */

class WindowLocations  :  public Window {
public:
	/**
	 * Constructor
	 * @param &graphics Reference to graphics
	 * @param &sounds Reference to sound engine
	 * @param &engine Reference to game engine
	 */
	WindowLocations(Graphics &graphics, Sounds &sounds, GameEngine &engine);
	
	/**
	 * Destructor
	 */
	~WindowLocations();
	
	/**
	 * Step is called periodically by window::open().
	 */
	void step(int timestep);
	
	/**
	 * Handles key down events
	 */
	void keyDown(SDL_keysym keysym);
	
	/**
	 * Handles mouse move events
	 */
	void mouseMove(SDL_MouseMotionEvent motion);
	
	/**
	 * Handles mouse down events
	 */
	void mouseDown(SDL_MouseButtonEvent button);
	
	/**
	 * Handles mouse up events
	 */
	void mouseUp(SDL_MouseButtonEvent button);
	

private:
	
	/**
	 * Draws player colors on the sidebar. The boxes are not UI components
	 * so they have to be redrawn on every refresh.
	 */
	void drawPlayerColors();
	
	/**
	 * Activates next player. 
	 */
	void nextPlayer();
	
	/**
	 * Starts game and closes this window.
	 */
	void startGame();
	
	/**
	 * Selects random locations for all players.
	 */
	void randomLocations();
	
	GameEngine &gameEngine; //Reference to game engine
	int playerInTurn;       //Player index
	
	bool scrollMode;    //Tells whether we are scrolling or not
	float dragDistance; //Odometer when scrolling
	
	//UI components:
	UIText *textPlayer;
	UIText *textTip;
	UIText *textPlayers;
	UIButton *butNext;
	UIButton *butQuit;
};

#endif //_WINDOWSTARTINGLOCATIONS_H_
