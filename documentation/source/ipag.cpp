#include <SDL/SDL.h>
#include <iostream>

#include "WindowMainMenu.h"
#include "WindowPlayers.h"
#include "WindowCreateWorld.h"
#include "WindowLocations.h"
#include "WindowShop.h"
#include "WindowGame.h"
#include "WindowGameOver.h"

#include "GameEngine.h"
#include "Graphics.h"
#include "Sounds.h"
#include "World.h"

/**
 * Starter.
 * @author Tapio Auvinen (alustavasti)
 */

int main( int args, char *argv[]) {

	puts("Interplanetary Artillery Game");
	
	//Initialize random number generator
	srand( time(NULL) );
	
	
	//Initialize SDL
	fputs("Initializing SDL\n", stderr);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	atexit(SDL_Quit);
	

	//Initialize Graphics
	fputs("Initializing graphics\n", stderr);
	Graphics *graphics = new Graphics();
	if (!graphics->init(1024, 768, 16)) {
		fputs("Failed to initialize graphics\n", stderr);
		return EXIT_FAILURE;
	}
	
	//Initialize Sound
	fputs("Initializing sound\n", stderr);
	Sounds *sounds = new Sounds(22050, AUDIO_S16, 2, 1024);

	
	Window *window;
	GameEngine *engine;
	
	//Open one window at a time. The return value tells us whether the user
	//wants to quit or open the next window
	while (1) {
		//Main Menu
		window = new WindowMainMenu(*graphics, *sounds);
		if (window == NULL)
			break;
		
		if (window->open() == 0) {
			delete window;
			break;
		} else {
			delete window;
		}
		
		//Game starts. Create game engine.
		engine = new GameEngine();
		
		//Add players
		window = new WindowPlayers(*graphics, *sounds, *engine);
		if (window == NULL)
			break;
		
		if (window->open() == 0) {
			delete window;
			continue;
		} else {
			delete window;
		}
		
		while (1) {
			//Create world
			window = new WindowCreateWorld(*graphics, *sounds, *engine);
			if (window == NULL)
				break;
			
			if (window->open() == 0) {
				delete window;
				break;
			} else {
				delete window;
			}
			
			//Select locations
			window = new WindowLocations(*graphics, *sounds, *engine);
			if (window == NULL)
				break;
			
			if (window->open() == 0) {
				delete window;
				break;
			} else {
				delete window;
			}
			
			//Shop window
			window = new WindowShop(*graphics, *sounds, *engine);
			if (window == NULL)
				break;
			
			if (window->open() == 0) {
				delete window;
				break;
			} else {
				delete window;
			}
			
			//Game window
			window = new WindowGame(*graphics, *sounds, *engine);
			if (window == NULL)
				break;
			
			window->open();
			delete window;
			
			//Score window
			window = new WindowGameOver(*graphics, *sounds, *engine);
			if (window == NULL)
				break;
			
			if (window->open() == 0) {
				delete window;
				break;
			} else {
				delete window;
			}
		}
		
		delete engine;
	}
	
	delete graphics;
	delete sounds;
	
	return EXIT_SUCCESS;
}
