#ifndef PLAYER_H
#define PLAYER_H

class Player;

#include "BodyCannon.h"
#include "GameEngine.h"
#include "Ai.h"
#include "WeaponSelection.h"
#include "Shield.h"

using std::string;

/**
 * @author Jaakko Luttinen
 * Player is a class for a player in the game. Player has name, color,
 * points, ranking, money, integrity and a cannon.
 */
class Player {
	
public:

	/**
	 * Points for each damage unit.
	 */
	static const int pointsPerDamage = 1;
	
	/**
	 * Points for each kill.
	 */
	static const int pointsPerKill = 100;
	
	/**
	 * Points for being the last man standing.
	 */
	static const int pointsPerLastManStanding = 200;
	
	/**
	 * Minimum distance between two alive cannons on same planet.
	 */
	static const int minimumDistance = 40;

	/**
	 * Constructs a new player.
	 * @param name   Name of the player.
	 * @param engine The game to be in.
	 */
	Player(const string &name, GameEngine &engine);
	
	/**
	 * Destructs the player.
	 */
	~Player();
	
	/**
	 * Sets the name of the player.
	 * @param name New name.
	 */
	inline void setName( const string &name )  { this->name = name; };
	
	/**
	 * Returns the name of the player.
	 * @return Name of the player.
	 */
	inline const char* getName() const  { return this->name.c_str(); };
	
	/**
	 * Returns the game which the player is in.
	 * @return The game.
	 */
	inline GameEngine& getGameEngine() const  { return this->engine; };

	/**
	 * Sets the cannon for the player. World will clean the memory.
	 * @param newCannon A cannon for the player.
	 */	
	void setCannon( BodyCannon &newCannon );
	
	/**
	 * Removes the cannon from player.
	 */
	void removeCannon();

	/**
	 * Returns the cannon of the player. Note that it may be NULL.
	 * @return Player's cannon.
	 */
	const BodyCannon* getCannon() const  { return this->cannon; };

	/**
	 * Sets the AI for the player. Player will free the memory allocation.
	 * @param newAI AI for the player.
	 */	
	void setAI( Ai &newAI );
	
	/**
	 * Removes the AI from player.
	 */
	void removeAI();

	/**
	 * Returns the AI (may be NULL).
	 * @return AI (or NULL).
	 */
	inline Ai* getAI()  { return this->computerAI; };
	
	/**
	 * Sets the color of the player.
	 * @param r Red component.
	 * @param g Green component.
	 * @param b Blue component.
	 */
	void setColor( unsigned char r, unsigned char g, unsigned char b );
	
	/**
	 * Tells the color of the player.
	 * @param r Red component.
	 * @param g Green component.
	 * @param b Blue component.
	 */
	void getColor(unsigned char &r, unsigned char &g, unsigned char &b) const;
	
	/**
	 * Sets player's integrity.
	 * @param integrity The integrity of the player.
	 */
	void setIntegrity( float integrity );
	
	/**
	 * Sets player's money.
	 * @param money The money for the player.
	 */
	inline void setMoney( int money )  { this->money = money; };
	
	/**
	 * Returns the integrity of the player.
	 * @return The integrity of the player.
	 */
	inline float getIntegrity() const  { return this->integrity; };
	
	/**
	 * Returns the money of the player.
	 * @return The money of the player.
	 */
	inline int getMoney() const  { return this->money; };

	/**
	 * Player takes the given damage. Damage may have a player as a source.
	 * Calculates damage points as well.
	 * @param shooter Source of the damage. May be NULL.
	 * @param damage  The damage.
	 */	
	void doDamage( Player *shooter, float damage );
	
	/**
	 * Zeroes points.
	 */
	inline void clearPoints()  { this->points = 0; };
	
	/**
	 * Returns player's points.
	 * @return Player's points.
	 */
	inline int getPoints() const  { return this->points; };
	
	/**
	 * Tells whether the player is dead. Player is dead if at least one of the
	 * following conditions is met: 1) player has no cannon; 2) player's
	 * cannon is ruined; 3) player's integrity is zero; 4) player has no
	 * ammunition left.
	 */
	bool isDead();
	
	/**
	 * Calculates "Last man standing" points for the player, if not calculated
	 * already.
	 */
	void calculatePoints();
	
	/**
	 * Calculates the ranking points for the player.
	 */
	void calculateRanking();
	
	/**
	 * Returns the ranking of the player.
	 * @return The ranking of the player.
	 */
	inline int getRanking() const  { return this->ranking; };
	
	/**
	 * Shoots with selected weapon.
	 */
	void shoot();
	
	/**
	 * Simulates a shot. Does not do any permanent changes.
	 */
	void shootSimulation();
	
	/**
	 * Increases the aiming angle of the cannon.
	 * @param angle The angle to add.
	 */
	void increaseAimingAngle(float angle);
	
	/**
	 * Increases aiming power of the cannon.
	 * @param power The power to add.
	 */
	void increaseAimingPower(float power);
	
	/**
	 * Sets the aiming angle of the cannon.
	 * @param angle The angle in radians.
	 */
	void setAimingAngle(float angle);
	
