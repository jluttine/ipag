#ifndef GRAPHICS_GAME_H
#define GRAPHICS_GAME_H

class Graphics;

#include <vector>
#include <SDL/SDL.h>
#include "Coordinates.h"

#define SIDEBAR_WIDTH  200

using std::vector;

/**
 * Class Graphics. Low level graphic functions + some game specific stuff.
 * 
 * If a drawing function takes a Coordinates object as a reference, the
 * object is considered to be a part of the continuous world and it may
 * appear in up tp four different places on the screen and it is subject to
 * scrolling. If a function takes x and y coordinates, the object is drawn
 * on those screen coordinates and it is not scrolled.
 *
 * Common game graphics is loaded on init. Sprite indexes are defined in
 * images.h. Files are defined in resource file data/bitmpas.
 *
 * Only on graphics object may exist. It sould be created when the program
 * starts and deleted before just before it quits.
 *
 * @author Tapio Auvinen
 */

class Graphics {
public:
	/**
	 * Constructor. init() must be called before anything can be drawn.
	 */
	Graphics();
	
	/**
	 * Destructor
	 */
	~Graphics();
	
	/**
	 * Initializes the graphics engine. Nothing must be drawn before this
	 * is done. If this fails, you should quit.
	 * @param resX x-resolution
	 * @param resY y-resolution
	 * @param resX bit depth in bits usually 16, 24 or 32
	 * @return true if successful.
	 */
	bool init(int resX, int resY, int bitDepth);
	
	/**
	 * Sets coordinate system so that grapchics becomes aware of the
	 * dimensions of the world. This must be set before any game graphics
	 * is drawn.
	 * @param &system new coordinate system
	 */
	void setCoordinateSystem(const CoordinateSystem &system);
	
	/**
	 * Converts screen coordinates to world coordinates.
	 * @param x x location on screen
	 * @param y y location on screen
	 * @return Coordinates object. Remember to delete it afterwards.
	 */
	Coordinates *getWorldCoordinates(int x, int y);
	
	/**
	 * Updates screen so that user can see changes.
	 */
	void update();
	
	/**
	 * Clears backbuffer.
	 */
	void clear();
	
	/**
	 * Scrolls viewport by (x, y). Relative coordinates, world units.
	 * @param x distance to be scrolled
	 * @param y distance to be scrolled
	 */
	void moveCamera(float x, float y);
	
	/**
	 * Moves camera so that point (x, y) is centerd. Absolute coordintes,
	 * world units.
	 * @param x new x coordinate, world units
	 * @param y new y coordinate, world units
	 */
	void setCamera(float x, float y);

	/**
	 * Creates a random starfield. The field is stored in Graphics until a new
	 * one is created.
	 */
	void createStarfield();
	
	/**
	 * Draws the starfield directly on the screen.
	 */
	void drawStarfield();
	
	/**
	 * Draws a bitmap on the screen. World coordinates.
	 * @param *surface Surface to be copied on the screen
	 * @param &location Location of the center of the object, world coordinates
	 * @param *sourceRect Defines the area of the source bitmap that is to
	 *                    be copied. NULL means that whole bitmap is copied.
	 */
	void drawBitmap(SDL_Surface *surface, const Coordinates &location, 
	                SDL_Rect *sourceRect = NULL);
	
	/**
	 * Draws a bitmap on the screen. Absolute screen coordinates.
	 * @param *surface Surface to be copied on the screen
	 * @param x Location of the center, screen coordinates
	 * @param y Location of the center, screen coordinates
	 * @param *sourceRect Defines the area of the source bitmap that is to
	 *                    be copied. NULL means that whole bitmap is copied.
	 */
	void drawBitmap(SDL_Surface *surface, int x, int y,
	                SDL_Rect *sourceRect = NULL);
	
	/**
	 * Draws a sprite on the screen. World coordinates. For animated
	 * sprites you should call drawAnimated().
	 * @param spriteIndex indexes are defined in images.h
	 * @param &location Location of the center, world coordinates
	 */
	void drawSprite(int spriteIndex, const Coordinates &location);
	
	/**
	 * Draws a sprite on the screen. Absolute screen coordinates.
	 * @param spriteIndex indexes are defined in images.h
	 * @param x Location of the center, screen coordinates
	 * @param y Location of the center, screen coordinates
	 */
	void drawSprite(int spriteIndex, int x, int y);
	
	/**
	 * Draws a sprite on the screen. Selects frame accoring to phase.
	 * 0 = first frame, .999 = last frame, 1 = first frame again... Phase
	 * can be between (0, inf). This if useful for loopable animations. For
	 * non-loopable animations make sure not to ever reach 'phase = 1'
	 * because that's the first frame again.
	 * @param spriteIndex indexes are defined in images.h
	 * @param &location Location of the center, world coordinates
	 * @param phase Phase of animation, [0, 1] or [0, inf] (looping)
	 */
	void drawAnimated(int spriteIndex, const Coordinates &location,
	                  float phase);
	
