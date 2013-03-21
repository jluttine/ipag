
#ifndef _ANGLE_H_
#define _ANGLE_H_

/**
 * Class Angle.
 * Represents an angle and offers some functions to handle angles.
 * Angle fixes itself so that it is always inbetween 0 and 2*Pi
 * @author Lasse Hakulinen
 */

class Angle {

public:

	/**
	 * Constructor.
	 * @param radian - the width of the angle in radian
	 */
	Angle(float radian = 0 );
	
	/**
	 * Destructor.
	 */
	~Angle();

	/**
	 * Fixes the angle so that it is between 0 and 2*Pi
	 * @param &angle - reference to the angle to fix
	 */
	static void fix(float &angle);
	
	/**
	 * Tells if an angle is between two points.
	 * @param angle - angle to check
	 * @param start - starting angle
	 * @param end - finishing angle
	 * @return true if angle is between start and end
	 */
	static bool isBetween(float angle, float start, float end);
	
	/**
	 * Tells if the angle is between two points.
	 * @param start - starting angle
	 * @param end - finishing angle
	 * @return true if the angle is between start and end
	 */
	bool isBetween(float start, float end);
			
	/**
	 * @return the value of angle
	 */
	inline float getAngle() const { return this->radian; };
	
	/**
	 * Increases the value of angle.
	 * @param angle - value of how much the angle is increased.
	 */
	void add(float angle);
	
	/**
	 * Sets the value of the angle.
	 * @param angle - the value which the angle is set to
	 */
	void set(float angle);	
	
	/**
	 * Gets the distance between the angle and a given angle.
	 * @param angle - the other angle
	 * @param direction - direction where the distance is calculated
	 * if direction > 0 = from the angle to positive direction
	 * if direction < 0 = from the angle to negative direction
	 * if direction = 0 = shortest distance
	 */
	float getDistance(float angle, int direction = 0) const;

private:

	#ifndef M_PI
	#define M_PI 3.14159265358979323846
	#endif
	
	float radian;
	
};

#endif //_ANGLE_H_

