
#ifndef _WINDOW_H_
#define _WINDOW_H_

class Window;

#include <SDL/SDL.h>
#include <vector>
#include "Graphics.h"
#include "UIComponent.h"
#include "soundList.h"
#include "Sounds.h"

using std::vector;

/**
 * Class Window. Base class for all windows.
 * @author Tapio Auvinen
 */

class Window {
public:

	/**
	 * Constructor
	 * @param &graphics Reference to graphics
	 * @param &sounds Reference to sound engine
	 */
	Window(Graphics &graphics, Sounds &sounds);
	
	/**
	 * Destructor
	 */
	virtual ~Window();

	/**
	 * Step is called periodically by Window::open(). Add here stuff that
	 * has to be updated regularly.
	 * @param timestep timestep in milliseconds
	 */
	virtual void step(int timestep) { };
	
	/**
	 * Opens the window. This won't return until the window closes. All input
	 * handling is done by the window.
	 * @return Returns a return value that may reflect users choise.
	 */
	virtual int open();
	
	/**
	 * Closes window.
	 * @param returnValue Value that will be returned by open(). Following
	 *    values are recommended:
	 *    0: back to main menu or quit
	 *    1: next window
	 */
	void close(int returnValue);
	
	/**
	 * Default show action. Updates screen.
	 */
	virtual void show();
	
	/**
	 * Redraws every component on the screen.
	 */
	void update();
	
	/**
	 * Adds a gui component to the window. All components must be added with
	 * this function. They are removed when window closes.
	 * @param *component component to be added
	 */
	void addComponent(UIComponent *component);
	
	/**
	 * Finds out if there is a component at these coordinates. NOTE: If
	 * components are overlapping, the first one found is returned.
	 * @param x location, screen coordinates
	 * @param y location, screen coordinates
	 * @return pointer to the component. NULL if no component was found.
	 */
	UIComponent *findComponent(int x, int y);
	
	/**
	 * Handles key down events.
	 */
	virtual void keyDown(SDL_keysym keysym) { };
	
	/**
	 * Handles key up events.
	 */
	virtual void keyUp(SDL_keysym keysym) { };
	
	/**
	 * Handles mouse move events.
	 */
	virtual void mouseMove(SDL_MouseMotionEvent motion) { };
	
	/**
	 * Handles mouse down events.
	 */
	virtual void mouseDown(SDL_MouseButtonEvent button) { };
	
	/**
	 * Handles mouse up events.
	 */
	virtual void mouseUp(SDL_MouseButtonEvent button) { };
	
	/**
	 * Returns pointer to graphics.
	 * @return poiner to graphics
	 */
	Graphics *getGraphics() { return &graphics; };
	
protected:
	Graphics &graphics; //Refernce to graphics engine
	Sounds &sounds;     //Refernce to sound engine
	bool closed;        //Tells if we are ready to quit
	int returnValue;    //Value to be returned by open()
	
	UIComponent *focus;  //Focused component
	
	/**
	 * Sets the focused component.
	 * @param *component Component to be focused.
	 */
	void setFocus(UIComponent *component);
	
private:

	vector<UIComponent*> components; //All components contained by the window
};

#endif //_WINDOW_H_
