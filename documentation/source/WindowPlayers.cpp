#include "WindowPlayers.h"

#define MIN_PLAYERS  2
#define MAX_PLAYERS  8

//NOTE: If you increase the maximum number of players, you have to add
//more colors.

 
//Player colors:
unsigned char colors[][3] = {
	{ 255,   0,   0 },
	{   0, 255,   0 },
	{   0, 255, 255 },
	{ 255, 255,   0 },
	{ 191,  63, 255 },
	{ 127, 127, 255 },
	{ 255, 255, 191 },
	{ 255, 191, 255 }
};

/**
 * Constructor.
 */
WindowPlayers::WindowPlayers(Graphics &graphics, Sounds &sounds,
                             GameEngine &gameEngine)
    : Window(graphics, sounds), gameEngine(gameEngine)
{
	this->newPlayerType = 0;
	this->humanNumbering = 1;
	this->aiNumbering = 1;
	this->playerCount = 0;
	
	//Create UI components
	this->textTitle = new UIText(*this, "Players:", 350, 140);
	this->textPlayers = new UIText(*this, 372, 160);
	
	this->buttonStart = new UIButton(*this, "Start game", 800, 660);
	
	this->textNewPlayer = new UIText(*this, "New player", 350, 590);
	this->textNewName = new UIText(*this, "Name:", 360, 620);
	this->fieldName = new UITextField(*this, 20, 408, 620);
	
	this->textNewType = new UIText(*this, 380, 640);
	this->butDecrType = new UIButton(*this, "<", 360, 640);
	this->butIncrType = new UIButton(*this, ">", 508, 640);
	this->butAdd = new UIButton(*this, "Add player", 360, 660);
	this->butRemoveAll = new UIButton(*this, "Remove all", 360, 700);
	
	this->setFocus(fieldName);
	updatePlayerType();
	
	addComponent(textTitle);
	addComponent(textPlayers);
	addComponent(buttonStart);
	addComponent(textNewPlayer);
	addComponent(textNewName);
	addComponent(fieldName);
	addComponent(textNewType);
	addComponent(butDecrType);
	addComponent(butIncrType);
	addComponent(butAdd);
	addComponent(butRemoveAll);
}

/**
 * Destructor
 */
WindowPlayers::~WindowPlayers() {
	delete textTitle;
	delete textPlayers;
	delete buttonStart;
	delete textNewPlayer;
	delete textNewName;
	delete fieldName;
	delete textNewType;
	delete butDecrType;
	delete butIncrType;
	delete butAdd;
	delete butRemoveAll;
}

/**
 * Show is called automatically when window is opened.
 */
void WindowPlayers::show() {
	redraw();
}

/**
 * Redraws everything.
 */
void WindowPlayers::redraw() {
	this->graphics.clear();                            //Clear screen
	this->graphics.drawSprite(IMAGE_BACKGROUND, 0, 0); //Draw background
	this->update();                                    //Draw components
	
	//Draw player colors
	Player *player;
	unsigned char r, g, b;  //player color
	
	for (int i = 0; i < gameEngine.getPlayerCount(); i++) {
		player = gameEngine.getPlayer(i);
		
		if (player) {
			player->getColor(r, g, b);
			graphics.drawRect(NULL, 360, 164 + i * 18, 5, 5, r, g, b);
		}
	}
	
	this->graphics.update();  //Update screen
}

/**
 * Handles key down events
 */
void WindowPlayers::keyDown(SDL_keysym keysym) {
	//Send events to focused component
	if (this->focus != NULL) {
		this->focus->keyDown(keysym);
	}
	
	switch (keysym.sym) {
		case SDLK_ESCAPE:
			this->close(0);
			break;
			
		case SDLK_RETURN:
			addPlayer();
			break;
		
		default:
			break;
	}
	
	//Update screen
	redraw();
}

/**
 * Handles mouse up events
 */
void WindowPlayers::mouseUp(SDL_MouseButtonEvent button) {

	//Find out if a button was hit
	UIComponent *component = findComponent(button.x, button.y);
	
	//'Start game' button
	if (component == buttonStart) {
		this->sounds.playSound(SOUND_CLICK);
		this->startGame();
	}
	
	//'Add player' button
	else if (component == butAdd) {
		addPlayer();
	}
	
	//Player type (increase)
	else if (component == butIncrType) {
		newPlayerType++;
		if (newPlayerType > 3)
			newPlayerType = 0;
	
		this->sounds.playSound(SOUND_CLICK);

		updatePlayerType();
	}
	
	//Player type (decrease)
	else if (component == butDecrType) {
		newPlayerType--;
		if (newPlayerType < 0)
			newPlayerType = 3;
			
		this->sounds.playSound(SOUND_CLICK);
		
		updatePlayerType();
	}
	
	//'Remove all' button
	else if (component == butRemoveAll) {
		gameEngine.removeAllPlayers();
		this->humanNumbering = 1;
		this->aiNumbering = 1;
		this->playerCount = 0;

		this->sounds.playSound(SOUND_TICK);

		updatePlayers();
	}
	
	redraw();
}

/**
 * Adds a new player. Parameters are read from UI components.
 */
void WindowPlayers::addPlayer() {
	Player *player;
	char *name = fieldName->getText();
	
	//Limit number of players
	if (gameEngine.getPlayerCount() >= MAX_PLAYERS) {
		this->sounds.playSound(SOUND_TICK);
		return;
	} else {
		this->sounds.playSound(SOUND_CLICK);
	}

	
	//Default names
	if (name == NULL) {
		name = new char[20];
		
		if (newPlayerType > 0) {
			sprintf(name, "AI %d", aiNumbering);
			aiNumbering++;
			
		} else {
			sprintf(name, "Player %d", humanNumbering);
			humanNumbering++;
		}
	}
	
	//Create player
	player = new Player(name, gameEngine);
	player->setColor(colors[playerCount][0],
	                 colors[playerCount][1],
	                 colors[playerCount][2]);
	playerCount++;

	//Set AI
	switch (newPlayerType) {
		case 1:
			//Stupid computer
			player->setAI(*(new Ai(*player, 0)));
			break;
		
		case 2:
			//Normal computer
			player->setAI(*(new Ai(*player, 1)));
			break;
		
		case 3:
			//Clever computer
			player->setAI(*(new Ai(*player, 2)));
			break;
	}
	
	gameEngine.addPlayer(*player);
	
	delete [] name;
	
	updatePlayers();
	fieldName->clear();
}

/**
 * Updates player list.
 */
void WindowPlayers::updatePlayers() {
	Player *player;
	string text;
	
	for (int i = 0; i < gameEngine.getPlayerCount(); i++) {
		player = gameEngine.getPlayer(i);
		
		if (player) {
			text.append(player->getName());
			text.append("\n");
		}
	}
	
	this->textPlayers->setText(text);
}

/**
 * Updates the component showing player type.
 */
void WindowPlayers::updatePlayerType() {
	switch (newPlayerType) {
		case 0:
			this->textNewType->setText("Human");
			break;
		
		case 1:
			this->textNewType->setText("Stupid computer");
			break;
		
		case 2:
			this->textNewType->setText("Normal computer");
			break;
		
		case 3:
			this->textNewType->setText("Clever computer");
			break;
	}
}

/**
 * Starts game and closes this window.
 */
void WindowPlayers::startGame() {
	if (gameEngine.getPlayerCount() < MIN_PLAYERS)
		return;
	
	this->close(1);
}
