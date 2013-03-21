#include <iostream>
#include "Sprite.h"

/**
 * Constructor. You should call create() or setBitmapIndex() later.
 */
Sprite::Sprite() {
	this->surface = NULL;
	this->bitmapIndex = -1;
	
	phase = 0;
	angle = 0;
	previousAngle = -1;
}

/**
 * Constructor that makes the Sprite use common game graphics.
 */
Sprite::Sprite(int bitmapIndex) {
	this->surface = NULL;
	this->bitmapIndex = bitmapIndex;
	
	phase = 0;
	angle = 0;
	previousAngle = -1;
}

/**
 * Constructor that creates an empty surface of size (w x h).
 */
Sprite::Sprite(int w, int h) {
	this->surface = NULL;
	this->bitmapIndex = -1;
	
	create(w, h);
	
	phase = 0;
	angle = 0;
	previousAngle = -1;
}

/**
 * Destructor
 */
Sprite::~Sprite() {
	if (this->surface)
		SDL_FreeSurface(this->surface);
}

/**
 * Creates an empty surface of size (w x h). If the Sprite was using common
 * game graphics, it forgets about it now and starts using it's own surface.
 */
void Sprite::create(int w, int h) {
	//Free the old surface
	if (this->surface)
		SDL_FreeSurface(this->surface);
		
	//Create a new surface
	SDL_Surface *tempBitmap;
	tempBitmap = SDL_CreateRGBSurface(SDL_SRCCOLORKEY, w, h, 32,
	                                  255, 0, 255, 0);
	
	//Set transparency
	SDL_SetColorKey(tempBitmap, SDL_SRCCOLORKEY | SDL_RLEACCEL, 
	                SDL_MapRGB(tempBitmap->format, 255, 0, 255)); 
	
	//Convert colors to speed up blitting
	this->surface = SDL_DisplayFormat(tempBitmap);
	SDL_FreeSurface(tempBitmap);
	
	if (this->surface == NULL)
		return;
	
	SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format,
	             255, 0, 255));
}

/**
 * Makes the sprite use common game graphics. If the sprite has it's own
 * surface, it is deleted now.
 * @param bitmapIndex
 */
void Sprite::setBitmapIndex(int bitmapIndex) {
	this->bitmapIndex = bitmapIndex;
	
	//Free the old surface
	if (this->surface) {
		SDL_FreeSurface(this->surface);
		this->surface = NULL;
	}
}

/**
 * Sets phase of animation. [0, 1] or [0, inf] (looping)
 */
void Sprite::setPhase(float phase) {
	this->phase = phase;
}

/**
 * Sets orientation of Sprite. You have to use drawRotated to see the
 * effect. The actual rotation (which is slow) takes place in drawRotated
 * and only if the angle has changed. If you call setAngle and drawRotated
 * many times with the same angle, no re-rotation is done.
 * @param angle radians, ccw, 0 = east
 */
void Sprite::setAngle(float angle) {
	this->angle = angle;
}

/**
 * Returns width of the sprite in pixels if the sprite has its own surface.
 * Sprite doesn't have direct access to graphics so it can't give dimensions
 * of common pictures.
 * @return -1 if the sprite doesn't have it's own surface
 */
int Sprite::getWidth() {
	if (this->surface) {
		return this->surface->w;
	} else {
		return -1;
	}
}

/**
 * Returns width of the sprite in pixels if the sprite has its own surface.
 * @return -1 if the sprite doesn't have it's own surface
 */
int Sprite::getHeight() {
	if (this->surface) {
		return this->surface->h;
	} else {
		return -1;
	}
}

/**
 * Draws the sprite on screen. World coordinates.
 */
void Sprite::draw(Graphics &graphics, const Coordinates &location) {
	if (this->surface != NULL) {
		graphics.drawBitmap(this->surface, location);
	}
	else if (this->bitmapIndex >= 0) {
		graphics.drawAnimated(this->bitmapIndex, location, this->phase);
	}
}

/**
 * Draws the sprite on screen. Screen coordinates.
 */
void Sprite::draw(Graphics &graphics, int x, int y) {
	if (this->surface != NULL) {
		graphics.drawBitmap(this->surface, x, y);
	} else if (this->bitmapIndex >= 0) {
		graphics.drawSprite(this->bitmapIndex, x, y);
	}
}

/**
 * Draws a rotated bitmap on screen. Angle can be set with setAngle(). For
 * larger bitmaps this can be a rather slow operation. If angle has not
 * changed, no re-rotation is done. Only rotation of common game graphics
 * is supported, i.e. you set the source bitmap with setBitmapIndex().
 */
void Sprite::drawRotated(Graphics &graphics, const Coordinates &location) {
	if (this->angle != this->previousAngle) {
		rotate(graphics, this->angle);
		this->previousAngle = this->angle;
	}
	
	graphics.drawBitmap(this->surface, location);
}

/**
 * Takes a sprite from common game graphics, rotates it and stores the
 * result on a surface. Source sprite is set with with setBitamapIndex()
 * or constructor. 
 * @param angle angle in radians, ccw, 0 = east
 */
void Sprite::rotate(Graphics &graphics, float angle) {
	const SDL_Surface *source;
	
	source = graphics.getSurface(this->bitmapIndex);
	if (source == NULL)
		return;
	
	//Reset surface
	create(source->w, source->h);
	
	//Update picture
	graphics.drawRotated(source, this->surface, angle);
}
