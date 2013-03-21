
#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

class GameEngine;

#include <vector>
#include "World.h"
#include "Player.h"
#include "Projectile.h"
#include "Sounds.h"
#include "images.h"

/**
 * Author: Jaakko Luttinen
 * GameEngine is a class for controlling the actual game simulation and the
 * game phase.
 */
class GameEngine
{

public:

	enum status { GAMEOVER, ACTION, TURN, ENDOFROUND };

	/**
	 * Constructs a new game engine.
	 */
	GameEngine();
	
	/**
	 * Destructs the game engine.
	 */
	~GameEngine();

	/**
	 * Sets the world. Game engine WILL delete the memory allocation of the
	 * world after the game.
	 * @param world The world for the game.
	 */
	void setWorld( World &world );
	
	/**
	 * Returns the world.
	 * @return The world.
	 */
	inline World* getWorld()  { return this->gameWorld; };

	/**
	 * Returns the player of given index or NULL (if invalid index).
	 * @return The player of given index or NULL for invalid index.
	 */
	Player* getPlayer( int index );

	/**
	 * Returns the player in turn.
	 * @return The player in turn.
	 */	
	Player* getPlayerInTurn();
	
	/**
	 * Returns the number of players in the game.
	 * @return The number of players in the game.
	 */
	inline int getPlayerCount()  { return this->players.size(); };
	
	/**
	 * Returns the number of projectile templates.
	 * @return The number of projectile templates.
	 */
	inline int getProjectileTemplateCount() const
		{ return this->projectileTemplates.size(); };
	
	/**
	 * Returns the projectile template of given index or NULL for invalid
	 * index.
	 * @return Projectile template of given index or NULL for invalid index.
	 */
	const Projectile* getProjectileTemplate( int index );
	
	/**
	 * Sets the function to call at the beginning of a turn.
	 * @param callbackFunction The function to call.
	 * @param parameter        The parameter for the function.
	 */	
	void setCallbackFunction( void (*callbackFunction)( void*),
	                          void *parameter );

	/**
	 * Tries to start the game.
	 * @return Return values are following:
	 *         0: start successful.
	 *         -1: game already running (earlier game must end first).
	 *         -2: game does not have enough players.
	 *         -3: world has not been created. 
	 */
	int startGame();
	
	/**
	 * Ends the game - that is sets the status to GAMEOVER and calculates
	 * points and rankings.
	 */
	void endGame();

	/**
	 * Gives the turn to next player. Mainly for game engine's own use. If
	 * used outside, it means skipping the turn.
	 */	
	void nextTurn();
	
	/**
	 * Returns the status of the game.
	 */
	inline status getStatus() const  { return this->gameStatus; };

	/**
	 * Starts action phase which continues until no action flagged body
	 * exists.
	 */
	void startAction();
	
	/**
	 * Works "identically" with startAction, but all the changes are only
	 * simulated - no permanent changes are made. Big difference between these
	 * two functions is, that this function returns only after it has
	 * completed the simulation.
	 */
	void simulate();

	/**
	 * Allows the game engine to work. Depending on the game status the engine
	 * will do a bit different things.
	 * @param timestep Delay since last call (ms).
	 */
	void step(unsigned int timestep);

	/**
	 * Tells whether the given player is in the game.
	 * @param player The player to look for.
	 * @return Whether the given player is in the game.
	 */
	bool hasPlayer(Player &player) const;
	
	/**
	 * Adds the given player in the game. Does not add same player multiple
	 * times. Game engine will clean the player's memory allocation!
	 * @param The player to be add.
	 */
	void addPlayer(Player &player);
	
	/**
	 * Removes the player of given index from the game.
	 * @param index The index of the player to be removed.
	 */
	void removePlayer(int index);
	
	/**
	 * Removes the given player from the game - if it is in it.
	 * @param player The player to remove.
	 */
	void removePlayer(Player &player);
	
	/**
	 * Removes all players from the game.
	 */
	void removeAllPlayers();

	/**
	 * Draws the world into graphics.
	 * @param graphics The graphics object to draw to.
	 */
	void draw(Graphics &graphics);
	
private:

	/**
	 * Length of action step in ms.
	 */
	static const int actionStepLength = 10;
	
	/**
	 * Length of end of round step in ms.
	 */
	static const int endOfRoundStepLength = 20;
	
	/**
	 * Number of end of round steps.
	 */
	static const int endOfRoundStepCount = 70;
	
	/**
	 * Checks game over conditions (that is number of players alive is less
	 * than two). Ends game if conditions are met.
	 */
	void checkGameOverConditions();
	
	/**
	 * Sorts the players by rankings. First is the player with lowest ranking
	 * and last is the player with best ranking.
	 */
	void sortPlayers();
	
	/**
	 * Begins a new turn. Does the necessary routines.
	 */
	void beginTurn();
	
	/**
	 * Does end of round procedures.
	 */
	void endOfRound();

	/**
	 * Projectiles of the game.
	 */	
	vector<Projectile*> projectileTemplates;
	
	/**
	 * The world of the game.
	 */
	World *gameWorld;
	
	/**
	 * The players in the game.
	 */
	vector<Player*> players;
	
	/**
	 * Index of player in turn.
	 */
	int playerInTurn;
	
	/**
	 * Status of the game (gameover, turn, action, endofround).
	 */
	status gameStatus; //Pelin tila (gameover, turn, action, endofround)

	/**
	 * Tells that endofround procedures have been passed and must be done
	 * as soon as possible. For unusual situations.
	 */
	bool endOfRoundPassed;

	/**
	 * Steps taken during the end of round phase.
	 */	
	int endOfRoundStepsTaken;
	
	/**
	 * Time (ms) remainder since last end of round step.
	 */
	int endOfRoundTimeRemainder;

	/**
	 * Because action must be done in constant length steps, we need the
	 * remainder from last step to keep up the exact speed.
	 */
	int actionTimeRemainder;
	
	/**
	 * Function to call when a new turn begins.
	 */ 
	void (*callbackFunction)( void* );
	
	/**
	 * The parameter to the callback function.
	 */
	void *callbackFunctionParameter;
	
};

#endif //_GAMEENGINE_H_
