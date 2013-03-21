
#include <stdlib.h>
#include "WindowGameOver.h"

/**
 * Class WindowGameOver.
 * WindowGameOver is a window that shows the ending results of the game.
 * @author Lasse Hakulinen
 */


/**
 * Constructor.
 * @param &graphics - reference to the graphics
 * @param &sounds - reference to the sounds
 * @param &gameEngine - reference to the gameEngine
 */
WindowGameOver::WindowGameOver(Graphics &graphics, Sounds &sounds,
    GameEngine &gameEngine)
    : Window(graphics, sounds), gameEngine(gameEngine) {
	
	int i;
	this->playerCount = this->gameEngine.getPlayerCount();
	
	this->textTitle = new UIText(*this, "GAME OVER", 470, 80);
	this->textPointsTitle = new UIText(*this, "Points", 220, 190);
	this->textRankingsTitle = new UIText(*this, "Total ranking", 620, 190);

	this->textsPlayerPoints = new UIText*[this->playerCount];
	this->textsPlayerRankings = new UIText*[this->playerCount];

	for ( i = 0; i < this->playerCount; i++ ) {
		// Players must be printed in the right order, so allocates
		// memory for them.
		this->textsPlayerPoints[i] = new UIText(*this, "pelaaja ##",
		                                        220, 240 + i * 30);
		                                        
		this->textsPlayerRankings[i] = new UIText(*this, "pelaaja  ##",
		                                          620, 240 + i * 30);
		
		this->addComponent(this->textsPlayerPoints[i]);
		this->addComponent(this->textsPlayerRankings[i]);
	}
	
	this->buttonOk = new UIButton(*this, "   OK   ", 470,
	                              270 + this->playerCount * 30);

	this->addComponent(this->textTitle);
	this->addComponent(this->textPointsTitle);
	this->addComponent(this->textRankingsTitle);
	this->addComponent(this->buttonOk);
	
	this->updateFields();
}

/**
 * Destructs the window.
 */
WindowGameOver::~WindowGameOver() {
	
	int i;
	
	delete this->textTitle;
	delete this->textPointsTitle;
	delete this->textRankingsTitle;

	for (i = 0; i < this->playerCount; i++) {
		delete this->textsPlayerPoints[i];
		delete this->textsPlayerRankings[i];
	}
	
	delete[] this->textsPlayerPoints;
	delete[] this->textsPlayerRankings;
	
	delete this->buttonOk;
}

/**
 * Shows the window.
 */
void WindowGameOver::show() {
	redraw();
}

/**
 * Redraws the window.
 */
void WindowGameOver::redraw() {
	this->graphics.clear();  //Clear screen
	this->graphics.drawSprite(IMAGE_BACKGROUND, 0, 0);
	this->update();          //Draw components
	this->graphics.update(); //Update screen
}

/**
 * Updates text fields.
 */
void WindowGameOver::updateFields() {
	
	Player **pointOrder = new Player*[this->playerCount];
	Player **rankingOrder = new Player*[this->playerCount];
	char text[80];
	int i;
	
	for ( i = 0; i < this->playerCount; i++ ) {
		rankingOrder[i] = pointOrder[i] = this->gameEngine.getPlayer(i);
	}
	
	qsort(pointOrder, this->playerCount, sizeof(Player*),
	      &WindowGameOver::comparePoints);
	      
	qsort(rankingOrder, this->playerCount, sizeof(Player*),
	      &WindowGameOver::compareRankings);
	
	for ( i = 0; i < this->playerCount; i++ ) {
		sprintf(text, "%-15s %d", pointOrder[i]->getName(),
		        pointOrder[i]->getPoints());
		        
		this->textsPlayerPoints[i]->setText(text);
		sprintf(text, "%-15s %d", rankingOrder[i]->getName(),
		        rankingOrder[i]->getRanking());
		        
		this->textsPlayerRankings[i]->setText(text);
	}

}

/**
 * Function for handling mouse button up events.
 * @param button - Event information.
 */
void WindowGameOver::mouseUp(SDL_MouseButtonEvent button) {
	
	
	//Find out if a button was hit
	UIComponent *component = findComponent(button.x, button.y);

	if (component == this->buttonOk) {
		this->sounds.playSound(SOUND_CLICK);
		this->close(1);
	}
}

/**
 * Function for handling key down events.
 * @param keysym - Event information.
 */	
void WindowGameOver::keyDown(SDL_keysym keysym) {

	if (keysym.sym == SDLK_ESCAPE || keysym.sym == SDLK_RETURN) {
		this->close(1);
	}
	
}

/**
 * Compares points between two players. For qsort.
 * @param *player1 - pointer to the first player.
 * @param *player2 - pointer to the second player.
 * @return player2's points - player1's points.
 */
int WindowGameOver::comparePoints(const void *player1, const void *player2){
	
	return (* (const Player**) player2 )->getPoints() -
	       (* (const Player**) player1 )->getPoints();
	
}

/**
 * Compares rankings between two players. For qsort.
 * @param *player1 - pointer to the first player.
 * @param *player2 - pointer to the second player.
 * @return player2's ranking - player1's ranking.
 */
int WindowGameOver::compareRankings(const void *player1,
                                    const void *player2){
	
	return ( *( const Player** )player2 )->getRanking() -
	       ( *( const Player** )player1 )->getRanking();
	
}
