
#include <iostream>
#include <math.h>
#include "Player.h" 
#include "Projectile.h"
#include "BodyPlanet.h"
#include "Angle.h"


/**
 * Constructs a new player.
 * @param name   Name of the player.
 * @param engine The game to be in.
 */
Player::Player(const string &name, GameEngine &engine)
	: engine(engine)
{
	
	this->setName( name );
	this->money = 0;
	this->quitted = false;
	this->engine = engine;
	this->cannon = NULL;
	this->computerAI = NULL;
	this->name = name; //string will deep copy
	this->points = 0;
	this->ranking = 0;
	this->relativeDeathRank = -1;
	
	this->simulationDamage = 0;
	this->simulationPoints = 0;
	this->simulating = false;
	
	this->integrity = 100;
	
	this->colorR = 0;
	this->colorG = 0x80;
	this->colorB = 0xFF;

}

/**
 * Destructs the player.
 */
Player::~Player() {

	this->removeCannon();
	this->removeAI();

}

/**
 * Sets the cannon for the player. World will clean the memory.
 * @param newCannon A cannon for the player.
 */	
void Player::setCannon( BodyCannon &newCannon ){
	
	this->removeCannon();
	this->cannon = &newCannon;	
}


/**
 * Removes the cannon from player.
 */
void Player::removeCannon(){
	
	BodyCannon *oldCannon;
	
	if (this->cannon){
		oldCannon = this->cannon;
		this->cannon = NULL;
		oldCannon->getWorld().removeBody( *oldCannon );
	}		
}

/**
 * Sets the AI for the player. Player will free the memory allocation.
 * @param newAI AI for the player.
 */	
void Player::setAI( Ai &newAI )
{
	
	this->removeAI();
	this->computerAI = &newAI;
	
}

/**
 * Removes the AI from player.
 */
void Player::removeAI()
{
	
	Ai* oldAI;
	
	if ( this->computerAI ) {
		
		//Removal must be done with appropriate precautions, because AI will
		//call this function back, and we don't want it to make things crash.
		oldAI = this->computerAI;
		this->computerAI = NULL;
		delete oldAI;
		
	}
	
}

/**
 * Sets the color of the player.
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void Player::setColor( unsigned char r, unsigned char g, unsigned char b )
{

	this->colorR = r;
	this->colorG = g;
	this->colorB = b;
	
}

/**
 * Tells the color of the player.
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void Player::getColor( unsigned char &r, unsigned char &g,
                       unsigned char &b ) const
{
	
	r = this->colorR;
	g = this->colorG;
	b = this->colorB;
	
}

/**
 * Sets player's integrity.
 * @param integrity The integrity of the player.
 */
void Player::setIntegrity( float integrity )
{
	
	if ( integrity > 0 ) {
		this->integrity = integrity;
		this->relativeDeathRank = -1;
	}
	
}

/**
 * Player takes the given damage. Damage may have a player as a source.
 * Calculates damage points as well.
 * @param shooter Source of the damage. May be NULL.
 * @param damage  The damage.
 */	
void Player::doDamage( Player *shooter, float damage )
{
	
	if ( this->integrity <= .0
	     || ( this->simulating && this->simulationDamage >= this->integrity ))
	{
		return;
	}
		
	//Calculate damage.
	damage = this->shield.absorbDamage( damage );
		
	if ( this->simulating ) {
		
		if ( damage + this->simulationDamage >= this->integrity ) {
			//Don't let too much damage be done.
			damage = this->integrity - this->simulationDamage;
			this->simulationDamage = this->integrity;
		}
		else {
			//Do damage.
			this->simulationDamage += damage;
		}
		
		//Damage points.
		if ( shooter ) {
			if ( shooter == this ) {
				this->simulationPoints -= (int)( damage * Player::pointsPerDamage );
			}
			else
			{
				shooter->simulationPoints +=
					( int )( damage * Player::pointsPerDamage );
			}
		}
		
		//Kill points.
		if ( this->integrity <= this->simulationDamage ) {
			
			if ( shooter != NULL ) {
				if ( shooter == this )
					this->simulationPoints -= Player::pointsPerKill;
				else
					shooter->simulationPoints += Player::pointsPerKill;
			}
				
		}
		
	}
	else {
		
		//Don't let too much damage be done.
		if ( damage >= this->integrity )
			damage = this->integrity;
			
		//Do damage.
		this->integrity -= damage;
	
		//Damage points.
		if ( shooter ) {
			if ( shooter == this )
				this->points -= ( int )( damage * Player::pointsPerDamage );
			else
				shooter->points += ( int )( damage * Player::pointsPerDamage );
		}
		
		//Kill points.
		if ( this->integrity <= .0 ) {
		
			this->integrity = .0;

			if ( this->cannon ) {
				this->cannon->ruin();
			}
		
			if ( shooter ) {
				this->pointsDeath( *shooter );
				shooter->pointsKill( *this );
			}
			
		}
		
	}
	
}

