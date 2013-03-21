
#include "Ai.h"

/**
 * Class Ai.
 * Artifical intelligence for computer players.
 * @author Lasse Hakulinen
 */


/**
 * Constructor.
 * @param &player - reference to player whose AI this is.
 * @param skill - level of skill.
 */
Ai::Ai(Player &player, int skill)
	: player(player) {
		
	this->setThinkingLevels(skill);
	
	this->thinkStepsTaken = 0;
	this->spesifyingSteps = 0;
	this->bestDamage = 0;
	this->bestAngle = 0;
	this->bestPower = 0;
}

/**
 * Destructs the AI
 */
Ai::~Ai() {
	this->player.removeAI();
}

/**
 * Calculates the best shot for computer player.
 * Tests only one shot and checks if it is better than the current best one.
 * This function is called numerous times in one turn.
 * When Ai is done with thinking, it automatically fires a shot.
 */
void Ai::think() {
	
	float damage = 0;
	int weapon = 0;

	this->player.getGameEngine().getWorld()->getSounds().disableSounds();
	this->thinkStepsTaken++;

	// At first fires randomly and checks the best shot
	if (this->thinkStepsTaken < this->randomStepCount){
		
		weapon = (int)((float)rand() / RAND_MAX *
                  this->player.getWeaponSelection().getWeaponCount());
				
		this->currentAngle = (float)rand() / RAND_MAX * 3.14;
		this->currentPower = (float)rand() / RAND_MAX * 0.5 + 0.2;
		this->player.setSelectedWeapon(weapon);
		this->player.setAimingAngle(this->currentAngle);
		this->player.setAimingPower(this->currentPower);
		
	}
	
	// Specifies the best shot
	else {
		if (this->thinkStepsTaken == this->randomStepCount){
			this->currentPower = this->bestPower - 0.08;
		}	
		
		if (this->spesifyingSteps == 0){
			// Checks with 3 different powers.
			this->currentAngle = this->bestAngle -
              ((this->thinkStepCount - this->randomStepCount) / 6 * 0.05);
				
			this->currentPower += 0.04;
		}
		
		this->spesifyingSteps++;
		if (this->spesifyingSteps >=
           (this->thinkStepCount - this->randomStepCount) / 3){
				
			this->spesifyingSteps = 0;
		}
		
		this->currentAngle += 0.05;
		this->player.setAimingAngle(this->currentAngle);
		this->player.setAimingPower(this->currentPower);
		
	}
	
	// Fires a simulation shot and defines how good it was.
	
	this->player.shootSimulation();	
	
	damage = this->player.getSimulationPoints();
	damage -= 3 * this->player.getSimulationDamage() *
	              Player::pointsPerDamage;
		
	if (damage > this->bestDamage || this->thinkStepsTaken <= 1){
		this->bestDamage = damage;
		this->bestAngle = this->currentAngle;
		this->bestPower = this->currentPower;
		
		if (this->thinkStepsTaken < this->randomStepCount){
			this->bestWeapon = weapon;
		}
	}

	// Sets the best shot which is fired if the thinking is interrupted
	this->player.setAimingAngle(this->bestAngle);
	this->player.setAimingPower(this->bestPower);
	this->player.setSelectedWeapon(this->bestWeapon);

	this->player.getGameEngine().getWorld()->getSounds().enableSounds();

	// If thinking is done, fires the best shot
	if (this->thinkStepsTaken >= this->thinkStepCount){
		this->thinkStepsTaken = 0;
		this->spesifyingSteps = 0;
		
		if (this->bestDamage <= 0){
			this->selectStartingLocation();
		}
		else {
			this->player.shoot();
		}
	}
	
}

/**
 * Does the shopping for computer player.
 */	
void Ai::doShopping() {
	// shields = how much money is left after buying shields
	
	int minShields = (int)(0.4 * this->player.getMoney());
	int maxShields = (int)(0.7 * this->player.getMoney());
	int shields = (int)((float)rand() / RAND_MAX *
					(maxShields - minShields) + minShields);
	
	while (this->player.getMoney() > shields){
		if (!this->player.buyShieldArmor(1)){
			break;
		}
	}

	int failedCount = 0;
	int index = 0;
	const Projectile *projectile;
	
	while (failedCount < 100){
		index = (int)((float)rand() / RAND_MAX *
                 this->player.getGameEngine().getProjectileTemplateCount());
				
		projectile =
		         this->player.getGameEngine().getProjectileTemplate(index);
		
		if (projectile->getPrice() > this->player.getMoney()){
			failedCount++;
		}
		
		else if (this->player.getWeaponSelection().getShotCount(index)
                 < Weapon::maximumCount){
					
			this->player.buyShots(index, 1);
		}
	}
	
}

/**
 * Selects the starting location for computer player.
 */
void Ai::selectStartingLocation() {

	int count = 0;
	int width = this->player.getGameEngine().getWorld()
	            ->getCoordinateSystem().getWidth();
		
	int height = this->player.getGameEngine().getWorld()
	             ->getCoordinateSystem().getHeight();
		
	while(this->player.setLocation((float)rand() / RAND_MAX * width,
          (float)rand() / RAND_MAX * height) == -3 && count < 200){
				
		count++;
	}
		
}

/**
 * Initializes variables for thinking
 */	 
void Ai::startThinking() {
	this->thinkStepsTaken = 0;
	this->spesifyingSteps = 0;
}

/**
 * Sets the levels how many simulation shots can be fired in one turn.
 * @param skill - Ai's level of skill (min = 0, max = 2)
 */
void Ai::setThinkingLevels(int skill){
		
	// stupid
	if (skill == 0){
		this->randomStepCount = 50;
		this->thinkStepCount = 60;
	}
	// normal
	else if (skill == 1){
		this->randomStepCount = 115;
		this->thinkStepCount = 140;
	}
	// good
	else {
		this->randomStepCount = 210;
		this->thinkStepCount = 240;
	}
}
