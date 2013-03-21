
#include <math.h>
#include <iostream>
#include "Angle.h"

/**
 * Class Angle.
 * Represents an angle and offers some functions to handle angles.
 * Angle fixes itself so that it is always inbetween 0 and 2*Pi
 * @author Lasse Hakulinen
 */


/**
 * Constructor.
 * @param radian - the width of the angle in radian
 */
Angle::Angle(float radian){

	this->set(radian);
}

/**
 * Destructor.
 */
Angle::~Angle(){
}

/**
 * Fixes the angle so that it is between 0 and 2*Pi
 * @param &angle - reference to the angle to fix
 */
void Angle::fix(float &angle) {	

	angle = fmod(angle, 2*M_PI);	

	if (angle < 0){
		angle += 2 * M_PI;
	}	
}

/**
 * Increases the value of angle.
 * @param angle - value of how much the angle is increased.
 */
void Angle::add(float angle){

	this->radian += angle;
	Angle::fix(this->radian);

}

/**
 * Sets the value of the angle.
 * @param angle - the value which the angle is set to
 */
void Angle::set(float angle){

	this->radian = angle;
	Angle::fix(this->radian);

}

/**
 * Tells if an angle is between two points.
 * @param angle - angle to check
 * @param start - starting angle
 * @param end - finishing angle
 * @return true if angle is between start and end
 */
bool Angle::isBetween(float angle, float start, float end){

	Angle::fix(angle);
	Angle::fix(start);
	Angle::fix(end);
	
	if (start == end){
		return angle == start;
	}
	else if (start < end){
		return angle >= start && angle <= end;
	}
	else {
		return angle >= start || angle <= end;
	}

}

/**
 * Tells if the angle is between two points.
 * @param start - starting angle
 * @param end - finishing angle
 * @return true if the angle is between start and end
 */
bool Angle::isBetween(float start, float end){
	
	return Angle::isBetween(this->radian, start, end);
}

/**
 * Gets the distance between the angle and a given angle.
 * @param angle - the other angle
 * @param direction - direction where the distance is calculated
 * if direction > 0 = from the angle to positive direction
 * if direction < 0 = from the angle to negative direction
 * if direction = 0 = shortest distance
 */
float Angle::getDistance(float angle, int direction) const{

	float dist1, dist2;

	Angle::fix(angle);	
	dist1 = angle - this->radian;
	Angle::fix(dist1);	
	dist2 = (2 * M_PI) - dist1;

	if (direction > 0){
		return dist1;
	}
	else if (direction < 0){
		return dist2;
	}
	else if (dist1 < dist2){
		return dist1;
	}
	else {
		return dist2;
	}	
}
