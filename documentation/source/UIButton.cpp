#include <cstring>
#include "UIButton.h"


/**
 * Constructor. 
 * @param &parentWindow Parent window must be set because it provides
 * services that the button needs.
 * @param *text Text
 * @param x Location of the upper-left corner.
 * @param y Location of the upper-left corner.
 */
UIButton::UIButton(Window &parentWindow, const char *text, int x, int y)
	: UIComponent(parentWindow, x, y)
{
	this->image = NULL;
	this->text = NULL;
	
	setText(text);
}

/**
 * Destructor
 */
UIButton::~UIButton() {
	Graphics *graphics = parentWindow.getGraphics();
	
	if (this->text)
		delete [] this->text;
	
	if (this->image)
		graphics->freeSurface(this->image);
}

/**
 * Changes text.
 */
void UIButton::setText(const char *text) {
	Graphics *graphics = parentWindow.getGraphics();
	
	if (text == NULL)
		return;
	
	if (this->text)
		delete [] this->text;
	
	//Copy text
	this->text= new char[strlen(text) + 1];
	strcpy(this->text, text);

	//Resize the surface
	this->width = strlen(text) * graphics->getCharWidth();
	this->height = graphics->getLineHeight();
	
	if (this->image)
		graphics->freeSurface(this->image);
	
	if (this->width > 0 && this->height > 0)
		this->image = graphics->createSurface(this->width, this->height);
	else
		this->image = NULL;
	
	//Draw text on surface
	if (this->image)
		graphics->drawText(this->image, text, 0, 2);
}
