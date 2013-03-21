#include <iostream>
#include <fstream>
#include <math.h>
#include "Graphics.h"

//Number of stars
#define STARS  400

//Text properties
#define LINE_HEIGHT  18
#define CHAR_WIDTH   8

using namespace std;

/**
 * Constructor.
 */
Graphics::Graphics() {
	this->windowCenter = NULL;
	this->font = NULL;
	
	this->stars = NULL;
	this->starfieldCenterX = 0;
	this->starfieldCenterY = 0;
}

Graphics::~Graphics() {

	if (this->windowCenter)
		delete this->windowCenter;
	
	if (this->font)
		freeSurface(this->font);
		
	if (stars)
		delete [] stars;
	
	destroySprites();
}

/**
 * Initializes the graphics engine. Nothing must be drawn before this is
 * done. If this fails, you should quit.
 * @return true if successful. 
 */
bool Graphics::init(int resX, int resY, int bitDepth) {
	screen = SDL_SetVideoMode(resX, resY, bitDepth, SDL_ANYFORMAT | SDL_FULLSCREEN);
	
	//Windowd mode:
	//screen = SDL_SetVideoMode(resX, resY, bitDepth, SDL_ANYFORMAT);
	
	
	if (!screen) {
		cerr << "Failed to open screen: " << SDL_GetError() << endl;
		return false;
	}
	
	SDL_WM_SetCaption("IPAG", "IPAG"); 
	
	//Load font
	this->font = loadBitmap("data/font.bmp");
	
	//Load all game graphics
	if (!loadSprites()) {
		return false;
	}
	
	return true;
}

/**
 * Sets coordinate system so that grapchics becomes aware of the dimensions
 * of the world. This must be set before any game graphics is drawn.
 */
void Graphics::setCoordinateSystem(const CoordinateSystem &system) {
	if (this->windowCenter){
		delete this->windowCenter;
	}
	
	this->windowCenter = new Coordinates(system, 0, 0);
}

/**
 * Converts screen coordinates to world coordinates.
 */
Coordinates *Graphics::getWorldCoordinates(int x, int y) {
	float wx, wy;
	Coordinates *coords;
	
	wx = windowCenter->getX() - screen->w / 2 + x;
	wy = windowCenter->getY() - screen->h / 2 + y;
	
	coords = new Coordinates(windowCenter->getCoordinateSystem(), wx, wy);
	
	return coords;
}

/**
 * Updates screen so that user can see changes.
 */