/**
 * Gives points for killing a player.
 * @param dead The killed player.
 */
void Player::pointsKill( const Player &dead ) 
{

	if ( &dead != this )
		this->points += Player::pointsPerKill;
		
}

/**
 * Might give minus points for death, suicide for example.
 * @param
 */
void Player::pointsDeath( const Player &killer )
{
	
	if ( &killer == this )
		this->points -= Player::pointsPerKill;
		
	this->calculateRelativeDeathRank();
		
}

/**
 * Calculates player's relative death rank. RDR = ( players died before him)
 * / (players in the game - 1).
 */
void Player::calculateRelativeDeathRank()
{
	
	int playerCount = this->engine.getPlayerCount();
	int deadPlayers = 0, i;
	
	if ( playerCount ) {

		for ( i = 0; i < playerCount; i++ ) {
			if ( this->engine.getPlayer( i )->isDead() )
				deadPlayers++;		
		}
		
		if ( this->isDead() )
			deadPlayers -= 1;

		this->relativeDeathRank = ( float )( deadPlayers ) / ( playerCount - 1);
		
	}
		
}

/**
 * Calculates "Last man standing" points for the player, if not calculated
 * already.
 */
void Player::calculatePoints()
{
	
	if ( this->relativeDeathRank < 0 ) {
		if ( !this->isDead() )
			this->calculateRelativeDeathRank();
		else
			this->relativeDeathRank = 0;
	}
		
	this->points += ( int )( this->relativeDeathRank * this->relativeDeathRank
	                         * Player::pointsPerLastManStanding );
	
}

/**
 * Calculates the ranking points for the player.
 */
void Player::calculateRanking()
{

	Player *compare;
	int i;
	
	for ( i = 0; i < this->engine.getPlayerCount(); i++ ) {
		
		compare = this->engine.getPlayer( i );
		if ( compare != this ) {

			//Ranking score calculating....
			if ( this->points < compare->points )
				this->ranking -= 100;
			else if ( this->points > compare->points )
				this->ranking += 100;
		}
	}	
	
}

/**
 * Sets the player active or passive. That is, the cannon will be shown
 * differently when the player has turn.
 * @param active Active=true, passive=false.
 */
void Player::setActive(bool active){
	
	if (this->cannon){
		this->cannon->setActive(active);
	}
}

/**
 * Tells whether the player is dead. Player is dead if at least one of the
 * following conditions is met: 1) player has no cannon; 2) player's cannon
 * is ruined; 3) player's integrity is zero; 4) player has no ammunition
 * left.
 */
bool Player::isDead(){
	
	if ( !this->cannon || this->cannon->isDestroyed()
	     || this->cannon->isRuined() )
	{
		return true;
	}
	
	//Ruin the cannon if player is dead.
	if ( this->integrity <= 0 || this->weaponSelection.getWeaponCount() == 0
	     || this->quitted )
	{
		this->cannon->ruin();
		return true;
	}
		
	return false;
	
}

/**
 * Raises a flag to tell that the player wants to quit the game.
 */