	/**
	 * Rotates a bitmap and draws the result on a surface. Note that this
	 * is a rather slow operation.
	 * @param *source Bitmap to be rotated.
	 * @param *target Surface that the result is drawn to
	 * @param rot angle in radians, 0 = east, ccw
	 */
	void drawRotated(const SDL_Surface *source, SDL_Surface *target,
	                 float angle);
	
	/**
	 * Draws a filled rectangle on screen. World coordinates.
	 * @param &location Location of the top-left corner
	 * @param w Width in world units
	 * @param h Height in world units
	 * @param r r component, [0, 255]
	 * @param g g component, [0, 255]
	 * @param b b component, [0, 255]
	 */
	void drawRect(const Coordinates &location,
	              unsigned int w, unsigned int h,
	              Uint8 r, Uint8 g, Uint8 b);
	
	/**
	 * Draws a filled rectangle on the screen. Screen units.
	 * @param *target Target surface, NULL means screen
	 * @param x Location of the top-left corner
	 * @param y Location of the top-left corner
	 * @param w Width in pixels
	 * @param h Height in pixels
	 * @param r r component, [0, 255]
	 * @param g g component, [0, 255]
	 * @param b b component, [0, 255]
	 */
	void drawRect(SDL_Surface *target, int x, int y,
	              unsigned int w, unsigned int h,
	              Uint8 r, Uint8 g, Uint8 b);
	
	/**
	 * Draws text on a surface.
	 * @param *target Target surface. If NULL, the text is rendered
	 *                directly on the screen.
	 * @param *text Text to be drawn. It may contain '/n' characters.
	 * @param x location of the top-left corner on screen
	 * @param y location of the top-left corner on screen
	 */
	void drawText(SDL_Surface *target, const char *text, int x, int y);

	/**
	 * Returns line height of text in pixels.
	 * @return height in pixels
	 */
	int getLineHeight();

	/**
	 * Returns character width in pixels.
	 * @return width in pixels
	 */
	int getCharWidth();
	
	/**
	 * Returns the sdl-surface of a sprite. Note that many objects may use
	 * the same sprite and sprites may not be modified.
	 * @param spriteIndex indexes are defined in images.h
	 * @return NULL if there is no such sprite
	 */
	const SDL_Surface* getSurface(int spriteIndex);

	/**
	 * Returns a sprite index. This index can be used later to access the
	 * sprite.
	 * @param *name Name of the sprite. Names are defined in resource file
	 *              'data/bitmaps'.
	 * @return sprite index, or -1 if there is no such sprite
	 */
	int getSpriteIndex(char *name);
	
	/**
	 * Loads a bitmap and returns a pointer to the sdl-surface. Remember
	 * to free it.
	 * @param fileName file name
	 * @return pointer to the surface, NULL on failure
	 */
	SDL_Surface* loadBitmap(char *fileName);
	
	/**
	 * Creates a unique surface that can be used to store any image data.
	 * The surface must be freed when it's not needed anymore.
	 * @param w width in pixels
	 * @param h height in pixels
	 * @return pointer to the new surface, NULL on failure
	 */
	SDL_Surface *createSurface(unsigned int w, unsigned int h);
	
	/**
	 * Frees a surface that was created with createSurface().
	 * @param *surface surface to be freed
	 */
	void freeSurface(SDL_Surface *surface);
	
	/**
	 * Locks the screen to allow direct access. This is not necessary for
	 * normal sprite blitting.
	 */
	void lock();
	
	/**
	 * Unlocks the screen if it was locked with lock().
	 */
	void unlock();
	
	
private:
	
	//Structure to store common game graphics
	typedef struct {
		char *name;
		SDL_Surface *surface;
		unsigned int columns;
		unsigned int rows;
		Uint32 colorKey;
	} TSprite;

	//Structure to store stars in the starfield
	typedef struct {
		int x;
		int y;
		Uint32 color;
	} TStar;
	
	SDL_Surface *screen; //Pointer to the screen
	SDL_Surface *font;   //Font bitmap
	
	vector<TSprite*> sprites;  //Common game graphics
	
	Coordinates *windowCenter; //Coordinates of window center,
	                           //needed in scrolling
	
	TStar *stars;  //Star field
	float starfieldCenterX, starfieldCenterY; //Coordinates of the center of
	                                       //star field, needed in scrolling
	
	/**
	 * Loads common game graphics. This should only be called once at init.
	 * If this fails, no graphics may be drawn.
	 * @return true on success, false on failure
	 */
	bool loadSprites();
	
	/**
	 * Destroys game graphics
	 */
	void destroySprites();
	
	/**
	 * Plots a pixel directly to a surface. 
	 * @param *surface target surface
	 * @param x location in pixels
	 * @param y location in pixels
	 * @param color SDL color
	 */
	inline void putpixel(SDL_Surface *surface, int x, int y, Uint32 color);
	
	/**
	 * Returns the pixel value at (x, y).
	 * @param *surface source surface
	 * @param x location in pixels
	 * @param y location in pixels
	 */
	inline Uint32 getpixel(const SDL_Surface *surface, int x, int y);

};


#endif