	/**
	 * Sets the aiming power of the cannon.
	 * @param power The power.
	 */
	void setAimingPower(float power);

	/**
	 * Game engine will call this to notify the player of a starting
	 * simulation. Not for others!
	 */	
	void startSimulation();
	
	/**
	 * Game engine will call this to notify the player that the simulation has
	 * ended. Not for others!
	 */
	void endSimulation();

	/**
	 * Tells the points the player got in the simulation.
	 * @return The points player got in simulation.
	 */	
	int getSimulationPoints() const  { return this->simulationPoints; };
	
	/**
	 * Tells the damage the player received in the simulation.
	 * @return The damage player received in simulation.
	 */
	float getSimulationDamage() const  { return this->simulationDamage; };
	
	/**
	 * Tells whether player died in the simulation. Returns false if the
	 * player was dead already. Only death in simulation matters.
	 * @return Whether player died in simulation.
	 */
	bool getSimulationDeath() 
		{ return !this->isDead() && this->simulationDamage >= this->integrity;};
	
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
	int setLocation( float x, float y );

	/**
	 * Selects a weapon.
	 * @param change How many steps to take in weapon selection.
	 * @return Returns the selected weapon, or NULL.
	 */	
	const Weapon* selectWeapon( int change );
	
	/**
	 * Sets the weapon of given index as the selected weapon.
	 * @param index Index of the weapon in player's weapon selection.
	 * @return The selected weapon, or NULL.
	 */
	const Weapon* setSelectedWeapon(int index)
		{ return this->weaponSelection.setSelectedWeapon(index); };
	
	/**
	 * Buys given projectiles.
	 * @param projectile Shot to buy.
	 * @param count      Number of shots to buy.
	 * @return True for successful shopping.
	 */
	bool buyShots( int projectile, int count );
	
	/**
	 * Gives the player infinite shots of given projectile.
	 * @param projectile The projectile to give infinitely.
	 */
	void addInfiniteShots( int projectile );
	
	/**
	 * Returns the weapon selection of the player.
	 * @return The weapon selection.
	 */
	const WeaponSelection& getWeaponSelection() const
		{ return this->weaponSelection; };
		
	/**
	 * Clears the weapon selection.
	 */
	inline void clearWeaponSelection()  { this->weaponSelection.clear(); };
	
	/**
	 * Returns the shield of the player.
	 * @return Player's shield.
	 */
	const Shield& getShield() const  { return this->shield; };
	
	/**
	 * Tries to buy armor for the shield.
	 * @param armor Armors to buy.
	 * @return True for successful shopping.
	 */
	bool buyShieldArmor( int armor );
	
	/**
	 * Clears all armor.
	 */
	void clearArmor()  { this->shield.clear(); };

	/**
	 * Increases the parameter of the selected weapon.
	 * @param index Index of the parameter.
	 * @param steps The steps to increase.
	 */
	void increaseParameter( int index, int steps );

	/**
	 * Sets the player active or passive. That is, the cannon will be shown
	 * differently when the player has turn.
	 * @param active Active=true, passive=false.
	 */
	void setActive(bool active);
	
	/**
	 * Raises a flag to tell that the player wants to quit the game.
	 */
	void quit();
	
	/**
	 * Tells whether the player has requested to quit the game.
	 */
	inline bool hasQuitted() const  { return this->quitted; };
	
private:

	/**
	 * Gives points for killing a player.
	 * @param dead The killed player.
	 */
	void pointsKill( const Player &dead );
	
	/**
	 * Might give minus points for death, suicide for example.
	 * @param
	 */
	void pointsDeath( const Player &killer );
	
	/**
	 * Calculates player's relative death rank.
	 * RDR = ( players died before him ) / ( players in the game - 1 ).
	 */
	void calculateRelativeDeathRank();

	/**
	 * Player's cannon. Player does NOT clean the memory allocation, World
	 * will.
	 */
	BodyCannon *cannon;
	
	/**
	 * Player's AI. Player frees the memory allocation.
	 */
	Ai *computerAI;
	
	/**
	 * Player's integrity.
	 */
	float integrity;
	
	/**
	 * Damage received in the last simulation.
	 */
	float simulationDamage;
	
	/**
	 * Points received in the last simulation.
	 */
	int simulationPoints;
	
	/**
	 * Tells whether simulation is on.
	 */
	bool simulating;

	/**
	 * Player's shield.
	 */
	Shield shield;
	
	/**
	 * The game the player is in.
	 */
	GameEngine &engine;
	
	/**
	 * Weapon selection of the player.
	 */
	WeaponSelection weaponSelection;
	
	/**
	 * Player's name.
	 */
	string name;
	
	/**
	 * Player's points.
	 */
	int points;
	
	/**
	 * Player's ranking.
	 */
	int ranking;
	
	/**
	 * Player's money.
	 */
	int money;
	
	/**
	 * Player's relative death rank.
	 * RDR = (players died before him)/(players-1).
	 */
	float relativeDeathRank;
	
	/**
	 * Components of player's color.
	 */
	unsigned char colorR, colorG, colorB;
	
	/**
	 * Flag to indicate that player wants to leave the game.
	 */	
	bool quitted;
	
};

#endif 
