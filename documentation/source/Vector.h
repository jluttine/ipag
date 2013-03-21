
#ifndef _VECTOR_H_
#define _VECTOR_H_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


/**
 * Author: Jaakko Luttinen
 * Vector is a class for 2D vectors.
 */

class Vector
{
	
public:

	/**
	 * Constructs a new vector with given components.
	 * @param x X component.
	 * @param y Y component.
	 */
	Vector( float x = 0, float y = 0 )  { this->set( x, y ); };
	
	/**
	 * Constructs a new vector from given vector.
	 * @param vect The vector to copy.
	 */	
	Vector( const Vector &vect )  { this->set( vect.x, vect.y ); };
	
	/**
	 * Returns the x component.
	 * @return X component.
	 */
	inline float getX() const  { return this->x; };
	
	/**
	 * Returns the y component.
	 * @return Y component.
	 */
	inline float getY() const  { return this->y; };

	/**
	 * Returns the angle in range 0-2Pi.
	 * @return The angle.
	 */
	float getAngle() const;
	
	/**
	 * Returns the length of the vector.
	 * @return Length of the vector.
	 */
	float getLength() const;
	
	/**
	 * Forms a unit vector.
	 * @param unitVector Vector to modify.
	 */
	void getUnitVector( Vector &unitVector ) const;
	
	/**
	 * Projects the vector to base vector and stores the result to result
	 * vector.
	 * @param result The vector to store the result.
	 * @param base   The vector to use as a base.
	 */
	void getProjectVector( Vector &result, const Vector &base ) const;
	
	/**
	 * Returns dot product between the vectors.
	 * @param vect Other operand.
	 * @return Dot product.
	 */
	float getDotProduct( const Vector &vect ) const;
	
	/**
	 * Returns scalar cross product.
	 * @param vect Other operand.
	 * @return Cross product.
	 */
	float getCrossProduct( const Vector &vect ) const;
	
	/**
	 * Sets the components.
	 * @param x X component.
	 * @param y Y component.
	 */
	void set( float x, float y );
	
	/**
	 * Adds the components.
	 * @param dx X component to add.
	 * @param dy Y component to add.
	 */
	void add( float dx, float dy );
	
	/**
	 * Adds the given vector.
	 * @param vect Vector to add.
	 */
	void add( const Vector &vect );
	
	/**
	 * Scales the vector.
	 * @param scalar The scalar.
	 */
	void scale( float scalar );
	
	/**
	 * Rotates the vector by given angle.
	 * @param angle Rotation angle.
	 */
	void rotate( float angle );

	/**
	 * Assigns the vector.
	 * @param vect Vector to copy.
	 * @return Result vector.
	 */	
	Vector& operator=( const Vector &vect );
	
	/**
	 * Adds the given vector.
	 * @param vect Vector to add.
	 * @return Result vector.
	 */
	Vector& operator+=( const Vector &vect );
	
	/**
	 * Subtracts the given vector.
	 * @param vect Vector to subtract.
	 * @return Result vector.
	 */
	Vector& operator-=( const Vector &vect );
	
	/**
	 * Scales the vector.
	 * @param scalar The scalar.
	 */
	Vector& operator*=( float scalar );
	
private:

	/**
	 * X component.
	 */
	float x;
	
	/**
	 * Y component.
	 */
	float y;
	
};

#endif //_VECTOR_H_
