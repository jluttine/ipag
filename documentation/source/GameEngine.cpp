
#include <iostream>
#include <math.h>
#include "ProjectileSplitting.h"
#include "ProjectileSeeking.h"
#include "ProjectileBouncing.h"
#include "ProjectileSustaining.h"
#include "ProjectileShooting.h"
#include "ProjectileLaser.h"
#include "ProjectileShootingBouncing.h"
#include "ProjectileSeekingBouncing.h"
#include "ProjectileSplittingBouncing.h"
#include "GameEngine.h"
#include "BodyPlanet.h"
#include "Ai.h"

/**
 * Constructs a new game engine.
 */
GameEngine::GameEngine() {

	this->callbackFunction = NULL;
	this->callbackFunctionParameter = NULL;
	this->gameWorld = NULL;
	this->playerInTurn = 0;
	this->gameStatus = GAMEOVER;
	this->endOfRoundPassed = false;
	this->endOfRoundStepsTaken = 0;
	this->endOfRoundTimeRemainder = 0;
	this->actionTimeRemainder = 0;

	//Projectile templates:
	//Two first parameter rows are the basic stuff of projectile (except
	//Sustaining projectiles). Third and fourth parameter rows are subclass
	//parameters.
	this->projectileTemplates.push_back( new Projectile(
		"Grenade", "Basic grenade.", 100, IMAGE_GRENADE,
		SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 15, 40 ) );
	this->projectileTemplates.push_back( new ProjectileLaser(
		"Laser", "Basic laser.", 200, IMAGE_LASER,
		SOUND_LASER, BodyExplosion::LASER, 10, 20, 20, 0.9 ) );
	this->projectileTemplates.push_back( new ProjectileBouncing(
		"BounZ", "Bouncing shot.", 500, IMAGE_BOUNCING,
		SOUND_GRENADE, BodyExplosion::SMALL_NUCLEAR, 10, 1, 30, 30,
		5, 0.45 ) );
	this->projectileTemplates.push_back( new ProjectileSeeking(
		"Missile", "Seeking missile.", 500, IMAGE_MISSILE,
		SOUND_ROCKET, BodyExplosion::BIG_GAS, 10, 1, 20, 30,
		100, 0.0007 ) );
	this->projectileTemplates.push_back( new ProjectileSeekingBouncing(
		"Frog", "Seeking and bouncing shot.", 1000, IMAGE_FROG,
		SOUND_GRENADE, BodyExplosion::SMALL_NUCLEAR, 10, 1, 25, 30,
		500, 0.0005, 6, 0.6 ) );
	this->projectileTemplates.push_back( new ProjectileSplitting(
		"Splitting grenade", "Splits into four grenades.", 1000, IMAGE_GRENADE,
		SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 15, 30,
		*this->projectileTemplates[0], 4, 1.57, 500, 0.1 ) );
	this->projectileTemplates.push_back( new ProjectileSplittingBouncing(
		"Splitting bounZ", "Splits into four bouncing shots.", 1000,
		IMAGE_BOUNCING,	SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 15, 30,
		*this->projectileTemplates[2], 4, 1.57, 300, 0.15,
		ProjectileBouncing::maximumBounces, 1.0 ) );
	this->projectileTemplates.push_back( new ProjectileSplitting(
		"Splitting missile", "Splits into three missiles.", 3000, IMAGE_MISSILE,
		SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 15, 30,
		*this->projectileTemplates[3], 3, 1.57, 500, 0.1 ) );
	this->projectileTemplates.push_back( new ProjectileSplittingBouncing(
		"Frog squad", "Splits into three frogs.", 3000, IMAGE_FROG,
		SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 15, 30,
		*this->projectileTemplates[4], 3, 1.57, 500, 0.05,
		ProjectileBouncing::maximumBounces, 0.6 ) );
	this->projectileTemplates.push_back( new ProjectileSustaining(
		"Grenade fire", "Sustained grenade fire.", 2000,
		*this->projectileTemplates[0], 10, 100, 0.1 ) );
	this->projectileTemplates.push_back( new ProjectileSustaining(
		"Laser fire", "Sustained laser fire.", 3000,
		*this->projectileTemplates[1], 10, 150, 0.1 ) );
	this->projectileTemplates.push_back( new Projectile(
		"Nuke", "Extremely effective bomb.", 5000, IMAGE_NUKE,
		SOUND_ROCKET, BodyExplosion::BIG_NUCLEAR, 10, 1, 70, 50 ) );
	this->projectileTemplates.push_back( new ProjectileShooting(
		"Grenade probe", "Grenade shooting probe.", 3000, IMAGE_PROBE,
		SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 10, 30,
		*this->projectileTemplates[0], 10, 400, 0.4 ) );
	this->projectileTemplates.push_back( new ProjectileShooting(
		"Laser probe", "Laser shooting probe.", 6000, IMAGE_PROBE,
		SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 10, 30,
		*this->projectileTemplates[1], 6, 400, 0.9 ) );
	this->projectileTemplates.push_back( new ProjectileShooting(
		"Missile probe", "Missile shooting probe.", 6000, IMAGE_PROBE,
		SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 10, 30, 30,
		*this->projectileTemplates[3], 6, 400, 0.5 ) );
	this->projectileTemplates.push_back( new ProjectileSplitting(
		"Fleet of terror", "Splits into three laser probes.", 12000,
		IMAGE_PROBE, SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 10, 30, 30,
		*this->projectileTemplates[13], 3, 5.7, 500, 0.15 ) );
	this->projectileTemplates.push_back( new ProjectileShootingBouncing(
		"Angry toad", "Bouncing and missile shooting probe.", 15000,
		IMAGE_PROBE, SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 10, 30,
		*this->projectileTemplates[3], 6, 1000, 0.5,
		ProjectileBouncing::maximumBounces, 0.8 ) );
	this->projectileTemplates.push_back( new ProjectileShootingBouncing(
		"Toad queen", "Bouncing and frog squad shooting probe.", 15000,
		IMAGE_PROBE, SOUND_GRENADE, BodyExplosion::SMALL_GAS, 10, 1, 10, 30,
		*this->projectileTemplates[8], 4, 1600, 0.25,
		ProjectileBouncing::maximumBounces, 0.8 ) );

}

