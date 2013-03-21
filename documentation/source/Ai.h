
#ifndef _AI_H_
#define _AI_H_
	
class Ai;

#include "Player.h"

/**
 * Class Ai.
 * Artifical intelligence for computer players.
 * @author Lasse Hakulinen
 */

class Ai {
	
public:

	/**
	 * Constructor.
	 * @param &player - reference to player whose AI this is.
	 * @param skill - level of skill.
	 */
	Ai(Player &player, int skill = 1);
	
	/**
	 * Destructs the AI
	 */
	~Ai();
	
	/**
	 * Initializes variables for thinking
	 */	 
	void startThinking();
	
	/**
	 * Calculates the best shot for computer player.
	 * Tests one shot and checks if it is better than the current best one.
	 * This function is called numerous times in one turn.
	 * When Ai is done with thinking, it automatically fires a shot.
	 */
	void think();
	
	/**
	 * Does the shopping for computer player.
	 */
	void doShopping();
	
	/**
	 * Selects the starting location for computer player.
	 */
	void selectStartingLocation();
	
private:

	/**
	 * Sets the levels how many simulation shots can be fired in one turn.
	 * @param skill - Ai's level of skill (min = 0, max = 2)
 	*/
	void setThinkingLevels(int skill);

	Player &player;
	
	int thinkStepCount, thinkStepsTaken, randomStepCount, spesifyingSteps;
	
	float bestAngle, bestPower, bestDamage;
	float currentAngle, currentPower;
	int bestWeapon;
	
};

#endif //_AI_H_
