#ifndef _WINDOW_GAME_H_
#define _WINDOW_GAME_H_

#include "Window.h"
#include "GameEngine.h"
#include "UIText.h"
#include "UIButton.h"

/**
 * WindowGame is the actual game window.
 * @author Tapio Auvinen
 */

class WindowGame  :  public Window {
public:
	/**
	 * Constructor.
	 * @param &graphics Reference to graphics
	 * @param &sounds Reference to sound engine
	 * @param &engine Reference to game engine
	 */
	WindowGame(Graphics &graphics, Sounds &sounds, GameEngine &engine);
	
	/**
	 * Destructor
	 */
	~WindowGame();

	/**
	 * Opens game window and starts the game.
	 */
	int open();

	/**
	 * Step function is called periodically by Window::open(). It makes the
	 * game move.
	 * @param timestep timestep in milliseconds
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
	 * Handles mouse down events.
	 */
	void mouseDown(SDL_MouseButtonEvent button);
	
	/**
	 * Handles mouse up events.
	 */
	void mouseUp(SDL_MouseButtonEvent button);
	
	
private:

	/**
	 * Refreshes UI. Game engine calls this when there is a significant
	 * change in it's state. 
	 * @param wnd Pointer to game window. This is a static callback
	 *            function so 'this' is not available and we have to
	 *            receive it as parameter.
	 */
	static void uiCallback(void *wnd);

	/**
	 * Ends the game and closes this window.
	 */
	void endGame();
	
	/**
	 * Updates player name and weapon info.
	 */
	void updateSidebar();
	
	/**
	 * Updates score. Energy bars are not UI components so they have to be
	 * redrawn every refresh.
	 */
	void updateScore();
	

	GameEngine &gameEngine; //Reference to game engine
	bool scrollMode;      //Tells whether we are scrolling or not
	bool moveMode;       //'select new location' mode
	float dragDistance;  //Odometer for scrolling

	int parameterIndex;  //Currently selected weapon parameter

	
	//UI components:
	UIText *textPlayer;  //Player in turn
	
	UIText *textPlayers; //All players and their
	UIText *textScore;   //score
	
	//Weapon:
	UIText *textWeapon;
	UIText *textAmmo;
	UIButton *butWeaponNext;
	UIButton *butWeaponPrev;
	
	//Weapon parameters:
	UIText *textParamTitle;
	UIText *textParamValue;
	UIButton *butParamNext; //Select parameter
	UIButton *butParamPrev;
	UIButton *butParamIncr; //Adjust parameter value
	UIButton *butParamDecr;
	
	UIButton *butMove;  //Select new location
	UIButton *butQuit;
};

#endif //_WINDOW_GAME_H_
