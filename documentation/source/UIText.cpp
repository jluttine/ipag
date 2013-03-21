#include <iostream>
#include <cstring>
#include "UIText.h"

/**
 * Constructor.
 */
UIText::UIText(Window &parentWindow, int x, int y)
	: UIComponent(parentWindow, x, y)
{
	this->image = NULL;
}

/**
 * Constructor.
 */
UIText::UIText(Window &parentWindow, const char *text, int x, int y)
	: UIComponent(parentWindow, x, y)
{
	this->image = NULL;
	
	setText(text);
}

/**
 * Destructor
 */
UIText::~UIText() {
	Graphics *graphics = parentWindow.getGraphics();
	
	if (this->image)
		graphics->freeSurface(this->image);
}

/**
 * Sets text.
 */
void UIText::setText(string &text) {
	this->content = text;
	
	updateImage();
}

/**
 * Sets text.
 */
void UIText::setText(const char *text) {
	if (text == NULL)
		this->content.clear();
	else
		this->content = text;
	
	updateImage();
}

/**
 * Sets text.
 */
void UIText::setText(const int number) {
	char text[20];
	
	sprintf(text, "%d", number);
	this->content = text;
	
	updateImage();
}

/**
 * Clears text.
 */
void UIText::clear() {
	this->content.clear();
	updateImage();
}

/**
 * Updates image of the component. Nothing is drawn on the screen. This
 * should be called is text is changed.
 */
void UIText::updateImage() {
	Graphics *graphics = parentWindow.getGraphics();
	
	int lines = 1;   //Number of lines
	int width = 0;   //Width counter
	int widest = 0;  //Width of the widest line in characters
	
	//Measure width and height
	for (unsigned int i = 0; i < content.length(); i++) {
		if (content[i] == '\n') {
			if (width > widest)
				widest = width;
			
			width = 0;
			lines++;
		} else {
			width++;
		}
	}
	
	//What if the last line was longest?
	if (width > widest)
		widest = width;
	
	//Set width and height of the component
	this->width = widest * graphics->getCharWidth();
	this->height = lines * graphics->getLineHeight();
	
	//Destroy old image and create a new one
	if (this->image != NULL)
		graphics->freeSurface(this->image);
	
	if (this->width > 0 && this->height > 0)
		this->image = graphics->createSurface(this->width, this->height);
	else
		this->image = NULL;
	
	//Draw text on surface
	if (this->image)
		graphics->drawText(this->image, this->content.c_str(), 0, 0);
}