/**
 * Destructs the game engine.
 */
GameEngine::~GameEngine()
{
	
	this->gameStatus = GAMEOVER;

	//Remove world.
	if ( this->gameWorld ) {
		
		delete this->gameWorld;
		this->gameWorld = NULL;
		
	}
	
	//Remove players.
	this->removeAllPlayers();

	//Clean projectiles.
	for (unsigned int i = 0; i < this->projectileTemplates.size(); i++ )
		delete this->projectileTemplates[i];
	this->projectileTemplates.clear();

}

/**
 * Sets the world. Game engine WILL delete the memory allocation of the
 * world after the game.
 * @param world The world for the game.
 */
void GameEngine::setWorld( World &world )
{
	
	if ( this->gameWorld )
		delete this->gameWorld;
		
	this->gameWorld = &world;
	
}

/**
 * Returns the player of given index or NULL (if invalid index).
 * @return The player of given index or NULL for invalid index.
 */
Player* GameEngine::getPlayer( int index )
{
	
	if ( index < 0 || index >= (int)this->players.size() ) {
		return NULL;
	}
	
	return this->players[index];
	
}

/**
 * Returns the player in turn.
 * @return The player in turn.
 */	
Player *GameEngine::getPlayerInTurn() {

	if ( this->players.size() > 0 )
		return this->players[this->playerInTurn];
		
	std::cerr << "GameEngine::getPlayerInTurn: no players in the game"
	          << std::endl;
	return NULL;

}

/**
 * Returns the projectile template of given index or NULL for invalid index.
 * @return Projectile template of given index or NULL for invalid index.
 */
const Projectile* GameEngine::getProjectileTemplate( int index )
{
	
	if ( index < 0 || index >= (int)this->projectileTemplates.size() )
		return NULL;
		
	return this->projectileTemplates[index];
	
}

/**
 * Sets the function to call at the beginning of a turn.
 * @param callbackFunction The function to call.
 * @param parameter        The parameter for the function.
 */	
void GameEngine::setCallbackFunction( void (*callbackFunction)( void*),
                                      void *parameter )
{
	
	this->callbackFunction = callbackFunction;
	this->callbackFunctionParameter = parameter;
	
}

/**
 * Tries to start the game.
 * @return Return values are following:
 *         0: start successful.
 *         -1: game already running (earlier game must end first).
 *         -2: game does not have enough players.
 *         -3: world has not been created. 
 */
int GameEngine::startGame()
{
	
	if ( this->gameStatus != GAMEOVER )
		return -1;
		
	if ( this->players.size() <= 1 )
		return -2;
		
	if ( this->gameWorld == NULL )
		return -3;
		
	//Zero points.
	for ( unsigned int i = 0; i < this->players.size(); i++ )
		this->players[i]->clearPoints();
	
	this->playerInTurn = 0;
	this->endOfRoundPassed = false;
	this->gameStatus = TURN;
	this->beginTurn();
	
	return 0;
	
}

/**
 * Ends the game - that is sets the status to GAMEOVER and calculates
 * points and rankings.
 */
