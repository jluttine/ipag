#ifndef _WINDOW_PLAYERS_H_
#define _WINDOW_PLAYERS_H_

#include "Window.h"
#include "UIButton.h"
#include "UIText.h"
#include "UITextField.h"
#include "GameEngine.h"

/**
 * WindowPlayers is a window where players are added.
 * @author Tapio Auvinen
 */
 
class WindowPlayers  :  public Window {
public:

	/**
	 * Constructor.
	 * @param &graphics Reference to graphics
	 * @param &sounds Reference to sound engine
	 * @param &engine Reference to game engine
	 */
	WindowPlayers(Graphics &graphics, Sounds &sounds,
	              GameEngine &gameEngine);
	
	/**
	 * Destructor
	 */
	~WindowPlayers();

	/**
	 * Show is called automatically when window is opened.
	 */
	void show();
	
	/**
	 * Handles key down events
	 */
	void keyDown(SDL_keysym keysym);
	
	/**
	 * Handles mouse up events
	 */
	void mouseUp(SDL_MouseButtonEvent button);
	
	
private:

	/**
	 * Redraws everything.
	 */
	void redraw();

	/**
	 * Adds a new player. Parameters are read from UI components.
	 */
	void addPlayer();
	
	/**
	 * Updates player list.
	 */
	void updatePlayers();
	
	/**
	 * Updates the component showing player type.
	 */
	void updatePlayerType();
	
	/**
	 * Starts game and closes this window.
	 */
	void startGame();
	
	GameEngine &gameEngine; //Reference to game engine
	
	//UI components:
	UIText *textTitle;
	UIText *textPlayers;
	
	UIText *textNewPlayer;
	UIText *textNewName;
	UITextField *fieldName;
	UIText *textNewType;
	UIButton *butIncrType;
	UIButton *butDecrType;
	
	UIButton *buttonStart;
	UIButton *butAdd;
	UIButton *butRemoveAll;
	
	int newPlayerType;   //Type of the new player
	int humanNumbering;  //Counter for automatic naming
	int aiNumbering;     //Counter for automatic naming
	int playerCount;     //Counts players
};

#endif //_WINDOW_PLAYERS_H_
