
#include "ProjectileShooting.h"

/**
 * Constructs a new projectile.
 * @param name           Name of the projectile.
 * @param description    Description of the projectile.
 * @param price          Price of the projectile.
 * @param spriteIndex    Index of the sprite.
 * @param soundIndex     Index of the firing sound.
 * @param explosionIndex Index of the explosion type.
 * @param radius         Radius of the projectile.
 * @param mass           Mass of the projectile.
 * @param damage         Maximum damage of the projectile.
 * @param damageRadius   Radius of the damage.
 * @param ammunition     Projectile template to shoot.
 * @param shotCount      Maximum ammunition. After all ammunition has been
 *                       fired, projectile will destruct.
 * @param shotDelay      Delay between two shots in ms.
 * @param shotVelocity   Shooting velocity for shots.
 */
ProjectileShooting
	::ProjectileShooting( const string &name, const string &description,
	                      int price, int spriteIndex, int soundIndex,
	                      BodyExplosion::EType explosionIndex, float radius,
	                      float mass, float damage, float damageRadius,
	                      const Projectile &ammunition, int shotCount,
	                      int shotDelay, float shotVelocity )
	: Projectile( name, description, price, spriteIndex, soundIndex,
	              explosionIndex, radius, mass, damage, damageRadius ),
	  ammunition( ammunition )
{

	this->shotCount = shotCount;
	this->shotsFired = 0;
	this->shotDelay = shotDelay;
	this->shotVelocity = shotVelocity;
	this->timeElapsed = 0;	
	
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileShooting::ProjectileShooting( const ProjectileShooting &copy )
	: Projectile( copy ), ammunition( copy.ammunition )
{
	
	this->shotCount = copy.shotCount;
	this->shotsFired = 0;
	this->shotDelay = copy.shotDelay;
	this->shotVelocity = copy.shotVelocity;
	this->timeElapsed = 0;	
	
}
	
/**
 * Simulates the timestep for the capsule.
 * @param timestep The step length in ms.
 * @param capsule  The capsule, that is the projectile in the world.
 */
void ProjectileShooting::step( int timestep, BodyProjectile &capsule )
{

	const Body *target;
	Vector targetVector, velocity, firingVelocity;
	
	this->timeElapsed += timestep;
	
	if ( this->timeElapsed >= this->shotDelay ) {
		
		target = this->selectTarget( capsule );
		
		if ( target != NULL ) {
			
			targetVector.set(
				capsule.getLocation().getDistanceX( target->getLocation().getX() ),
				capsule.getLocation().getDistanceY( target->getLocation().getY() ) );
			                  
			velocity = capsule.getVelocity();

			Vector velocityTargetPerpendicularComponent;
			Vector velocityTargetParallelComponent;
		
			//Velocity's parallel component to target.
			velocity.getProjectVector( velocityTargetParallelComponent,
			                           targetVector );
			//Nopeuden kohdetta vastaan kohtisuora komponentti.
			//Velocity's perpendicular component to target.
			velocityTargetPerpendicularComponent.set(
				velocity.getX() - velocityTargetParallelComponent.getX(),
				velocity.getY() - velocityTargetParallelComponent.getY() );
		
			firingVelocity -= velocityTargetPerpendicularComponent;
			float perpendicularLength =
				velocityTargetPerpendicularComponent.getLength();   
				               
			//Shoot only if undesired component's can be eliminated and so the
			//projectile should fly exactlyt to target (if gravity's ignored).                 
			if ( perpendicularLength < this->shotVelocity ) {
				//Shoot.
				targetVector.scale( sqrt( (this->shotVelocity * this->shotVelocity)
					                          - (perpendicularLength
					                             * perpendicularLength) )
				                    / targetVector.getLength() );
				                    
				firingVelocity += targetVector;
				this->timeElapsed = 0;
				
				Projectile *model = this->ammunition.getCopy();
				model->setShooter( this->getShooter() );
				
				BodyProjectile *newProjectile =
					new BodyProjectile( capsule.getWorld(),
					                    capsule.getLocation().getX(),
					                    capsule.getLocation().getY(), *model );	
		
				velocity += firingVelocity;
				
				newProjectile->setVelocity( velocity.getX(), velocity.getY() );
				newProjectile->setActionFlag( capsule.getActionFlag() );
				capsule.getWorld().addBody( *newProjectile );
				capsule.getWorld().playSound( model->getSound() );
				
				this->shotsFired++;
				
				if ( this->shotsFired >= this->shotCount ) {
					this->explode( capsule, capsule.getLocation(),
					               &capsule.getVelocity() );
					capsule.destroy();
				}
			
			}
			
		}
		
	}	
	
	Projectile::step( timestep, capsule );
	
}


/**
 * Selects a new target. Target is the closest cannon not owned by the
 * owner.
 * @param capsule The capsule.
 * @return Selected target.
 */
const Body* ProjectileShooting::selectTarget( const BodyProjectile &capsule )
{
	
	Body *body;
	BodyCannon *cannon, *target = NULL;
	int i;
	float distance, shortestDistance = -1;
	
	for ( i = 0; ( body = capsule.getWorld().getBody( i ) ) != NULL; i++ ) {
		
		cannon = dynamic_cast<BodyCannon*>(body);
		if ( cannon && &cannon->getOwner() != this->getShooter()
		     && !cannon->isRuined() )
		{
			
			distance =
				capsule.getLocation().getDistance( cannon->getLocation().getX(),
				                                  cannon->getLocation().getY() );
				                                  
			if ( distance < shortestDistance || shortestDistance < 0 ) {
				
				shortestDistance = distance;
				target = cannon;
				
			}
			
		}
		
	}
		
	return target;
	
}

/**
 * Forms a string to describe the damage of the projectile.
 * @param text String to store the damage description.
 */
void ProjectileShooting::getDamageText( std::string &text ) const
{
	
	char buffer[80];
	std::string damage;
	this->ammunition.getDamageText( damage );
	sprintf( buffer, "%s/shot", damage.c_str() );
	text = buffer;
	
}