void GameEngine::endGame()
{
	
	if ( this->gameStatus == GAMEOVER )
		return;
	
	this->gameStatus = GAMEOVER;
	
	//Remove players wanting to quit.
	for ( int i = this->players.size() - 1; i >= 0; i-- ) {
		
		if ( this->players[i]->hasQuitted() )
			this->removePlayer( i );
		
	}
	
	//Calculate Last man standing-points.
	for ( unsigned int i = 0; i < this->players.size(); i++ )
		this->players[i]->calculatePoints();
	
	//Calculate rankings.
	for ( unsigned int i = 0; i < this->players.size(); i++ )
		this->players[i]->calculateRanking();
	
	//Sort players.
	this->sortPlayers();
	
	//Send a signal to game window to make it update the list
	if ( this->callbackFunction )
		this->callbackFunction( this->callbackFunctionParameter );

}

/**
 * Does end of round procedures.
 */
void GameEngine::endOfRound()
{
	
	this->endOfRoundStepsTaken = 0;
	this->endOfRoundTimeRemainder = 0;
	this->gameStatus = ENDOFROUND;

}

/**
 * Gives the turn to next player. Mainly for game engine's own use. If used
 * outside, it means skipping the turn.
 */	
void GameEngine::nextTurn()
{
	
	int previousPlayer = this->playerInTurn;
	
	this->players[this->playerInTurn]->setActive( false );
		
	do {
		
		this->playerInTurn++;
		
		if ( this->playerInTurn >= (int)this->players.size() ) {
		
			//End of round.
			this->playerInTurn = 0;
			if ( this->gameStatus == TURN )
				this->endOfRound();
			else
				this->endOfRoundPassed = true;
			
		}
		
	} while ( this->players[this->playerInTurn]->isDead()
	          && this->playerInTurn != previousPlayer );
	
	this->beginTurn();

}

/**
 * Starts action phase which continues until no action flagged body exists.
 */
void GameEngine::startAction()
{
	
	if ( this->gameStatus == TURN ) {
		
		this->gameStatus = ACTION;
		this->actionTimeRemainder = 0;
		
	}
	
}

/**
 * Works "identically" with startAction, but all the changes are only
 * simulated - no permanent changes are made. Big difference between these
 * two functions is, that this function returns only after it has completed
 * the simulation.
 */
void GameEngine::simulate()
{
	
	int i;
	bool isAction = true;
	Body *body;
	
	//Notify players of simulation.
	for ( i = 0; i < (int)this->players.size(); i++ )
		this->players[i]->startSimulation();
		
	//Simulation.
	while ( isAction ) {

		this->gameWorld->step( GameEngine::actionStepLength );
		
		//Check whether all action has ended.
		i = 0;
		isAction = false;
		while ( (body = this->gameWorld->getBody(i++)) != NULL && !isAction ) {
			
			if ( body->getActionFlag() && !body->isDestroyed() )
				isAction = true;
			
		}

	}
	
	//Notify players.
	for ( i = 0; i < (int)this->players.size(); i++ )
		this->players[i]->endSimulation();

}

/**
 * Allows the game engine to work. Depending on the game status the engine
 * will do a bit different things.
 * @param timestep Delay since last call (ms).
 */
void GameEngine::step( unsigned int timestep )
{

	int i = 0;
	const Body* body;
	int stepcount = 0;

	if ( this->gameStatus == ACTION ) {
		
		//Simulate world with constant length steps.
		this->actionTimeRemainder += timestep;
		while ( this->actionTimeRemainder >= GameEngine::actionStepLength ) {
			
			this->gameWorld->step( GameEngine::actionStepLength );
			this->actionTimeRemainder -= GameEngine::actionStepLength;
			
		}
		
		//Has action ended?
		this->gameStatus = TURN;
		while ( ( body = this->gameWorld->getBody( i++ ) ) != NULL
		        && this->gameStatus == TURN ) {
			
			if ( body->getActionFlag() && !body->isDestroyed() )
				this->gameStatus = ACTION;
			
		}

		//If action is over, begin a new turn.
		if ( this->gameStatus == TURN ) {
			this->nextTurn();
		}

	}
	else if ( this->gameStatus == TURN ) {
		
		//Let AI think.
		Ai *computerAI = this->players[this->playerInTurn]->getAI();
		if ( computerAI ) {
			computerAI->think();		
		}
		
	}
	else if ( this->gameStatus == ENDOFROUND ) {
		
		//Lisätään suoritettava aika ja lasketaan montako askelta nyt pitäisi
		//ottaa.
		this->endOfRoundTimeRemainder += timestep;
		stepcount = this->endOfRoundTimeRemainder
		            / GameEngine::endOfRoundStepLength;
		this->endOfRoundTimeRemainder -= stepcount
		                                 * GameEngine::endOfRoundStepLength;
		
		//Tutkitaan, onko endofround vaihe suoritettu ja aika siirtyä vuorovaiheeseen.
		if ( stepcount + this->endOfRoundStepsTaken
		     >= GameEngine::endOfRoundStepCount ) {
			stepcount = GameEngine::endOfRoundStepCount
			            - this->endOfRoundStepsTaken;
			this->gameStatus = TURN;
		}
		
		//Otetaan askeleita, jos niitä on otettavana.
		if ( stepcount ) {
			this->gameWorld->endOfRound( ( float )stepcount
			                             / GameEngine::endOfRoundStepCount );
			this->endOfRoundStepsTaken += stepcount;
		}
		
	}
	
}

