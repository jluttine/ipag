
#ifndef _WINDOWGAMEOVER_H_
#define _WINDOWGAMEOVER_H_

#include "Window.h"
#include "UIText.h"
#include "UIButton.h"
#include "GameEngine.h"

/**
 * Class WindowGameOver.
 * WindowGameOver is a window that shows the ending results of the game
 * and the current total ranking points.
 * @author Lasse Hakulinen
 */
class WindowGameOver  :  public Window {
	
public:

	/**
	 * Constructor.
	 * @param &graphics - reference to the graphics
	 * @param &sounds - reference to the sounds
	 * @param &gameEngine - reference to the gameEngine
	 */
	WindowGameOver(Graphics &graphics, Sounds &sounds,
	               GameEngine &gameEngine);
	
	/**
	 * Destructs the window.
	 */
	~WindowGameOver();
	
	/**
	 * Shows the window.
	 */
	void show();
	
	/**
	 * Redraws the window.
	 */
	void redraw();
	
	/**
	 * Nothing to do in this function.
	 */
	virtual void step(int timestep) {  };

	/**
	 * Function for handling key down events.
	 * @param keysym - Event information.
	 */	
	void keyDown(SDL_keysym keysym);
	
	/**
	 * Function for handling mouse button up events.
	 * @param button - Event information.
	 */
	void mouseUp(SDL_MouseButtonEvent button);
	
private:

	/**
	 * Updates text fields.
	 */
	void updateFields();
	
	/**
	 * Compares points between two players. For qsort.
	 * @param *player1 - pointer to the first player.
	 * @param *player2 - pointer to the second player.
	 * @return player2's points - player1's points.
	 */
	static int comparePoints(const void *player1, const void *player2);
	
	/**
	 * Compares rankings between two players. For qsort.
	 * @param *player1 - pointer to the first player.
	 * @param *player2 - pointer to the second player.
	 * @return player2's ranking - player1's ranking.
	 */
	static int compareRankings(const void *player1, const void *player2);

	/**
	 * Game engine.
	 */
	GameEngine &gameEngine;

	/**
	 * Window title.
	 */
	UIText *textTitle;
	
	/**
	 * Title for point list.
	 */
	UIText *textPointsTitle;
	
	/**
	 * Title for ranking list.
	 */
	UIText *textRankingsTitle;
	
	/**
	 * Number of players.
	 */
	int playerCount;
	
	/**
	 * Player point texts.
	 */
	UIText **textsPlayerPoints;
	
	/**
	 * Player ranking texts.
	 */
	UIText **textsPlayerRankings;
	
	/**
	 * OK button.
	 */
	UIButton *buttonOk;
	
};

#endif //_WINDOWGAMEOVER_H_
