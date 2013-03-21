#include "WindowCreateWorld.h"

#define WORLD_W  700
#define WORLD_H  700

//Default number of planets
#define NUM_PLANETS  6
#define MAX_PLANETS  9
#define MIN_PLANETS  2

//Minimum distance between planets:
#define MIN_DISTANCE  40

/**
 * Constructor.
 */
WindowCreateWorld::WindowCreateWorld(Graphics &graphics,
                                     Sounds &sounds,
                                     GameEngine &engine)
    : Window(graphics, sounds), gameEngine(engine)
{
	this->scrollMode = false;

	//Create UI components
	this->textPlanets = new UIText(*this, "Number of planets", 856, 100);
	this->textNumPlanets = new UIText(*this, 876, 120);
	this->butLessPlanets = new UIButton(*this, "<", 856, 120);
	this->butMorePlanets = new UIButton(*this, ">", 896, 120);
	
	this->butCreate = new UIButton(*this, "Create", 858, 140);
	this->butStart = new UIButton(*this, "Finish", 858, 220);
	this->butQuit = new UIButton(*this, "Back to main menu", 858, 730);
	
	addComponent(textPlanets);
	addComponent(butLessPlanets);
	addComponent(butMorePlanets);
	addComponent(textNumPlanets);
	addComponent(butCreate);
	addComponent(butStart);
	addComponent(butQuit);

	//Initialize values
	this->numPlanets = NUM_PLANETS;
	this->textNumPlanets->setText(numPlanets);
}

/**
 * Destructor.
 */
WindowCreateWorld::~WindowCreateWorld() {
	delete textPlanets;
	delete textNumPlanets;
	delete butLessPlanets;
	delete butMorePlanets;

	delete butCreate;
	delete butStart;
	delete butQuit;
}

/**
 * Called when window is first opened.
 */
void WindowCreateWorld::show() {
	this->createWorld();
}

/**
 * Called automatically by Window::open().
 */
void WindowCreateWorld::step(int timestep) {
	
	this->gameEngine.step(timestep);
	
	this->graphics.clear();                           //Clear screen
	this->gameEngine.draw(this->graphics);            //Draw game view
	this->graphics.drawSprite(IMAGE_SIDEBAR, 824, 0); //Draw sidebar
	this->update();                                   //Draw UI components
	this->graphics.update();                          //Update screen
}

/**
 * Handles key down events
 */
void WindowCreateWorld::keyDown(SDL_keysym keysym) {
	switch (keysym.sym) {
		case SDLK_ESCAPE:
			this->close(0);
			break;
			
		default:
			break;
	}
}

/**
 * Handles mouse move events
 */
void WindowCreateWorld::mouseMove(SDL_MouseMotionEvent motion) {
	if (this->scrollMode) {
		//Prevent mouse jumping (workaround for a bug most likely in SDL)
		if (motion.xrel > 200 || motion.xrel < -200
		    || motion.yrel > 200 || motion.yrel < -200)
		{
			return;
		}
		
		//Scroll
		graphics.moveCamera(motion.xrel, motion.yrel);
	}
}

/**
 * Handles mouse down events
 */
void WindowCreateWorld::mouseDown(SDL_MouseButtonEvent button) {
	//Activate scroll mode
	if (button.x < 824) {
		this->scrollMode = true;
		SDL_ShowCursor(SDL_DISABLE);
		SDL_WM_GrabInput(SDL_GRAB_ON);
	}
}

/**
 * Handles mouse up events
 */