void Player::quit()
{
	
	if ( !this->quitted ) {
		
		this->quitted = true;
		if ( this->cannon )
			this->cannon->ruin();
		this->engine.removePlayer( *this );
		
	}
	
}

/**
 * Tries to set the location for the player's cannon. Selects the nearest
 * planet and its nearest point on its surface.
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @return Return values are following:
 *         0: success.
 *         -1: world does not exist.
 *         -2: didn't find a planet.
 *         -3: too close to other player, please try again.
 */
int Player::setLocation( float x, float y )
{

	World *world = this->engine.getWorld();
	BodyPlanet *closestPlanet;
	Coordinates newLocation( world->getCoordinateSystem(), 0, 0 );
	float angleOnPlanet;
	int i;
	Player *player;
	
	if ( world == NULL )
		return -1;

	closestPlanet = ( BodyPlanet *)world->getNearestPlanet( x, y );
	
	if ( closestPlanet ) {
		//Determine the angle on planet.
		angleOnPlanet = atan2( closestPlanet->getLocation().getDistanceY( y ),
		                       closestPlanet->getLocation().getDistanceX( x ) );
		angleOnPlanet -= closestPlanet->getAngle();
		Angle::fix( angleOnPlanet );
		

		//Transform the location on planet to coordinates.
		BodyCannon::calculateLocation( newLocation, *closestPlanet,
		                               angleOnPlanet );
		                               
		//Check that the location is ok, that is, it is not too close to another
		//player on the sama planet.
		for ( i = 0; i < this->engine.getPlayerCount(); i++ ) {
			player = this->engine.getPlayer( i );
			if ( player != this ) {
				if ( player->cannon && !player->cannon->isRuined()
				     && &player->cannon->getPlanet() == closestPlanet )
				{
					if ( player->cannon->getLocation().getDistance(newLocation.getX(),
					                                               newLocation.getY())
					     < Player::minimumDistance )
					{
						return -3;
					}
				}
			}
		}
		
		if ( this->cannon ) {
			this->cannon->setPlanet( *closestPlanet );
			closestPlanet->addCannon( *this->cannon );
			this->cannon->setAngleOnPlanet( angleOnPlanet );
		}
		else {
			this->setCannon( *( new BodyCannon( *closestPlanet, angleOnPlanet,
			                                    *this ) ) );
			closestPlanet->addCannon( *this->cannon );
			world->addBody( *this->cannon );
		}
		
		//It takes whole turn to move.
		if ( this->engine.getStatus() == GameEngine::TURN )
			this->engine.nextTurn();
			
		return 0;
	}
	
	return -2;
	
}


/**
 * Shoots with selected weapon.
 */
void Player::shoot(){
	
	const Projectile *shotModel;
	Projectile *shot;
	
	if ( this->engine.getStatus() == GameEngine::TURN
	     && this->engine.getPlayerInTurn() == this )
	{
	
		if ( this->cannon ){
			
			ParameterList parameters =
				this->weaponSelection.getSelectedWeapon()->getParameters();
			int projectile = this->weaponSelection.shoot();
			if ( projectile >= 0 ) {
				shotModel = this->engine.getProjectileTemplate( projectile );
				if ( shotModel ) {
					shot = shotModel->getCopy();
					shot->setShooter( this );
					shot->setParameters( parameters );
					this->cannon->shoot(*shot);
				
				}
			}
		
		}
	
		this->engine.startAction();
		
	}
	
}

/**
 * Simulates a shot. Does not do any permanent changes.
 */
void Player::shootSimulation()
{
	
	const Projectile *shotModel;
	Projectile *shot;
	const Weapon *weapon;
	
	if ( this->engine.getStatus() == GameEngine::TURN
	     && this->engine.getPlayerInTurn() == this )
	{
		
		weapon = this->weaponSelection.getSelectedWeapon();
		if ( this->cannon && weapon ){
			
			ParameterList parameters = weapon->getParameters();
			int projectile = weapon->getShot();
			if ( projectile >= 0 ) {
				shotModel = this->engine.getProjectileTemplate( projectile );
				if ( shotModel ) {
					shot = shotModel->getCopy();
					shot->setShooter( this );
					shot->setParameters( parameters );
					this->cannon->shoot(*shot);
				
				}
			}
		
		}
	
		//This won't return until simulation is completed.
		this->engine.simulate(); 

	}
	
}

