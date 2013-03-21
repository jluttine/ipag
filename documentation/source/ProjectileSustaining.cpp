
#include "ProjectileSustaining.h"

/**
 * Constructs a new projectile.
 * @param name            Name of the projectile.
 * @param description     Description of the projectile.
 * @param price           Price of the projectile.
 * @param ammunition      The projectiles to shoot.
 * @param count           Number of projectiles to shoot.
 * @param delay           Time delay between two shots.
 * @param dispersingAngle The angle of dispersion to give some unaccuracy.
 */
ProjectileSustaining::ProjectileSustaining( const string &name,
                                            const string &description,
                                            int price,
                                            const Projectile &ammunition,
                                            int count,
                                            int delay,
                                            float dispersingAngle )
	: Projectile( name, description, price, -1, -1, BodyExplosion::SMALL_GAS,
	              ammunition.getRadius(), 0, 0, 0 ),
	  ammunition( ammunition )
{
	
	this->shotCount = count;
	this->shotDelay = delay;
	this->timeElapsed = delay;
	this->shotsFired = 0;
	this->isShot = false;
	this->dispersingAngle = dispersingAngle;
	
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileSustaining::ProjectileSustaining(const ProjectileSustaining &copy)
	: Projectile( copy ), ammunition( copy.ammunition )
{
	
	this->shotCount = copy.shotCount;
	this->shotDelay = copy.shotDelay;
	this->timeElapsed = copy.shotDelay;
	this->shotsFired = 0;
	this->isShot = false;
	this->dispersingAngle = copy.dispersingAngle;
	
}
	
/**
 * Simulates the timestep for the capsule.
 * @param timestep The step length in ms.
 * @param capsule  The capsule, that is the projectile in the world.
 */
void ProjectileSustaining::step( int timestep, BodyProjectile &capsule )
{
	
	float angle;
	Vector velocity;
	
	if ( !this->isShot ) {
		this->shotVelocity = capsule.getVelocity();
		this->isShot = true;
	}

	capsule.setVelocity( 0, 0 ); //zero velocity

	this->timeElapsed += timestep;
	
	if ( this->timeElapsed >= this->shotDelay ) {
		//Shoot!
		velocity = this->shotVelocity;
		angle = ( 2.0 * rand() / RAND_MAX - 1.0 ) * this->dispersingAngle;
		velocity.rotate( angle );
		
		Projectile *model = this->ammunition.getCopy();
		model->setShooter( this->getShooter() );
			
		BodyProjectile *newProjectile =
			new BodyProjectile( capsule.getWorld(), capsule.getLocation().getX(),
		                      capsule.getLocation().getY(), *model );

		newProjectile->setVelocity( velocity.getX(), velocity.getY() );
		newProjectile->setActionFlag( capsule.getActionFlag() );
		capsule.getWorld().addBody( *newProjectile );
		capsule.getWorld().playSound( model->getSound() );
		
		//Time zeroed.
		this->timeElapsed = 0;
		
		//One shot fired.
		this->shotsFired++;
		if ( this->shotsFired >= this->shotCount )
			capsule.destroy();
		
	}
	
	Projectile::step( timestep, capsule );
	
}

/**
 * Simulates the collision between the capsule and colliding body.
 * @param capsule       The capsule.
 * @param collidingBody The body to collide with.
 */
void ProjectileSustaining::collide( BodyProjectile &capsule,
                                    Body &collidingBody )
{
	
	return;
	
}

/**
 * Forms a string to describe the damage of the projectile.
 * @param text String to store the damage description.
 */
void ProjectileSustaining::getDamageText( std::string &text ) const
{
	
	char buffer[80];
	std::string damage;
	this->ammunition.getDamageText( damage );
	sprintf( buffer, "%dx%s", this->shotCount, damage.c_str() );
	text = buffer;
	
}

