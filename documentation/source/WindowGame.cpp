#include <iostream>

#include "WindowGame.h"
#include "images.h"

using std::string;


/**
 * Constructor.
 */
WindowGame::WindowGame(Graphics &graphics, Sounds &sounds,
                       GameEngine &engine)
    : Window(graphics, sounds), gameEngine(engine)
{
	this->scrollMode = false;
	this->moveMode = false;
	this->parameterIndex = 0;
	this->dragDistance = 0;
	
	//Create UI Components
	this->textPlayer = new UIText(*this, 855, 620);
	
	this->textPlayers = new UIText(*this, 857, 100);
	this->textScore = new UIText(*this, 972, 100);
	
	this->textWeapon = new UIText(*this, 855, 680);
	this->textAmmo = new UIText(*this, 855, 700);
	this->butWeaponNext = new UIButton(*this, ">", 1004, 680);
	this->butWeaponPrev = new UIButton(*this, "<", 840, 680);
	
	this->textParamTitle = new UIText(*this, 855, 720);
	this->textParamValue = new UIText(*this, 855, 740);
	this->butParamNext = new UIButton(*this, ">", 1004, 720);
	this->butParamPrev = new UIButton(*this, "<", 840, 720);
	this->butParamIncr = new UIButton(*this, ">", 1004, 740);
	this->butParamDecr = new UIButton(*this, "<", 840, 740);

	this->butMove = new UIButton(*this, "Move", 855, 650);
	this->butQuit = new UIButton(*this, "End game", 950, 10);
	
	
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
	addComponent(textPlayers);
	addComponent(textScore);
	addComponent(textWeapon);
	addComponent(textAmmo);
	addComponent(butWeaponNext);
	addComponent(butWeaponPrev);
	addComponent(textParamTitle);
	addComponent(textParamValue);
	addComponent(butParamNext);
	addComponent(butParamPrev);
	addComponent(butParamIncr);
	addComponent(butParamDecr);
	addComponent(butMove);
	addComponent(butQuit);
}

WindowGame::~WindowGame() {
	delete textPlayer;
	delete textPlayers;
	delete textScore;
	delete textWeapon;
	delete textAmmo;
	delete butWeaponNext;
	delete butWeaponPrev;
	delete textParamTitle;
	delete textParamValue;
	delete butParamNext;
	delete butParamPrev;
	delete butParamIncr;
	delete butParamDecr;
	delete butMove;
	delete butQuit;
}

/**
 * Opens game window and starts the game. 
 */
int WindowGame::open() {
	
	//Game engine informs game window about changes in it's state with a
	//callback function:
	this->gameEngine.setCallbackFunction(&WindowGame::uiCallback,
	                                     this);
	
	this->gameEngine.startGame();
	
	Window::open();
	
	return 1;
}

/**
 * Game engine calls this when there is significant state in it's state. 
 * @param wnd This is a static callback function so 'this' is not available
 *            and we have to receive it as parameter.
 */
void WindowGame::uiCallback(void *wnd) {
	WindowGame *window = (WindowGame*)wnd;
	
	if (window != NULL) {
		window->parameterIndex = 0;
		window->updateSidebar();
	}
}

/**
 * Ends game and closes this window.
 */
void WindowGame::endGame() {
	this->gameEngine.endGame();
	this->gameEngine.setCallbackFunction(NULL, NULL);
	
	this->close(1);
}

/**
 * Updates player name and weapon info.
 */
void WindowGame::updateSidebar() {
	const Weapon *selectedWeapon = NULL;
	string text;
	Player *player;
	
	//Player names (the order may change)
	string names;
	
	for (int i = 0; i < gameEngine.getPlayerCount(); i++) {
		player = gameEngine.getPlayer(i);
		
		if (player) {
			names.append(player->getName());
			names.append("\n");
		}
	}
	
	this->textPlayers->setText(names);
	
	
	//Player in turn
	player = this->gameEngine.getPlayerInTurn();
	if (player) {
		this->textPlayer->setText(player->getName());
		selectedWeapon = player->getWeaponSelection().getSelectedWeapon();
	}
	
	if (selectedWeapon) {
		//Weapon name
		const Projectile *shot = this->gameEngine.getProjectileTemplate(selectedWeapon->getShot());
		if (shot)
			this->textWeapon->setText( shot->getName() );
		else 
			this->textWeapon->setText("-none-");
		
		//Ammo
		this->textAmmo->setText(selectedWeapon->getShotCount());
		
		//Weapon parameters
		ParameterList parameters = selectedWeapon->getParameters();
		
		parameters.getParameterTitle(this->parameterIndex, text);
		this->textParamTitle->setText(text.c_str());
		
		parameters.getParameterText(this->parameterIndex, text);
		this->textParamValue->setText(text.c_str());
	} else {
		this->textWeapon->setText("-none-");
	}
	
	updateScore();
}

