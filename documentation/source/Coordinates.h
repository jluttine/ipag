
#ifndef _COORDINATES_H_
#define _COORDINATES_H_

#include <iostream>
#include "CoordinateSystem.h"

/**
 * Author: Jaakko Luttinen
 * Coordinates is a class for a point in a continuous coordinate system.
 * It means that every x is between 0-width and y is between 0-height, where
 * width and height are the width and height of the coordinate system.
 * Continuity means that x=x+n*width and y=y+n*height, where n is an
 * integer. In order to be able to use this class correctly you must
 * understand some of the effects of continuity. For example, the distance
 * from (x1,y1) to (x2,y2) cannot be determined, because distance has
 * endlessly options. But we can determine shortest distance. Also, x0 is
 * always between x1 and x2 (if x1 is not equal to x2), but we can ask is in
 * the range from x1 to positive direction until x2. Class will return only
 * coordinate values in the range 0 - axis length. It will also translate
 * all parameters into that range, so any value as a parameter is valid.
 */
class Coordinates
{
	
public:

	/**
	 * Constructs a new point (x,y) in given coordinate system.
	 * @param coordSystem Coordinate system for the point.
	 * @param x           X-coordinate.
	 * @param y           Y-coordinate.
	 */
	Coordinates(const CoordinateSystem &coordSystem, float x=0, float y=0);
	
	/**
	 * Constructs a new point to same coordinate system and same coordinates
	 * as coords.
	 * @param coords The coordinates to use as a copy.
	 */
	Coordinates( const Coordinates &coords );
	
	/**
	 * Returns the coordinate system of the point.
	 * @return Coordinate system of the point.
	 */
	inline const CoordinateSystem&	getCoordinateSystem() const
		{ return *this->system; };
	
	/**
	 * Returns the x-coordinate of the point.
	 * @return X-coordinate of the point.
	 */
	inline float getX() const  { return this->x; };
	
	/**
	 * Returns the y-coordinate of the point.
	 * @return Y-coordinate of the point.
	 */
	inline float getY() const  { return this->y; };
	
	/**
	 * Sets the coordinates of the point.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 */
	void set( float x, float y );
	
	/**
	 * Adds the values to coordinates.
	 * @param dx Addition to x-coordinate.
	 * @param dy Addition to y-coordinate.
	 */
	void add( float dx, float dy );

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
	float getDistanceX( float x, int direction = 0 ) const;

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
	float getDistanceY( float y, int direction = 0 ) const;
	
	/**
	 * Returns the shortest distance between the coordinates.
	 * @param x X-coordinate of the point.
	 * @param y Y-coordinate of the point.
	 */
	float getDistance( float x, float y ) const;
	
	/**
	 * Tells relative coordinates. It means resulting point will be in the
	 * same coordinate system as this and its coordinates are (x+addX,y+addY).
	 * @param result Object to store the resulting coordinates.
	 * @param addX   Addition in x-component.
	 * @param addY   Addition in y-component.
	 */
	void getRelativeCoordinates( Coordinates &result,
	                             float addX, float addY) const;
	
	/**
	 * Tells whether the coordinates have same coordinate system. Two points
	 * are comparable only if they are in the same coordinate system.
	 * @param coords Point, whose coordinate system is compared.
	 */
	inline bool isSameSystem( const Coordinates &coords ) const
		{ return &this->system == &coords.system; };
		
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
	bool isBetweenX( float start, float end ) const;

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
	bool isBetweenY( float start, float end ) const;
	
	/**
	 * Prints the point in format "(x, y)" to os.
	 * @param os       Output stream.
	 * @param location The coordinates to print.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<( std::ostream &os,
	                                 const Coordinates &location );
	
protected:
	
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
	static float getCoordinateDistance( float from, float to, int max,
	                                    int direction );

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
	static bool isBetweenCoordinates( float coord, float start, float end );
	
	/**
	 * Fixes the coord to range 0-max. For example, if coord=-1, coord will be
	 * fixed to coord=max-1. That is, coord=coord+n*max, where n is an integer
	 * so that coord will be in the range 0-max.
	 * @param coord The coordinate to fix.
	 * @param max   The length of the axis.
	 */
	static void fixCoordinate( float &coord, int max );

	/**
	 * Fixes both coordinates to base range (0 - axis length).
	 */
	void fix();
	
private:

	/**
	 * The coordinate system for the point. Class does NOT free the memory!
	 */
	const CoordinateSystem *system;
	
	/**
	 * The coordinates.
	 */
	float x, y;
	
};

#endif //_COORDINATES_H_