/**
 * Checks game over conditions (that is number of players alive is less than
 * two). Ends game if conditions are met.
 */
void GameEngine::checkGameOverConditions()
{
	
	int playersAlive = 0;
	
	if ( this->gameStatus == GAMEOVER )
		return;
	
	for ( unsigned int i = 0; i < this->players.size(); i++ )
		playersAlive += !this->players[i]->isDead();
		
	if ( playersAlive < 2 ) {
		this->endGame();
	}
		
}

/**
 * Begins a new turn. Does the necessary routines.
 */
void GameEngine::beginTurn()
{
	
	//If game has ended, no new turn will be started.
	this->checkGameOverConditions();
	
	if ( this->gameStatus != GAMEOVER ) {
	
		//If end of round procedures has been skipped because of turn phase,
		//do the procedures now.
		if ( this->endOfRoundPassed ) {
				
			this->endOfRoundPassed = false;
			this->endOfRound();
			
		}
				
		//The player in turn must be alive...
		while ( this->players[this->playerInTurn]->isDead() )
			this->nextTurn();
		if ( this->players[this->playerInTurn]->getAI() )
		  this->players[this->playerInTurn]->getAI()->startThinking();
		this->players[this->playerInTurn]->setActive( true );
			
		//If the callback function has been set, call it with the given
		//parameter.
		if ( this->callbackFunction )
			this->callbackFunction( this->callbackFunctionParameter );
		
	}
	
}

/**
 * Sorts the players by rankings. First is the player with lowest ranking
 * and last is the player with best ranking.
 */
void GameEngine::sortPlayers()
{
	
	Player *player;
	int i, j;
	
	for ( i = 1; i < (int)this->players.size(); i++ ) {
		
		for ( j = i - 1; j >= 0
		                 && this->players[j+1]->getRanking()
		                    < this->players[j]->getRanking(); j-- ) {
			
			player = this->players[j+1];
			this->players[j+1] = this->players[j];
			this->players[j] = player;
			
		}
		
	}
	
}

/**
 * Draws the world into graphics.
 * @param graphics The graphics object to draw to.
 */
void GameEngine::draw(Graphics &graphics)
{
	if ( this->gameWorld )
		this->gameWorld->draw(graphics);
}

/**
 * Tells whether the given player is in the game.
 * @param player The player to look for.
 * @return Whether the given player is in the game.
 */
bool GameEngine::hasPlayer(Player &player) const{
	
	for (unsigned int i=0; i < this->players.size(); i++){
		if (this->players[i] == &player){
			return true;
		}
	}
	return false;
}

/**
 * Adds the given player in the game. Does not add same player multiple
 * times. Game engine will clean the player's memory allocation!
 * @param The player to be add.
 */
void GameEngine::addPlayer(Player &player){
	
	if (!this->hasPlayer(player)){
		this->players.push_back(&player);
	}
}

/**
 * Removes the player of given index from the game.
 * @param index The index of the player to be removed.
 */
void GameEngine::removePlayer(int index){

	Player *player;
		
	if (index < 0 || index >= (int)this->players.size() ) {
		std::cerr << "GameEngine::removePlayer: Invalid index " << index;
		return;
	}

	if ( this->gameStatus != GAMEOVER ) {
		
		this->players[index]->quit();
		//Tutkitaan, onko pelinaineksia enää jäljellä.
		this->checkGameOverConditions();
		if ( this->gameStatus == TURN && index == this->playerInTurn )
			this->nextTurn();

	}
	else {
		
		player = this->players[index];
		this->players.erase(this->players.begin() + index);
		delete player;
	
	}
	
}	

/**
 * Removes the given player from the game - if it is in it.
 * @param player The player to remove.
 */
void GameEngine::removePlayer(Player &player){
	
	for (unsigned int i = 0; i < this->players.size(); i++){
		if (this->players[i] == &player){
			return this->removePlayer(i);
		}
	}
}

/**
 * Removes all players from the game.
 */
void GameEngine::removeAllPlayers(){
	
	int i;
	
	for (i = this->players.size() - 1; i >= 0; i--){
		this->removePlayer(i);
	}
}
