
#include "BodyProjectile.h"
#include "ProjectileSplitting.h"

/**
 * Constructs a new projectile.
 * @param name                Name of the projectile.
 * @param description         Description of the projectile.
 * @param price               Price of the projectile.
 * @param spriteIndex         Index of the sprite.
 * @param soundIndex          Index of the firing sound.
 * @param explosionIndex      Index of the explosion type.
 * @param radius              Radius of the projectile.
 * @param mass                Mass of the projectile.
 * @param damage              Maximum damage of the projectile.
 * @param damageRadius        Radius of the damage.
 * @param splittingProjectile Projectile template for splitting
 *                            projectiles.
 * @param splitCount          Number of splitting projectiles.
 * @param splitAngle          Angle of split.
 * @param timeToSplit         Time to split.
 * @param splittingVelocity   Velocity boost for splitting projectiles.
 */
ProjectileSplitting
	::ProjectileSplitting( const string &name, const string &description,
                         int price, int spriteIndex, int soundIndex,
                         BodyExplosion::EType explosionIndex, float radius,
                         float mass, float damage, float damageRadius,
                         Projectile &splittingProjectile, int splitCount,
                         float splitAngle, int timeToSplit,
                         float splittingVelocity )
	: Projectile( name, description, price, spriteIndex, soundIndex,
	              explosionIndex, radius, mass, damage, damageRadius ),
	  splittingProjectile( splittingProjectile )
{
	
	Angle::fix( splitAngle );
	this->splitCount = splitCount;
	this->splittingVelocity = splittingVelocity;
	this->indexSplittingTime =
		this->parameters.addParameter( ParameterList::TIME, "Split time", 0,
		                               100, 50, false );
	this->indexSplittingAngle =
		this->parameters.addParameter( ParameterList::ANGLE, "Split angle", 10,
		                               10, 36, false );
	this->parameters.setParameterValue(this->indexSplittingTime, timeToSplit);
	this->parameters.setParameterValue( this->indexSplittingAngle,
	                                    ( int )( 180 * splitAngle / M_PI ) );

}

/**
 * Constructs a projectile with same properties.
 * @param copy The projectile to use as a copy.
 */
ProjectileSplitting::ProjectileSplitting( const ProjectileSplitting &copy )
	: Projectile( copy ), splittingProjectile( copy.splittingProjectile )
{
	
	this->splitCount = copy.splitCount;
	this->splittingVelocity = copy.splittingVelocity;
	this->indexSplittingTime = copy.indexSplittingTime;
	this->indexSplittingAngle = copy.indexSplittingAngle;
	
}

/**
 * Simulates the timestep for the capsule.
 * @param timestep The step length in ms.
 * @param capsule  The capsule, that is the projectile in the world.
 */
void ProjectileSplitting::step( int timestep, BodyProjectile &capsule )
{
	
	Vector velocity( capsule.getVelocity() );
	float splitAngle =
		M_PI * this->parameters.getParameterValue( this->indexSplittingAngle )
		/ 180.0;
		
	float stepAngle =  splitAngle / this->splitCount;
	
	velocity.scale( this->splittingVelocity / velocity.getLength() );
	velocity.rotate( ( stepAngle - splitAngle ) / 2 );
	
	if ( this->timeLived
	     >= this->parameters.getParameterValue( this->indexSplittingTime ) )
	{
		
		for ( int i = 0; i < this->splitCount; i++ ) {
				
			Projectile *model = this->splittingProjectile.getCopy();
			model->setShooter( this->getShooter() );
			
			BodyProjectile *newProjectile =
				new BodyProjectile( capsule.getWorld(),
				                    capsule.getLocation().getX(),
			                      capsule.getLocation().getY(), *model );

			newProjectile->setVelocity(
				capsule.getVelocity().getX() + velocity.getX(),
				capsule.getVelocity().getY() + velocity.getY() );
				
			velocity.rotate( stepAngle );

			newProjectile->setActionFlag( capsule.getActionFlag() );
			capsule.getWorld().addBody( *newProjectile );
			
		}
		
		capsule.destroy();
		
	}
	
	Projectile::step( timestep, capsule );
	
}

/**
 * Forms a string to describe the damage of the projectile.
 * @param text String to store the damage description.
 */
void ProjectileSplitting::getDamageText( std::string &text ) const
{
	
	char buffer[80];
	std::string damage;
	this->splittingProjectile.getDamageText( damage );
	sprintf( buffer, "%dx%s", this->splitCount, damage.c_str() );
	text = buffer;
	
}