void Graphics::update() {
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

/**
 * Clears backbuffer.
 */
void Graphics::clear() {
	lock();

	//Paint it black
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	
	unlock();
}

/**
 * Scrolls viewport by (x, y). Relative coordinates, world units.
 */
void Graphics::moveCamera(float x, float y) {
	this->windowCenter->add(x, y);
	
	//Scroll starfield
	//We cannot use the Coordinates / CoordinateSystem stuff here
	//because of performance.
	this->starfieldCenterX += x / 3;
	this->starfieldCenterY += y / 3;
	
	//Make sure that coordinates stay within the acceptable region
	while (starfieldCenterX < 0)
		starfieldCenterX += screen->w;
	
	while (starfieldCenterX >= screen->w)
		starfieldCenterX -= screen->w;
		
	while (starfieldCenterY < 0)
		starfieldCenterY += screen->h;
		
	while (starfieldCenterY >= screen->h)
		starfieldCenterY -= screen->h;
}

/**
 * Moves camera so that point (x, y) is centerd. Absolute coordintes, world
 * units.
 */
void Graphics::setCamera(float x, float y) {
	this->windowCenter->set(x, y);
}

/**
 * Creates a random starfield. The field is stored in Graphics until a new
 * one is created.
 */
void Graphics::createStarfield() {
	int b;  //Brightness
	
	//Delete the old star field
	if (stars)
		delete [] stars;
	
	//Create a new one
	stars = new TStar[STARS];
	
	for (int i=0; i < STARS; i++) {
		stars[i].x = rand() % screen->w;
		stars[i].y = rand() % screen->h;
		
		b = 32 + rand() % (255 - 32);
		stars[i].color = SDL_MapRGB(screen->format, b, b, b);
	}
}

/**
 * Draws the starfield directly on the screen.
 */
void Graphics::drawStarfield() {
	int sx, sy;  //Screen coordinates
	
	if (stars == NULL)
		return;
	
	for (int i = 0; i < STARS; i++) {
		//Scroll
		sx = (int)(stars[i].x - starfieldCenterX);
		sy = (int)(stars[i].y - starfieldCenterY);
		
		//Make sure that pixels stay in the window
		if (sx < 0)
			sx += screen->w;
		
		if (sy < 0)
			sy += screen->h;
		
		putpixel(this->screen, sx, sy, stars[i].color);
	}
}


/**
 * Draws a bitmap on the screen. World coordinates.
 * @param *surface Surface to be copied on the screen
 * @param &location Location, world coordinates
 * @param *sourceRect Defines the area of the source bitmap that is to be
 *                    copied. NULL means that whole bitmap is copied.
 */
void Graphics::drawBitmap(SDL_Surface *surface, const Coordinates &location,
                          SDL_Rect *sourceRect) {
	int i, j;
	float dx, dy;      //Distance from window center
	short int sx, sy;  //Screen coordinates
	unsigned int w, h;
	SDL_Rect destination;
	
	if (sourceRect == NULL) {
		w = surface->w;
		h = surface->h;
	} else {
		w = sourceRect->w;
		h = sourceRect->h;
	}
	
	//We may have to draw it four times because of the continuous world.
	for (i=-1; i<=1; i++) {
		for (j=-1; j<=1; j++) {
			//Bitmaps's distance from window center
			dx = windowCenter->getDistanceX(location.getX(), i);
			dy = windowCenter->getDistanceY(location.getY(), j);
			
			//Calculate screen coordinates
			sx = (int)(screen->w / 2 + dx - w / 2);
			sy = (int)(screen->h / 2 + dy - h / 2);
			
			//Draw if it's visible
			if ((sx + w > 0)  &&  (sx < screen->w)
			    &&  (sy + h > 0)  &&  (sy < screen->h))
			{
				destination.x = sx;
				destination.y = sy;
				
				SDL_BlitSurface(surface, sourceRect,
				                this->screen, &destination);
			}
		}
	}
}

/**
 * Draws a bitmap on the screen. Absolute screen coordinates.
 * @param *surface Surface to be copied on the screen
 * @param x Location, screen coordinates
 * @param y Location, screen coordinates
 * @param *sourceRect Defines the area of the source bitmap that is to be
 *                    copied. NULL means that whole bitmap is copied.
 */
void Graphics::drawBitmap(SDL_Surface *surface, int x, int y,
                          SDL_Rect *sourceRect)
{
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	
	SDL_BlitSurface(surface, sourceRect, this->screen, &destination);
}

/**
 * Draws a sprite on the screen. World coordinates. For animated sprites you
 * should call drawAnimated().
 * @param &location Location, world coordinates
 */
void Graphics::drawSprite(int spriteIndex, const Coordinates &location) {
	if (spriteIndex >= 0 || spriteIndex < (int)this->sprites.size())
		drawBitmap(this->sprites[spriteIndex]->surface, location, NULL);
}

/**
 * Draws a sprite on the screen. Absolute screen coordinates.
 * @param x Location, screen coordinates
 * @param y Location, screen coordinates
 */
void Graphics::drawSprite(int spriteIndex, int x, int y) {
	if (spriteIndex >= 0 || spriteIndex < (int)this->sprites.size())
		drawBitmap(this->sprites[spriteIndex]->surface, x, y, NULL);
}

/**
 * Draws a sprite on the screen. Selects frame accoring to phase. 0 = first
 * frame, .999 = last frame, 1 = first frame again... Phase can be between
 * (0, inf). This if useful for loopable animations. For non-loopable
 * animations make sure not to ever reach 'phase = 1' because that's the
 * first frame again.
 */
void Graphics::drawAnimated(int spriteIndex,
                            const Coordinates &location,
                            float phase)
{
	SDL_Rect sourceRect;
	
	if (spriteIndex < 0 || spriteIndex >= (int)this->sprites.size()) {
		return;
	}
	
	int cols = this->sprites[spriteIndex]->columns;
	int rows = this->sprites[spriteIndex]->rows;
	int w = this->sprites[spriteIndex]->surface->w;
	int h = this->sprites[spriteIndex]->surface->h;
	
	//Loop it
	int frame = (int)(phase * cols * rows) % (rows * cols);
	
	//Calculate source region
	sourceRect.x = (frame % cols) * (w / cols);
	sourceRect.y = (frame / cols) * (h / rows);
	sourceRect.w = w / cols;
	sourceRect.h = h / rows;

	drawBitmap(this->sprites[spriteIndex]->surface, location, &sourceRect);
}

/**
 * Rotates a bitmap and draws the result on a surface. Note that this is a
 * rather slow operation.
 * @param *source Bitmap to be rotated.
 * @param *target Surface that the result is drawn to
 * @param rot Angle in radians, 0 = east, ccw
 */
void Graphics::drawRotated(const SDL_Surface *source, SDL_Surface *target,
                           float rot)
{
	double x, y;       //Auxiliary
	float angle, dist; //Pixel's angle and distance from the center
	int sx, sy;        //Source coordinates
	int tx, ty;        //Target coordinates
	Uint32 color;
	
	for (ty = 0; ty < target->h; ty++) {
		for (tx = 0; tx < target->w; tx++) {
			//Read a pixel from rotated coordinates and plot
			
			x = tx - source->w / 2;
			y = ty - source->h / 2;
			angle = atan2(y, x);
			dist = sqrt(x*x + y*y);
			
			angle -= rot;
			sx = (int)(cos(angle) * dist + source->w / 2);
			sy = (int)(sin(angle) * dist + source->h / 2);
			
			if (sx >= 0 && sx < source->w && sy >= 0 && sy < source->h) {
				color = getpixel(source, sx, sy);
				putpixel(target, tx, ty, color);
			}
		}
	}
}

/**
 * Draws a filled rectangle on screen. World coordinates.
 * @param &location Location of the top-left corner
 * @param w Width in world units
 * @param h Height in world units
 */
void Graphics::drawRect(const Coordinates &location,
                        unsigned int w, unsigned int h,
                        Uint8 r, Uint8 g, Uint8 b)
{
	int i, j;
	SDL_Rect destination;
	float dx, dy;         //Distance from window center
	int sx, sy;           //Screen coordinates
	
	//Draw it in four places
	for (i=-1; i<=1; i++) {
		for (j=-1; j<=1; j++) {
			destination.w = (Uint16)w;
			destination.h = (Uint16)h;
			
			//Object's distance from window center
			dx = windowCenter->getDistanceX(location.getX(), i);
			dy = windowCenter->getDistanceY(location.getY(), j);
			
			//Calculate screen coordinates
			sx = (int)(screen->w / 2 + dx - w / 2);
			sy = (int)(screen->h / 2 + dy - h / 2);
			
			//Draw if it's visible
			if ((sx + w > 0)  &&  (sx < screen->w)
			    &&  (sy + h > 0)  &&  (sy < screen->h))
			{
				destination.x = sx;
				destination.y = sy;
				
				SDL_FillRect(this->screen, &destination,
                             SDL_MapRGB(screen->format, r, g, b));
			}
		}
	}
}

/**
 * Draws a filled rectangle on the screen. Screen units.
 * @param *target Target surface, NULL means screen
 * @param x Location of the top-left corner
 * @param y Location of the top-left corner
 * @param w Width in pixels
 * @param h Height in pixels
 */
void Graphics::drawRect(SDL_Surface *target, int x, int y,
                        unsigned int w, unsigned int h,
                        Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect destination;
	
	if (target == NULL)
		target = this->screen;
	
	destination.x = x;
	destination.y = y;
	destination.w = (Uint16)w;
	destination.h = (Uint16)h;
	
	SDL_FillRect(target, &destination, SDL_MapRGB(target->format, r, g, b));
}

/**
 * Draws text on a surface.
 * @param *target Target surface. If NULL, the text is rendered directly on
 * the screen.
 */
void Graphics::drawText(SDL_Surface *target, const char *text, int x, int y)
{
	SDL_Rect source, destination;
	
	source.w = 8;
	source.h = 14;
	destination.x = x;
	destination.y = y;
	
	if (target == NULL)
		target = this->screen;
	
	for (unsigned int i = 0; i < strlen(text); i++) {
		if (text[i] >= 'A' && text[i] <= 'Z') {
			source.x = (text[i] - 'A') * 8;
			source.y = 0;
		}
		else if (text[i] >= 'a' && text[i] <= 'z') {
			source.x = (text[i] - 'a') * 8;
			source.y = 14;
		}
		else if (text[i] >= '0' && text[i] <= '9') {
			source.x = (text[i] - '0') * 8;
			source.y = 28;
		}
		else if (text[i] == '\n') {
			source.x = 112;
			source.y = 28;
			destination.x = x;
			destination.y += LINE_HEIGHT;
			continue;
		}
		else if (text[i] >= '$' && text[i] <= '/') {
			source.x = (text[i] - '$') * 8;
			source.y = 42;
		}
		else if (text[i] >= ':' && text[i] <= '?') {
			source.x = (text[i] - ':') * 8 + 96;
			source.y = 42;
		}
		else {
			//Unknown character or empty space
			source.x = 88;
			source.y = 28;
		}
		
		SDL_BlitSurface(font, &source, target, &destination);
		
		destination.x += CHAR_WIDTH;
	}
}

int Graphics::getLineHeight() {
	return LINE_HEIGHT;
}

int Graphics::getCharWidth() {
	return CHAR_WIDTH;
}

/**
 * Returns the sdl-surface of a sprite. Note that many objects may use
 * the same sprite and sprites may not be modified.
 * @return NULL if there is no such sprite
 */
const SDL_Surface* Graphics::getSurface(int spriteIndex) {
	if (spriteIndex >= 0 || spriteIndex < (int)this->sprites.size())
		return this->sprites[spriteIndex]->surface;
	else
		return NULL;
}

/**
 * Returns a sprite index. This index can be used later to access the
 * sprite.
 * @param *name Name of the sprite. Names are defined in resource file
 *              'data/bitmaps'.
 * @return sprite index, or -1 if there is no such sprite
 */
int Graphics::getSpriteIndex(char *name) {
	//Find the sprite
	for (int i = 0; i < (int)this->sprites.size(); i++) {
		if (strcmp(name, this->sprites[i]->name) == 0)
			return i;
	}
	
	return -1;
}

/**
 * Loads a bitmap and returns a pointer to the sdl-surface. Remember to free
 * it.
 * @return NULL on failure
 */
SDL_Surface* Graphics::loadBitmap(char *fileName) {
	SDL_Surface* tempBitmap;
	SDL_Surface* finalBitmap;
	
	//Load the bitmap
	tempBitmap = SDL_LoadBMP(fileName);
	
	if (tempBitmap == NULL) {
		cerr << "Failed to load bitmap: " << SDL_GetError() << endl;
		return NULL;
	}
	
	//Set transparency
	SDL_SetColorKey(tempBitmap, SDL_SRCCOLORKEY | SDL_RLEACCEL,
	                SDL_MapRGB(tempBitmap->format, 255, 0, 255)); 
	
	//Convert colors to speed up blitting
	finalBitmap = SDL_DisplayFormat(tempBitmap);
	if (finalBitmap == NULL) {
		SDL_FreeSurface(tempBitmap);
		return NULL;
	}
	
	//Free the temporary bitmap
	SDL_FreeSurface(tempBitmap);
	
	return finalBitmap;
}

/**
 * Loads common game graphics. This should only be called once at init.
 * @return true on success, false on failure
 */
bool Graphics::loadSprites() {
	TSprite *sprite;

	ifstream file;
	char line[128];
	int rows, columns;
	
	file.open ("data/bitmaps", ifstream::in);

	if (!file.is_open()) {
		cerr << "Failed to open data/bitmaps" << endl;
		return false;
	}
	
	while (file.good()) {
    	file.getline(line, 128);
		
		//Skip empty lines
		if (strlen(line) < 1)
			continue;
		
		//Create a new sprite
		sprite = new TSprite;
		
		//Name
		sprite->name = new char[strlen(line) + 1];
		strcpy(sprite->name, line);
		
		//File name
		file.getline(line, 128);
		sprite->surface = loadBitmap(line);
		if (sprite->surface == NULL) {
			file.close();
			return false;
		}

		//Columns
		file.getline(line, 128);
		if (sscanf(line, "%*s %i", &columns) != 1) {
			cerr << "Resource file 'bitmaps' is corrupt" << endl;
			file.close();
			return false;
		}
		sprite->columns = columns;
		
		//Rows
		file.getline(line, 128);
		if (sscanf(line, "%*s %i", &rows) != 1) {
			cerr << "Resource file 'bitmaps' is corrupt" << endl;
			file.close();
			return false;
		}
		sprite->rows = rows;
		
		//Color key
		file.getline(line, 128); //This parameter cannot be adjusted yet
		
		//Use the default color key
		if (sprite->surface != NULL) {
			SDL_SetColorKey(sprite->surface, SDL_SRCCOLORKEY | SDL_RLEACCEL,
			                SDL_MapRGB(this->screen->format, 255, 0, 255)); 
		}
		
		this->sprites.push_back(sprite);
	}

	file.close();
	return true;
}

/**
 * Destroys game graphics
 */
void Graphics::destroySprites() {
	for (int i = 0; i < (int)this->sprites.size(); i++) {
		delete [] this->sprites[i]->name;
		SDL_FreeSurface(this->sprites[i]->surface);
		delete this->sprites[i];
	}

	this->sprites.clear();
}


/**
 * Creates a unique surface that can be used to store any image data. The
 * surface must be freed when it's not needed anymore.
 * @param w width in pixels
 * @param h height in pixels
 */
SDL_Surface *Graphics::createSurface(unsigned int w, unsigned int h) {
	SDL_Surface *tempBitmap;
	SDL_Surface *finalBitmap;
	
	//Create a new surface
	tempBitmap = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);

	//Set transparency
	SDL_SetColorKey(tempBitmap, SDL_SRCCOLORKEY | SDL_RLEACCEL,
	                SDL_MapRGB(tempBitmap->format, 255, 0, 255)); 
	
	//Convert colors to speed up blitting
	finalBitmap = SDL_DisplayFormat(tempBitmap);
	
	SDL_FreeSurface(tempBitmap);
	
	if (finalBitmap == NULL)
		return NULL;
	
	//Paint it transparent initially
	SDL_FillRect(finalBitmap, NULL,
	             SDL_MapRGB(finalBitmap->format, 255, 0, 255));
	
	return finalBitmap;
}