/**
 * Updates score. Energy bars are not UI components so they have to be
 * redrawn every refresh.
 */
void WindowGame::updateScore() {
	Player *player;
	string score;
	char number[10];
	unsigned char r, g, b; //player color
	int energy;            //player energy
	int red, green;        //energy bar color
	
	for (int i = 0; i < gameEngine.getPlayerCount(); i++) {
		player = gameEngine.getPlayer(i);
		
		if (player) {
			//Print score
			sprintf(number, "%d", player->getPoints());
			score.append(number);
			score.append("\n");
		
			//Player color
			player->getColor(r, g, b);
			graphics.drawRect(NULL, 845, 104 + i * 18, 5, 5, r, g, b);
			
			//Energy bar
			energy = (int)(player->getIntegrity() * .10);
			red = (int)(512 - player->getIntegrity() * 5.12);
			green = (int)(player->getIntegrity() * 5.12);

			red = red > 255 ? 255 : red;        //R max = 255
			red = red < 0 ? 0 : red;            //R min = 0
			green = green > 255 ? 255 : green;  //G max = 255
			green = green < 0 ? 0 : green;      //G min = 0

			if (player->getIntegrity() > 0  &&  player->getCannon() != NULL)
				graphics.drawRect(NULL,
				    1014, 100 + i * graphics.getLineHeight() + 10 - energy,
					4, energy + 1, red, green, 0);
			else
				graphics.drawRect(NULL,
				    1014, 100 + i * graphics.getLineHeight(),
					4, 12, 64, 64, 64);
		}
	}
	
	this->textScore->setText(score);
}

/**
 * Step function is called automatically by Window::open().
 */
void WindowGame::step(int timestep) {
	
	this->gameEngine.step(timestep);
	
	this->graphics.clear();                           //Clear screen
	this->gameEngine.draw(this->graphics);            //Draw game view
	this->graphics.drawSprite(IMAGE_SIDEBAR, 824, 0); //Draw sidebar
	this->update();                                //Draw all UI components
	this->updateScore();               //Draw player colors and energy bars

	if (this->gameEngine.getStatus() == GameEngine::GAMEOVER)
		this->graphics.drawText(NULL, "GAME OVER", 400, 370);
	
	this->graphics.update();
}


/**
 * Handles key down events
 */
void WindowGame::keyDown(SDL_keysym keysym) {

	Player *player;
	Ai *ai = NULL;
	
	player = this->gameEngine.getPlayerInTurn();
	if (player)
		ai = player->getAI();
		
	//If AI is in turn, disable controls
	if (ai)
		player = NULL;
	
	if (this->gameEngine.getStatus() == GameEngine::GAMEOVER) {
		this->endGame();
		return;
	}
	
	//Reset mode
	this->moveMode = false;
	
	//= Common controls =
	switch (keysym.sym) {
		case SDLK_ESCAPE:
			//Esc is disabled for safety
			this->sounds.playSound(SOUND_TICK);
			break;
			
		default:
			break;
	}

	
	//= Controls that belong to the player in turn =
	
	if (player == NULL)
		return;
		
	switch (keysym.sym) {
		case SDLK_SPACE:
			player->shoot();
			break;
		
		case SDLK_LEFT:
			if (keysym.mod & KMOD_CTRL)
				player->increaseAimingAngle(-0.05);
			else
				player->increaseAimingAngle(-0.2);
			
			break;
		
		case SDLK_RIGHT:
			if (keysym.mod & KMOD_CTRL)
				player->increaseAimingAngle(0.05);
			else
				player->increaseAimingAngle(0.2);
			
			break;
		
		case SDLK_UP:
			if (keysym.mod & KMOD_CTRL)
				player->increaseAimingPower(0.05);
			else
				player->increaseAimingPower(0.1);
				
			break;
		
		case SDLK_DOWN:
			if (keysym.mod & KMOD_CTRL)
				player->increaseAimingPower(-0.05);
			else
				player->increaseAimingPower(-0.1);
				
			break;
		
		default:
			break;
	}
}

