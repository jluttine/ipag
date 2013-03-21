#include "Window.h"

/**
 * Constructor
 */
Window::Window(Graphics &graphics, Sounds &sounds)
	: graphics(graphics), sounds(sounds)
{
	this->focus = NULL;
	this->closed = false;
}

/**
 * Destructor
 */
Window::~Window() {
}

/**
 * Opens the window. This won't return until the window closes. All input
 * handling is done by the window.
 * @return Returns a return value that may reflect users choise.
 */
int Window::open() {
	this->show();
	
	SDL_Event event;
	Uint32 currentTime, lastTime, timestep;
	
	lastTime = SDL_GetTicks();
	
	while (!this->closed) {
		
		//Calculate timestep
		currentTime = SDL_GetTicks();
		timestep =  currentTime - lastTime;
		lastTime = currentTime;
		
		if (timestep > 0) {
			this->step(timestep);
		}

		//Handle events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					this->close(0);
					break;
				
				case SDL_KEYDOWN:
					this->keyDown(event.key.keysym);
					break;
				
				case SDL_KEYUP:
					this->keyUp(event.key.keysym);
					break;
				
				case SDL_MOUSEMOTION:
					this->mouseMove(event.motion);
					break;
					
				case SDL_MOUSEBUTTONDOWN:
					this->mouseDown(event.button);
					break;
				
				case SDL_MOUSEBUTTONUP:
					this->mouseUp(event.button);
					break;
				
				default:
					break;
			}
		}
	}
	
	return returnValue;
}

/**
 * Default show action. Updates screen. Overwrite if necessary.
 */
void Window::show() {
	this->graphics.clear();  //Clear screen
	this->update();          //Draw compoents
	this->graphics.update(); //Update screen
}

/**
 * Adds a gui component to the window. All components must be added with
 * this function.
 */
void Window::addComponent(UIComponent *component) {
	this->components.push_back(component);
}

/**
 * Finds out if there is a component at these coordinates. NOTE: If
 * components are overlapping, the first one found is returned.
 * @param x location, screen coordinates
 * @param y location, screen coordinates
 * @return pointer to the component. NULL if no component was found.
 */
UIComponent *Window::findComponent(int x, int y) {
	
	//Compare coordinates
	for (unsigned int i = 0; i < this->components.size(); i++) {
		if (x > components[i]->getX()
		    && x < components[i]->getX() + components[i]->getWidth()
			&& y > components[i]->getY()
			&& y < components[i]->getY() + components[i]->getHeight())
		{
			return components[i];
		}
	}
	
	return NULL;
}

/**
 * Sets focused component.
 */
void Window::setFocus(UIComponent *component) {
	this->focus = component;
}

/**
 * Redraws every component on the screen.
 */
void Window::update() {
	for (unsigned int i = 0; i < this->components.size(); i++) {
		components[i]->draw(graphics);
	}
}

/**
 * Closes window.
 * @param returnValue Value that will be returned by open().
 */
void Window::close(int returnValue) {
	//Release mouse (in case you quit while scrolling)
	SDL_WM_GrabInput(SDL_GRAB_OFF);
	SDL_ShowCursor(SDL_ENABLE);

	this->closed = true;
	this->returnValue = returnValue;
}
