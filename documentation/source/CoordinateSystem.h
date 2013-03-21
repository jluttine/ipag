
#ifndef _COORDINATESYSTEM_H_
#define _COORDINATESYSTEM_H_

/**
 * Author: Jaakko Luttinen
 * CoordinateSystem is a class for a coordinate system in a continuous
 * space. CoordinateSystem has constant width and height.
 */
class CoordinateSystem
{
	
public:

	/**
	 * Constructs a coordinate system with given width and height.
	 * @param width  The width of the coordinate system.
	 * @param height The height of the coordinate system.
	 */
	CoordinateSystem( int width, int height );

	/**
	 * Returns the width of the coordinate system.
	 * @return The width of the coordinate system.
	 */
	int getWidth() const  { return this->width; };

	/**
	 * Returns the height of the coordinate system.
	 * @return The height of the coordinate system.
	 */
	int getHeight() const  { return this->height; };
	
private:
	
	/**
	 * The length of x- and y-axises.
	 */
	const int width, height;
	
};

#endif //_COORDINATESYSTEM_H_
