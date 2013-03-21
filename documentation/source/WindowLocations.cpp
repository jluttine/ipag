#include "Ai.h"
#include "WindowLocations.h"


/**
 * Constructor
 */
WindowLocations::WindowLocations(Graphics &graphics, Sounds &sounds,
                                 GameEngine &engine)
    : Window(graphics, sounds), gameEngine(engine)
{
	this->scrollMode = false;
	
	//Create UI components
	this->textTip = new UIText(*this, "Choose location for", 300, 20);
	this->textPlayer = new UIText(*this, 460, 20);
	this->textPlayers = new UIText(*this, 865, 100);
	this->butNext = new UIButton(*this, "Skip round", 858, 300);
	this->butQuit = new UIButton(*this, "Back to main menu", 858, 730);

	//Read player names
	Player *player;
	string names;
	
	for (int i = 0; i < gameEngine.getPlayerCount(); i++) {
		player = gameEngine.getPlayer(i);
		
		if (player) {
			names.append(player->getName());
			names.append("\n");
		}
	}
	
	this->textPlayers->setText(names);
	
	addComponent(textPlayer);
	addComponent(textTip);
	addComponent(textPlayers);
	addComponent(butNext);
	addComponent(butQuit);
	
	//Activate first player
	this->playerInTurn = -1;
	nextPlayer();
}

/**
 * Destructor
 */
WindowLocations::~WindowLocations() {
	delete textPlayer;
	delete textTip;
	delete textPlayers;
	delete butNext;
	delete butQuit;
}

/**
 * Step is called automatically by window::open().
 */
void WindowLocations::step(int timestep) {
	this->graphics.clear();                           //Clear screen
	this->gameEngine.draw(this->graphics);            //Draw game view
	this->graphics.drawSprite(IMAGE_SIDEBAR, 824, 0); //Draw sidebar
	this->update();                                   //Draw UI components
	this->drawPlayerColors();                         //Draw colors
	this->graphics.update();                          //Update screen
}

/**
 * Draws player colors on the sidebar. The boxes are not UI components
 * so they have to be redrawn every refresh.
 */
void WindowLocations::drawPlayerColors() {
	Player *player;
	unsigned char r, g, b; //player color
	
	for (int i = 0; i < gameEngine.getPlayerCount(); i++) {
		player = gameEngine.getPlayer(i);
		
		if (player) {
			player->getColor(r, g, b);
			graphics.drawRect(NULL,
			    850, 104 + i * graphics.getLineHeight(),
			    5, 5, r, g, b);
		}
	}
}

/**
 * Handles key down events
 */
void WindowLocations::keyDown(SDL_keysym keysym) {
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
void WindowLocations::mouseMove(SDL_MouseMotionEvent motion) {
	if (this->scrollMode) {
		
		//Workaround for a bug most likely in SDL
		if (motion.xrel > 200 || motion.xrel < -200
		    || motion.yrel > 200 || motion.yrel < -200)
		{
			return;
		}
		
		//Scroll
		graphics.moveCamera(motion.xrel, motion.yrel);
		
		//Odometer
		this->dragDistance += sqrt((float)(motion.xrel * motion.xrel
		                                 + motion.yrel * motion.yrel));
	}
}

/**
 * Handles mouse down events
 */
void WindowLocations::mouseDown(SDL_MouseButtonEvent button) {
	//Activate scroll mode
	if (button.x < 824) {
		this->scrollMode = true;
		SDL_ShowCursor(SDL_DISABLE);
		SDL_WM_GrabInput(SDL_GRAB_ON);
		
		this->dragDistance = 0;
	}
}

/**
 * Handles mouse up events
 */
void WindowLocations::mouseUp(SDL_MouseButtonEvent button) {
	if (button.x > 824  &&  this->scrollMode == false) {
		//Clicking sidebar. Find out if a component was hit.
		UIComponent *component = findComponent(button.x, button.y);

		//'Next player' button
		if (component == butNext) {
			if (playerInTurn >= gameEngine.getPlayerCount())
				this->startGame();
			else
				this->nextPlayer();
		}
		
		//'Back to main menu' button
		else if (component == butQuit) {
			this->close(0);
		}
	} else {
		//Clicking game area
		
		//Convert to world coordinates
		Coordinates* coords = this->graphics.getWorldCoordinates(button.x, button.y);
		
		Player *player;
		Ai *ai = NULL;
		player = gameEngine.getPlayer(playerInTurn);
		
		if (player)
			ai = player->getAI();
		
		//If AI is in turn, disable controls
		if (ai)
			player = NULL;
			
		//Set location
		if (player  &&  this->dragDistance < 5) {
			if (player->setLocation(coords->getX(), coords->getY()) == 0) {
				this->sounds.playSound(SOUND_CLICK);
				nextPlayer();
			} else {
				this->sounds.playSound(SOUND_TICK);
			}
		}
		
		delete coords;
	}

	//Deactivate scroll mode
	if (this->scrollMode) {
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		SDL_ShowCursor(SDL_ENABLE);
		this->scrollMode = false;
	}
}

/**
 * Activates next player. 
 */
void WindowLocations::nextPlayer() {
	Player *player;
	
	playerInTurn++;
	player = gameEngine.getPlayer(playerInTurn);
	
	if (playerInTurn < gameEngine.getPlayerCount()) {
		this->textPlayer->setText(gameEngine.getPlayer(playerInTurn)->getName());
	} else {
		//If this was the last player
		this->textPlayer->clear();
		this->textTip->clear();
		this->butNext->setText("Finish");
	}
	
	//If it's an AI, let it choose it's position
	if (player) {
		Ai *ai;
		ai = player->getAI();
		if (ai) {
			ai->selectStartingLocation();
			nextPlayer();
		}
	}
}

/**
 * Starts game and closes this window.
 */
void WindowLocations::startGame() {
	this->close(1);
}

/**
 * Selects random locations for all players.
 */
void WindowLocations::randomLocations() {
	int i, j;
	
	for (i = 0; i < gameEngine.getPlayerCount(); i++) {
		Player* player = gameEngine.getPlayer(i);
		
		for (j = 0; j < 20 && player->setLocation(rand(), rand()) == -3; j++);
	}
	
	playerInTurn = gameEngine.getPlayerCount();
	this->textPlayer->clear();
}
