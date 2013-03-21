
#include <math.h>
#include "Angle.h"
#include "ProjectileSeeking.h"

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
 * @param timeToTarget   Time to activate.
 * @param acceleration   The acceleration of steering.
 */
ProjectileSeeking::ProjectileSeeking( const string &name,
                                      const string &description,
                                      int price, int spriteIndex,
                                      int soundIndex,
                                      BodyExplosion::EType explosionIndex,
                                      float radius, float mass,
                                      float damage, float damageRadius,
                                      int timeToTarget, float acceleration )
	: Projectile( name, description, price, spriteIndex, soundIndex,
	              explosionIndex, radius, mass, damage, damageRadius )
{
	
	this->target = NULL;
	this->indexTargetingTime =
		this->parameters.addParameter( ParameterList::TIME, "Activate", 0, 100,
		                               101, false );
	this->parameters.setParameterValue( this->indexTargetingTime,
	                                    timeToTarget );
	this->acceleration = acceleration;
	
}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileSeeking::ProjectileSeeking( const ProjectileSeeking &copy )
	: Projectile( copy )
{
	
	this->target = NULL;
	this->indexTargetingTime = copy.indexTargetingTime;
	this->acceleration = copy.acceleration;
	
}

/**
 * Simulates the timestep for the capsule. If the targeting time has
 * elapsed a target will be selected and the projectile directed
 * straightly towards it.
 * @param timestep The step length in ms.
 * @param capsule  The capsule, that is the projectile in the world.
 */
void ProjectileSeeking::step( int timestep, BodyProjectile &capsule )
{
	
	//Prevent division by zero. And zero timestep does nothing anyway.
	if ( timestep == 0 )
		return;
	
	//If activation time has elapsed look for closest target.
	if ( this->timeLived
	     >= this->parameters.getParameterValue( this->indexTargetingTime ) )
	{
		this->selectTarget( capsule );
	}
	
	if ( this->target != NULL ) {
		Vector velocity = capsule.getVelocity();
		Vector targetVector( capsule.getLocation().getDistanceX(
		                       this->target->getLocation().getX() ),
		                     capsule.getLocation().getDistanceY(
		                       this->target->getLocation().getY() ) );
		                       
		Vector velocityTargetPerpendicularComponent;
		Vector velocityTargetParallelComponent;
		float correctingVelocity = timestep * this->acceleration;
		
		//Component of the velocity parallel to vector to target.
		velocity.getProjectVector( velocityTargetParallelComponent,
		                           targetVector );
		//Component of the velocity perpendicular to vector to target.
		velocityTargetPerpendicularComponent.set(
			velocity.getX() - velocityTargetParallelComponent.getX(),
			velocity.getY() - velocityTargetParallelComponent.getY() );

		Vector velocityEliminatingComponent; 
	
		//Perpendicular component should be eliminated.
		velocityEliminatingComponent -= velocityTargetPerpendicularComponent;
		
		//If moving away, should eliminate that component too.
		float angleParallel =
			velocityTargetParallelComponent.getAngle() - targetVector.getAngle();
			
		if ( !Angle::isBetween( angleParallel, 2 * M_PI - 0.3, 0.3 ) ) {
			velocityEliminatingComponent -= velocityTargetParallelComponent;
		}
		
		float eliminatingLength = velocityEliminatingComponent.getLength();
		if ( eliminatingLength > correctingVelocity ) {
			//Use all resources to eliminate undesired components.
			velocityEliminatingComponent.scale( correctingVelocity
			                                    / eliminatingLength );
		}
		else {
			//Undesired components can be eliminated totally. Let's accelerate
			//towards target with the rest "power".
			velocityEliminatingComponent = velocityTargetPerpendicularComponent;
			velocityEliminatingComponent.scale( -1 );
			float perpendicularLength =
				velocityTargetPerpendicularComponent.getLength();
			targetVector.scale( sqrt( correctingVelocity * correctingVelocity
			                          - perpendicularLength * perpendicularLength)
			                    / targetVector.getLength() );
			velocityEliminatingComponent += targetVector;
		}
	
		velocity += velocityEliminatingComponent;
		capsule.setVelocity( velocity.getX(), velocity.getY() );

	}
	
	Projectile::step( timestep, capsule );
	
}

/**
 * Selects a new target. Target is the closest not ruined cannon that is
 * not owned by the shooter.
 * @param capsule The capsule.
 */
void ProjectileSeeking::selectTarget( const BodyProjectile &capsule )
{
	
	Body *body;
	BodyCannon *cannon;
	int i;
	float distance, shortestDistance = -1;
	
	for ( i = 0; ( body = capsule.getWorld().getBody( i ) ) != NULL; i++ ) {
		
		cannon = dynamic_cast<BodyCannon*>(body);
		if ( cannon && &cannon->getOwner() != this->getShooter()
		     && !cannon->isRuined() ) {
			
			distance =
				capsule.getLocation().getDistance( cannon->getLocation().getX(),
				                                  cannon->getLocation().getY() );
				                                  
			if ( distance < shortestDistance || shortestDistance < 0 ) {
				
				shortestDistance = distance;
				this->target = cannon;
				
			}
			
		}
		
	}
		
}

