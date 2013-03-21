
#include <math.h>

#include "Coordinates.h"

/**
 * Constructs a new point (x,y) in given coordinate system.
 * @param coordSystem Coordinate system for the point.
 * @param x           X-coordinate.
 * @param y           Y-coordinate.
 */
Coordinates::Coordinates( const CoordinateSystem &coordSystem, float x,
                          float y )
{

	this->system = &coordSystem;
	this->set( x, y );
	
}

/**
 * Constructs a new point to same coordinate system and same coordinates
 * as coords.
 * @param coords The coordinates to use as a copy.
 */
Coordinates::Coordinates( const Coordinates &coords )
{
	
	this->system = coords.system;
	this->set( coords.x, coords.y );
	
}

/**
 * Sets the coordinates of the point.
 * @param x X-coordinate.
 * @param y Y-coordinate.
 */
void Coordinates::set( float x, float y )
{

	this->x = x;
	this->y = y;
	this->fix();
	
}

/**
 * Adds the values to coordinates.
 * @param dx Addition to x-coordinate.
 * @param dy Addition to y-coordinate.
 */
void Coordinates::add( float x, float y )
{
	
	this->x += x;
	this->y += y;
	this->fix();
	
}

/**
 * Returns the shortest distance in x-axis to the given x-coordinate in
 * given direction. If direction < 0, negative direction is used. If
 * direction > 0, positive direction is used. If direction = 0, shortest
 * distance is returned. The sign of the return value tells the direction
 * also.
 * @param x         X-coordinate which the distance is being determined.
 * @param direction Tells which direction to use.
 * @return The distance in the axis. Note that the sign tells the
 *         direction.
 */
float Coordinates::getDistanceX( float x, int direction ) const
{
	
	Coordinates::fixCoordinate( x, this->system->getWidth() );
	return Coordinates::getCoordinateDistance( this->x, x,
	                                           this->system->getWidth(),
	                                           direction );
	
}

/**
 * Returns the shortest distance in y-axis to the given y-coordinate in
 * given direction. If direction < 0, negative direction is used. If
 * direction > 0, positive direction is used. If direction = 0, shortest
 * distance is returned. The sign of the return value tells the direction
 * also.
 * @param y         Y-coordinate which the distance is being determined.
 * @param direction Tells which direction to use.
 * @return The distance in the axis. Note that the sign tells the
 *         direction.
 */
float Coordinates::getDistanceY( float y, int direction ) const
{

	Coordinates::fixCoordinate( y, this->system->getHeight() );
	return Coordinates::getCoordinateDistance( this->y, y,
	                                           this->system->getHeight(),
	                                           direction );
	
}

/**
 * Returns the shortest distance between the coordinates.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 */
float Coordinates::getDistance( float x, float y ) const
{
	
	float distX = this->getDistanceX( x );
	float distY = this->getDistanceY( y );
	return sqrt( distX * distX + distY * distY );
	
}

/**
 * Tells relative coordinates. It means resulting point will be in the
 * same coordinate system as this and its coordinates are (x+addX,y+addY).
 * @param result Object to store the resulting coordinates.
 * @param addX   Addition in x-component.
 * @param addY   Addition in y-component.
 */
void Coordinates::getRelativeCoordinates( Coordinates &result, float addX,
                                          float addY ) const
{
	result.system = this->system;
	result.set( this->x + addX, this->y + addY );
}

/**
 * Tells whether the point is between start and end x-coordinates. The
 * range to positive direction from start to end. If start=end, then it
 * will tell whether the point's x-coordinate is equal to start=end. Note
 * that if start is not equal to end, then the point is either in range
 * start-end or end-start. Or possibly both, because the ending points are
 * included. Note also, that start and end are fixed to range 0 - axis
 * length.
 * @param start The starting point of the range.
 * @param end   The ending point of the range.
 */
bool Coordinates::isBetweenX( float start, float end ) const
{
	Coordinates::fixCoordinate( start, this->system->getWidth() );
	Coordinates::fixCoordinate( end, this->system->getWidth() );
	return isBetweenCoordinates( this->x, start, end );
}

/**
 * Tells whether the point is between start and end x-coordinates. The
 * range to positive direction from start to end. If start=end, then it
 * will tell whether the point's x-coordinate is equal to start=end. Note
 * that if start is not equal to end, then the point is either in range
 * start-end or end-start. Or possibly both, because the ending points are
 * included. Note also, that start and end are fixed to range 0 - axis
 * length.
 * @param start The starting point of the range.
 * @param end   The ending point of the range.
 */
bool Coordinates::isBetweenY( float start, float end ) const
{
	Coordinates::fixCoordinate( start, this->system->getHeight() );
	Coordinates::fixCoordinate( end, this->system->getHeight() );
	return isBetweenCoordinates( this->y, start, end );
}

/**
 * Prints the point in format "(x, y)" to os.
 * @param os       Output stream.
 * @param location The coordinates to print.
 * @return The output stream.
 */
std::ostream& operator<<( std::ostream &os, const Coordinates &location )
{
	
	os << "(" << location.x << ", " << location.y << ")";
	return os;
	
}

/**
 * Fixes both coordinates to base range (0 - axis length).
 */
void Coordinates::fix()
{
	Coordinates::fixCoordinate(this->x, this->system->getWidth());
	Coordinates::fixCoordinate(this->y, this->system->getHeight());
}

/**
 * Returns the shortest distance to given direction from from-coordinate
 * to to-coordinate in axis, whose length is max. If direction < 0,
 * negative direction is used. If direction > 0, positive direction is
 * used. If direction = 0, shortest direction is returned. The coordinate
 * values must be fixed! Sign of the return value tells direction.
 * @param from The coordinate from which the distance is determined.
 * @param to   The coordinate to which the distance is determined.
 * @param max  The length of the axis.
 * @param direction The direction.
 * @return The distance.
 */
float Coordinates::getCoordinateDistance( float from, float to, int max,
                                          int direction )
{

	float dist1 = to - from;
	float dist2 = dist1 + ( dist1 < 0 ? max : -max );
		
	if ( direction ) {
		
		if ( dist1 / direction >= 0 )
			return dist1;
			
		return dist2;
		
	}
	else {
			
		//Return the one with smaller absolute value.
		if ( ( dist1 < 0 ? -dist1 : dist1 ) < ( dist2 < 0 ? -dist2 : dist2 ) )
			return dist1;
			
		return dist2;

	}
		
}

/**
 * Tells whether the coord-coordinate is between start and end
 * coordinates. Ending points are included. If start=end, tells whether
 * coord=start=end. Range is to positive direction from start to end. All
 * coordinate values must be fixed!
 * @param coord The coordinate to check.
 * @param start The starting coordinate of the range.
 * @param end   The ending coordinate of the range.
 * @return True if coord is between start and end, false otherwise.
 */
bool Coordinates::isBetweenCoordinates( float coord, float start,
                                        float end )
{
	
	if ( start == end )
		return coord == start;
		
	if ( start < end )
		return ( coord >= start ) && ( coord <= end );
	else
		return ( coord >= start ) || ( coord <= end );
	
}

/**
 * Fixes the coord to range 0-max. For example, if coord=-1, coord will be
 * fixed to coord=max-1. That is, coord=coord+n*max, where n is an integer
 * so that coord will be in the range 0-max.
 * @param coord The coordinate to fix.
 * @param max   The length of the axis.
 */
void Coordinates::fixCoordinate( float &coord, int max )
{
	
	int div = ( int )( coord / max );
	coord -= div * max;
	
	if ( coord < 0 )
		coord += max;
	
}
