#ifndef _SPRITE_H_ 
#define _SPRITE_H_ 

class Sprite;

#include <SDL/SDL.h>
#include "Graphics.h"
#include "Coordinates.h"

/**
 * Class Sprite is used to store unique game graphics. For example rotation
 * is such a slow operation that you don't want to do it for every frame but
 * to do it once and store the result.
 *
 * You can tell Sprite to use common game garphics in which case no extra
 * memory is consumed. However, it's usually easier to deal with Graphics
 * directly.
 *
 * @author Tapio Auvinen
 */

class Sprite {
public:
	
	/**
	 * Constructor. You should call create() or setBitmapIndex() later.
	 */
	Sprite();
	
	/**
	 * Constructor that makes the Sprite use common game graphics.
	 * @param spriteIndex indexes are defined in images.h
	 */
	Sprite(int spriteIndex);
	
	/**
	 * Constructor that creates an empty surface of size (w x h).
	 * @param width width in pixels
	 * @param width height in pixels
	 */
	Sprite(int w, int h);
	
	/**
	 * Destructor
	 */
	~Sprite();
	
	/**
	 * Creates an empty surface of size (w x h). If the Sprite was using
	 * common game graphics, it forgets about it now and starts using it's
	 * own surface.
	 * @param width width in pixels
	 * @param width height in pixels
	 */
	void create(int w, int h);
	
	/**
	 * Makes the Sprite use common game graphics. If the Sprite has it's
	 * own surface, it is deleted now.
	 * @param bitmapIndex indexes are defined in images.h
	 */
	void setBitmapIndex(int bitmapIndex);
	
	/**
	 * Sets phase of animation.
	 * @param phase [0, 1] or [0, inf] (looping)
	 */
	void setPhase(float phase);
	
	/**
	 * Sets the orientation of Sprite. You have to use drawRotated to see
	 * the effect. The actual rotation (which is slow) takes place in
	 * drawRotated and only if the angle has changed. If you call setAngle
	 * and drawRotated many times with the same angle, no re-rotation is
	 * done.
	 * @param angle radians, ccw, 0 = east
	 */
	void setAngle(float angle);
	
	/**
	 * Returns width of the sprite in pixels if the sprite has its own
	 * surface. Sprite doesn't have direct access to graphics so it can't
	 * give dimensions of common sprites.
	 * @return width in pixels, -1 if the sprite doesn't have it's own surface
	 */
	int getWidth();
	
	/**
	 * Returns width of the sprite in pixels if the sprite has its own
	 * surface.
	 * @return hight in pixels, -1 if the sprite doesn't have it's own surface
	 */
	int getHeight();
	
	/**
	 * Draws the sprite on screen. World coordinates.
	 * @param &graphics Reference to graphics
	 * @param location location of the object's center in the world
	 */
	void draw(Graphics &graphics, const Coordinates &location);
	
	/**
	 * Draws the sprite on screen. Screen coordinates.
	 * @param &graphics Reference to graphics
	 * @param x location of the object's upper-left corner, screen coordinates
	 * @param y location of the object's upper-left corner, screen coordinates
	 */
	void draw(Graphics &graphics, int x, int y);
	
	/**
	 * Draws a rotated bitmap on screen. Angle can be set with setAngle().
	 * For larger bitmaps this is a rather slow operation. If angle has
	 * not changed, no re-rotation is done. Only rotation of common game
	 * graphics is supported, i.e. you set the source bitmap with 
	 * setBitmapIndex().
	 * @param &graphics Reference to graphics
	 * @param location location of the object's center in the world
	 */
	void drawRotated(Graphics &graphics, const Coordinates &location);


private:
	SDL_Surface *surface;
	int bitmapIndex;  //Common game graphics index
	
	float phase;      //Phase of animation
	float angle;      //Orientation
	float previousAngle; //Previous orientation to prevent
	                     //unnecessary re-rotation
	
	/**
	 * Takes a sprite from common game graphics, rotates it and stores the
	 * result on a surface. Source sprite is set with with
	 * setBitamapIndex() or constructor. 
	 * @param angle angle in radians, ccw, 0 = east
	 */
	void rotate(Graphics &graphics, float angle);
};

#endif
