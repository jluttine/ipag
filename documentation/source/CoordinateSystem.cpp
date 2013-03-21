
#include <iostream>
#include "CoordinateSystem.h"

/**
 * Constructs a coordinate system with given width and height.
 * @param width  The width of the coordinate system.
 * @param height The height of the coordinate system.
 */
CoordinateSystem::CoordinateSystem( int width, int height )
	: width( width ), height( height )
{
	
	if ( width <= 0 || height <= 0 )
		fprintf( stderr,
		         "CoordinateSystem::CoordinateSystem: invalid axis length.\n" );
	
}