void WindowCreateWorld::mouseUp(SDL_MouseButtonEvent button) {
	
	//Find out if a button was hit
	if (button.x > 824  &&  this->scrollMode == false) {
		UIComponent *component = findComponent(button.x, button.y);
	
		//Increase number of planets
		if (component == butMorePlanets) {
			if (this->numPlanets < MAX_PLANETS) {
				this->numPlanets++;
				this->sounds.playSound(SOUND_CLICK);
			} else {
				this->sounds.playSound(SOUND_TICK);
			}
			
			this->textNumPlanets->setText(numPlanets);
		}
		
		//Decrease number of planets
		else if (component == butLessPlanets) {
			if (this->numPlanets > MIN_PLANETS) {
				this->numPlanets--;
				this->sounds.playSound(SOUND_CLICK);
			} else {
				this->sounds.playSound(SOUND_TICK);
			}
			
			this->textNumPlanets->setText(numPlanets);
		}
		
		//'Create world' button
		else if (component == butCreate) {
			this->sounds.playSound(SOUND_CLICK);
			createWorld();
		}
		
		//'Finish' button
		else if (component == butStart) {
			this->sounds.playSound(SOUND_CLICK);
			this->close(1);
		}
		
		//'Back to main menu' button
		else if (component == butQuit) {
			this->close(0);
		}
	}

	//Deactivate scroll mode
	if (this->scrollMode) {
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		SDL_ShowCursor(SDL_ENABLE);
		this->scrollMode = false;
	}
}

/**
 * Creates a random world
 */
void WindowCreateWorld::createWorld() {
	BodyPlanet *planet;     //The new planet
	BodyPlanet::ESize size; //Size
	BodyPlanet::EType type; //Type
	float x, y;             //Position
	float angularVelocity;
	
	BodyPlanet *nearest; //Nearest existing
	float dist;          //Distance to the nearest
	
	int i;
	int planets = 0;
	
	
	//Create world. It will be deleted by GameEngine.
	this->world = new World( WORLD_W, WORLD_H, 0.2, this->sounds);
	this->gameEngine.setWorld(*this->world);
	this->graphics.setCoordinateSystem(this->world->getCoordinateSystem());
	
	this->graphics.createStarfield(); //Make the starfield a bit different
	
	
	//Create planets
	//Try again max 100 times
	for (i = 0; i < 100; i++)  {
		//Position
		x = (float)rand() / RAND_MAX * WORLD_W;
		y = (float)rand() / RAND_MAX * WORLD_H;
		
		//Angular velocity
		angularVelocity = .35 + (float)rand() / RAND_MAX * .70;
		if (rand() % 2)
			angularVelocity *= -1;  //Direction of rotation
		
		//Size
		switch (rand() % 3) {
			case 0:
				size = BodyPlanet::SMALL;
				break;
				
			case 1:
				size = BodyPlanet::MEDIUM;
				break;
			
			case 2:
				size = BodyPlanet::LARGE;
				break;
			
			default:
				//This never happens, but it keeps the compiler happy
				size = BodyPlanet::MEDIUM;
				break;
		}
		
		//Type
		switch (rand() % 4) {
			case 0:
				type = BodyPlanet::ALIEN;
				break;
				
			case 1:
				type = BodyPlanet::EARTH;
				break;
			
			case 2:
				type = BodyPlanet::MARS;
				break;
			
			case 3:
				type = BodyPlanet::ICE;
				break;
			
			default:
				//This never happens, but it keeps the compiler happy
				type = BodyPlanet::MARS;
				break;
		}
		
		//Create the planet
		planet = new BodyPlanet(*this->world, x, y, size,
		                        type, angularVelocity);
		
		//Find the nearest existing planet
		nearest = (BodyPlanet *)this->world->getNearestPlanet(x, y);
		
		//If it's too close (maybe overlapping), we destroy the newly
		//created planet and try again later
		if (nearest != NULL) {
			dist = nearest->getLocation().getDistance(x, y);
		
			if (dist > planet->getRadius()
			    + nearest->getRadius() + MIN_DISTANCE)
			{
				this->world->addBody(*planet);
				planets++;
			} else {
				delete planet;
			}
		} else {
			this->world->addBody(*planet);
			planets++;
		}
		
		//Do we have enough planets?
		if (planets >= this->numPlanets)
			break;
		
		//World will destroy the planets eventually
	}
}