/**
 * Frees a surface that was created with createSurface().
 */
void Graphics::freeSurface(SDL_Surface *surface) {
	SDL_FreeSurface(surface);
}


/**
 * Plots a pixel directly to a surface. Screen coordinates.
 */
void Graphics::putpixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	/* This code is from SDL documentation. */
	
	int bpp = surface->format->BytesPerPixel;
	
	//p is the address to the pixel
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			*p = color;
			break;
		
		case 2:
			*(Uint16 *)p = color;
			break;
		
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (color >> 16) & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = color & 0xff;
			} else {
				p[0] = color & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = (color >> 16) & 0xff;
			}
			break;
		
		case 4:
			*(Uint32 *)p = color;
			break;
	}
}

/**
 * Returns the pixel value at (x, y). Screen coordinates.
 */
Uint32 Graphics::getpixel(const SDL_Surface *surface, int x, int y) {
	/* This code is from SDL documentation. */
	
	int bpp = surface->format->BytesPerPixel;
	
	// p is the address to the pixel
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			return *p;
	
		case 2:
			return *(Uint16 *)p;
	
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
	
		case 4:
			return *(Uint32 *)p;
	
		default:
			return 0;
	}
}


/**
 * Locks the screen to allow direct access. This is not necessary for normal
 * sprite blitting.
 */
void Graphics::lock() {
	//Lock the screen, if necessary
	if (SDL_MUSTLOCK(this->screen)) {
		SDL_LockSurface(screen);
	}
}

/**
 * Unlocks the screen if it was locked with lock().
 */
void Graphics::unlock() {
	//Ulock the screen, if necessary
	if(SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen); 
	}
}
