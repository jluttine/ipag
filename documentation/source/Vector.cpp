
#include <math.h>
#include "Vector.h"

/**
 * Returns the angle in range 0-2Pi.
 * @return The angle.
 */
float Vector::getAngle() const
{
	
	float angle = atan2( this->y, this->x );
	
	if ( angle < .0 )
		angle += 2 * M_PI;
		
	return angle;
	
}

/**
 * Returns the length of the vector.
 * @return Length of the vector.
 */
float Vector::getLength() const
{
	
	return sqrt( this->x * this->x + this->y * this->y );
	
}

/**
 * Forms a unit vector.
 * @param unitVector Vector to modify.
 */
void Vector::getUnitVector( Vector &unitVector ) const
{

	float length = this->getLength();
	unitVector.set( this->x / length, this->y / length );	
	
}

/**
 * Projects the vector to base vector and stores the result to result
 * vector.
 * @param result The vector to store the result.
 * @param base   The vector to use as a base.
 */
void Vector::getProjectVector( Vector &result, const Vector &base ) const
{
	
	float scalar = base.getDotProduct( *this ) / base.getDotProduct( base );
	result.set( base.x * scalar, base.y * scalar );
	
}

/**
 * Returns dot product between the vectors.
 * @param vect Other operand.
 * @return Dot product.
 */
float Vector::getDotProduct( const Vector &vect ) const
{
	
	return this->x * vect.x + this->y * vect.y;
	
}

/**
 * Returns scalar cross product.
 * @param vect Other operand.
 * @return Cross product.
 */
float Vector::getCrossProduct( const Vector &vect ) const
{

	//Because Vector is for vectors in a plane, result must be scalar.
	float result = this->x * vect.y - this->y * vect.x;
	return result < 0 ? -result : result;
	
}
	
/**
 * Sets the components.
 * @param x X component.
 * @param y Y component.
 */
void Vector::set( float x, float y )
{
	
	this->x = x;
	this->y = y;
	
}

/**
 * Adds the components.
 * @param dx X component to add.
 * @param dy Y component to add.
 */
void Vector::add( float dx, float dy )
{
	
	this->x += dx;
	this->y += dy;
	
}

/**
 * Adds the given vector.
 * @param vect Vector to add.
 */
void Vector::add( const Vector &vect )
{
	
	this->x += vect.x;
	this->y += vect.y;
	
}

/**
 * Scales the vector.
 * @param scalar The scalar.
 */
void Vector::scale( float scalar )
{
	
	this->x *= scalar;
	this->y *= scalar;
	
}

/**
 * Rotates the vector by given angle.
 * @param angle Rotation angle.
 */
void Vector::rotate( float angle )
{
	
	float oldX = this->x;
	float oldY = this->y;
	float cosin = cos( angle );
	float sini = sin( angle );
	this->x = cosin * oldX - sini * oldY;
	this->y = sini * oldX + cosin * oldY;
	
}

/**
 * Assigns the vector.
 * @param vect Vector to copy.
 * @return Result vector.
 */	
Vector& Vector::operator=(const Vector &vect)
{
	
	this->set( vect.x, vect.y );
	return *this;
	
}

/**
 * Adds the given vector.
 * @param vect Vector to add.
 * @return Result vector.
 */
Vector& Vector::operator+=( const Vector &vect )
{

	this->add( vect );
	return *this;

}

/**
 * Subtracts the given vector.
 * @param vect Vector to subtract.
 * @return Result vector.
 */
Vector& Vector::operator-=( const Vector &vect )
{
	
	this->add( -vect.x, -vect.y );
	return *this;
	
}

/**
 * Scales the vector.
 * @param scalar The scalar.
 */
Vector& Vector::operator*=( float scalar )
{
	
	this->scale( scalar );
	return *this;
	
}