/**
 * Increases the aiming angle of the cannon.
 * @param angle The angle to add.
 */
void Player::increaseAimingAngle(float angle)
{
	if ( this->engine.getStatus() == GameEngine::TURN && this->cannon )
		this->cannon->setAimingAngle(this->cannon->getAimingAngle()+angle);
}

/**
 * Increases aiming power of the cannon.
 * @param power The power to add.
 */
void Player::increaseAimingPower( float power )
{
	if ( this->engine.getStatus() == GameEngine::TURN && this->cannon )
		this->cannon->setAimingPower( this->cannon->getAimingPower() + power );
}

/**
 * Sets the aiming angle of the cannon.
 * @param angle The angle in radians.
 */
void Player::setAimingAngle(float angle)
{
	if ( this->engine.getStatus() == GameEngine::TURN && this->cannon )
		this->cannon->setAimingAngle(angle);
}

/**
 * Sets the aiming power of the cannon.
 * @param power The power.
 */
void Player::setAimingPower( float power )
{
	if ( this->engine.getStatus() == GameEngine::TURN && this->cannon )
		this->cannon->setAimingPower(power );
}

/**
 * Game engine will call this to notify the player of a starting simulation.
 * Not for others!
 */	
void Player::startSimulation()
{
	
	this->simulating = true;
	this->simulationDamage = 0;
	this->simulationPoints = 0;
	
}

/**
 * Game engine will call this to notify the player that the simulation has
 * ended. Not for others!
 */
void Player::endSimulation()
{
	
	this->simulating = false;
	
}

/**
 * Selects a weapon.
 * @param change How many steps to take in weapon selection.
 * @return Returns the selected weapon, or NULL.
 */	
const Weapon* Player::selectWeapon( int change )
{
	
	if ( this->engine.getStatus() == GameEngine::TURN )
		return this->weaponSelection.selectWeapon( change );
	else
		return this->weaponSelection.getSelectedWeapon();
	
}

/**
 * Increases the parameter of the selected weapon.
 * @param index Index of the parameter.
 * @param steps The steps to increase.
 */
void Player::increaseParameter( int index, int steps )
{
	
	if ( this->engine.getStatus() == GameEngine::TURN )
		this->weaponSelection.increaseParameter( index, steps );
	
}

/**
 * Buys given projectiles.
 * @param projectile Shot to buy.
 * @param count      Number of shots to buy.
 * @return True for successful shopping.
 */
bool Player::buyShots( int projectileIndex, int count )
{
	
	const Projectile *projectile =
		this->engine.getProjectileTemplate( projectileIndex );
	
	if ( projectile && count * projectile->getPrice() <= this->money ) {
		
		count = this->weaponSelection.addShots( projectileIndex, count,
		                                        projectile->getParameterList());
		if ( count != 0 ) {
			this->money -= count * projectile->getPrice();
			return true;
		}
		
	}
	
	return false;
	
}

/**
 * Gives the player infinite shots of given projectile.
 * @param projectile The projectile to give infinitely.
 */
void Player::addInfiniteShots( int projectileIndex )
{
	
	const Projectile *projectile =
		this->engine.getProjectileTemplate( projectileIndex );
	
	if ( projectile ) {
		
		this->weaponSelection.addInfiniteShots( projectileIndex,
		                                        projectile->getParameterList());
		
	}
	
}

/**
 * Tries to buy armor for the shield.
 * @param armor Armors to buy.
 * @return True for successful shopping.
 */
bool Player::buyShieldArmor( int armor )
{
	
	int price = this->shield.getIncreasePrice( armor );
	if ( price == 0 || price > this->money )
		return false;
	
	this->shield.increase( armor );
	this->money -= price;
	
	return true;
	
}
