#ifndef _WINDOW_CREATEWORLD_H_
#define _WINDOW_CREATEWORLD_H_

#include "Window.h"
#include "GameEngine.h"
#include "UIText.h"
#include "UIButton.h"

/**
 * WindowCreateWorld is a window where user creates the world and ajusts
 * it's parameters.
 *
 * @author Tapio Auvinen
 */

class WindowCreateWorld  :  public Window {
public:

	/**
	 * Constructor
	 * @param &graphics Reference to graphics
	 * @param &sounds Reference to sound engine
	 * @param &engine Reference to game engine
	 */
	WindowCreateWorld(Graphics &graphics, Sounds &sounds,
	                  GameEngine &engine);
	
	/**
	 * Destructor
	 */
	~WindowCreateWorld();
	
	/**
	 * Called priodically by Window::open(). Updates stuff that has to be
	 * updated regularly.
	 * @param timestep timestep in milliseconds
	 */
	void step(int timestep);
	
	/**
	 * Called when window is opened.
	 */
	void show();
	
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
	 * Creates a random world
	 */
	void createWorld();

	
	bool scrollMode; //Tells whether we are scrolling or not
	
	GameEngine &gameEngine; //Reference to game engine
	World *world;           //The new world
	
	int numPlanets;         //Number of planets currently
	
	//UI components:
	UIText *textPlanets;
	UIText *textNumPlanets;
	UIButton *butMorePlanets;
	UIButton *butLessPlanets;
	UIButton *butCreate;
	UIButton *butStart;
	UIButton *butQuit;

};

#endif //_WINDOW_CREATEWORLD_H_
