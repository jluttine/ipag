#ifndef _UI_COMPONENT_H_
#define _UI_COMPONENT_H_

class UIComponent;

#include <SDL/SDL.h>
#include "Window.h"

/**
 * UIComponent is base class for all UI components.
 * @author Tapio Auvinen
 */
 
class UIComponent {
public:
	/**
	 * Constructor.
	 * @param parent Parent window
	 * @param x Location of the upper-left corner
	 * @param y Location of the upper-left corner
	 */
	UIComponent(Window &parent, int x, int y);
	
	/**
	 * Destructor
	 */
	virtual ~UIComponent();
	
	/**
	 * Draws the component on screen
	 * @param &graphics Reference to graphics
	 */
	virtual void draw(Graphics &graphics);

	/**
	 * Handles key down events
	 */
	virtual void keyDown(SDL_keysym keysym) { };
	
	/**
	 * Handles key up events
	 */
	virtual void keyUp(SDL_keysym keysym) { };
	
	/**
	 * Handles mouse move events
	 */
	virtual void mouseMove(SDL_MouseMotionEvent motion) { };
	
	/**
	 * Handles mouse down events
	 */
	virtual void mouseDown(SDL_MouseButtonEvent button) { };
	
	/**
	 * Handles mouse up events
	 */
	virtual void mouseUp(SDL_MouseButtonEvent button) { };
	
	/**
	 * Returns x-position of the upper-left corner
	 * @return x position of the upper-left corner
	 */
	int getX() { return this->x; };
	
	/**
	 * Returns y-position of the upper-left corner.
	 * @return y-position of the upper-left corner
	 */
	int getY() { return this->y; };

	/**
	 * Returns width of the component.
	 * @return width in pixels
	 */
	int getWidth() { return this->width; };
	
	/**
	 * Returns height of the component.
	 * @return height in pixels
	 */
	int getHeight() { return this->height; };

	/**
	 * Relocates the component.
	 * @param x new location of upper-left corner
	 * @param y new location of upper-left corner
	 */
	void setPosition(int x, int y);

protected:
	Window &parentWindow;
	SDL_Surface *image;  //Image of the coponent
	
	//Position and size
	int x;
	int y;
	unsigned short int width;
	unsigned short int height;
};

#endif