/**
 * Handles mouse move events
 */
void WindowGame::mouseMove(SDL_MouseMotionEvent motion) {
	if (this->scrollMode) {
		
		//SDL sometimes gives faulty values for relative mouse motion. The
		//only way to fix the problem seemes to be filtering the values
		if (motion.xrel > 200 || motion.xrel < -200
		    || motion.yrel > 200 || motion.yrel < -200) {
			return;
		}
		
		//Scroll
		graphics.moveCamera(motion.xrel, motion.yrel);
		
		//Odometer for scrolling
		this->dragDistance += sqrt((float)(motion.xrel * motion.xrel
		                                 + motion.yrel * motion.yrel));
	}
}

/**
 * Handles mouse down events.
 */
void WindowGame::mouseDown(SDL_MouseButtonEvent button) {
	//Activate scroll mode
	if (button.x < 824) {
		this->scrollMode = true;
		SDL_ShowCursor(SDL_DISABLE);
		SDL_WM_GrabInput(SDL_GRAB_ON);
		
		this->dragDistance = 0;
	}
}

/**
 * Handles mouse up events.
 */
void WindowGame::mouseUp(SDL_MouseButtonEvent button) {
	UIComponent *component = NULL;  //Clicked component
	Player *player;
	Ai *ai = NULL;
	
	player = this->gameEngine.getPlayerInTurn();
	if (player)
		ai = player->getAI();
		
	//If AI is in turn, disable controls
	if (ai)
		player = NULL;
	
	//Common controls
	if (button.x > 824  &&  this->scrollMode == false) {
		component = findComponent(button.x, button.y);
		
		//Reset mode to avoid anomalies
		this->moveMode = false;
		
		//'End game' button
		if (component == butQuit) {
			this->sounds.playSound(SOUND_CLICK);
			this->endGame();
		}
	}
	
	//Controls that belong to the player in turn
	if (button.x > 824  &&  this->scrollMode == false  &&  player != NULL) {
		
		//'Select next weapon' button
		if (component == butWeaponNext) {
			this->sounds.playSound(SOUND_CLICK);
			player->selectWeapon(+1);
		}
		
		//'Select previous weapon' button
		else if (component == butWeaponPrev) {
			this->sounds.playSound(SOUND_CLICK);
			player->selectWeapon(-1);
		}
		
		//'Select next parameter' button
		else if (component == butParamNext) {
			this->sounds.playSound(SOUND_CLICK);

			this->parameterIndex++;
			if (this->parameterIndex >= player->getWeaponSelection().getSelectedWeapon()->getParameters().getParameterCount())
				this->parameterIndex = 0;
		}
		
		//'Select previous parameter' button
		else if (component == butParamPrev) {
			this->sounds.playSound(SOUND_CLICK);

			this->parameterIndex--;
			if (this->parameterIndex < 0)
				this->parameterIndex = -1 + player->getWeaponSelection().getSelectedWeapon()->getParameters().getParameterCount();
		}
		
		//'Increase parameter value' button
		else if (component == butParamIncr) {
			this->sounds.playSound(SOUND_CLICK);
			
			player->increaseParameter(this->parameterIndex, +1);
		}
		
		//'Decrease parameter value' button
		else if (component == butParamDecr) {
			this->sounds.playSound(SOUND_CLICK);

			player->increaseParameter(this->parameterIndex, -1);
		}
		
		//'Relocate cannon' button
		else if (component == butMove) {
			this->sounds.playSound(SOUND_CLICK);
			this->moveMode = true;
		}
		
		this->updateSidebar();
	}
	
	//Handle 'select new location'
	if (this->moveMode  &&  button.x < 824
	    &&  dragDistance < 5  &&  player != NULL)
	{
		//Convert to world coordinates
		Coordinates* coords = this->graphics.getWorldCoordinates(button.x,
		                                                         button.y);
		//Set new location
		player->setLocation(coords->getX(), coords->getY());
		this->moveMode = false;
		
		delete coords;
	}

	//Deactivate scroll mode
	if (this->scrollMode) {
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		SDL_ShowCursor(SDL_ENABLE);
		this->scrollMode = false;
	}
}
