#include <cstring>
#include "UITextField.h"

/**
 * Constructor.
 * @param length Maximum length of content in characters.
 */
UITextField::UITextField(Window &parentWindow, unsigned int length,
                         int x, int y)
	: UIComponent(parentWindow, x, y)
{
	Graphics *graphics = parentWindow.getGraphics();
	
	this->image = NULL;
	this->width = length * graphics->getCharWidth();
	this->height =  graphics->getLineHeight();
	this->maxLength = length;
}

/**
 * Destructor
 */
UITextField::~UITextField() {
	Graphics *graphics = parentWindow.getGraphics();
	
	if (this->image)
		graphics->freeSurface(this->image);
}

/**
 * Sets text.
 */
void UITextField::setText(string &text) {
	this->content = text;
	
	updateImage();
}

/**
 * Sets text.
 */
void UITextField::setText(const char *text) {
	if (text == NULL)
		this->content.clear();
	else
		this->content = text;
	
	updateImage();
}

/**
 * Clears content.
 */
void UITextField::clear() {
	this->content.clear();
	updateImage();
}

/**
 * Returns copy of the content. Remember to delete the returned string
 * after you are done with it.
 * @return NULL if component is empty
 */
char *UITextField::getText() {
	char *text;
	
	if (content.length() < 1)
		return NULL;
	
	text = new char[content.length()];
	
	if (text == NULL)
		return NULL;
	
	strcpy(text, content.c_str());
	
	return text;
}

/**
 * Updates image of the component. Nothing is drawn on the screen. This
 * should be called is text is changed.
 */
void UITextField::updateImage() {
	Graphics *graphics = parentWindow.getGraphics();
	
	//Resize the surface
	this->width = content.length() * graphics->getCharWidth();
	this->height = graphics->getLineHeight();
	
	//Destroy old image and create a new one
	if (this->image != NULL)
		graphics->freeSurface(this->image);
	
	if (this->width > 0 && this->height > 0)
		this->image = graphics->createSurface(this->width, this->height);
	else
		this->image = NULL;
	
	//Draw text on surface
	if (this->image)
		graphics->drawText(this->image, content.c_str(), 0, 0);
}

/**
 * Handles key down events.
 */
void UITextField::keyDown(SDL_keysym keysym) {
	unsigned char c;
	
	c = keysym.sym;  //ASCII character
	
	//Backspace
	if (c == 8 && content.length() > 0) { 
		content.erase(content.length() - 1, 1);
	}
	
	//Limit size
	if (content.length() >= this->maxLength) {
		return;
	}
	
	//Capitals
	if (keysym.mod & KMOD_SHIFT && keysym.sym >= 'a' && keysym.sym <= 'z') {
		c -= ('a' - 'A');
	}
	
	//Accept only sensible letters
	if ((keysym.sym >= 'a' && keysym.sym <= 'z')
		|| (keysym.sym >= 'A' && keysym.sym <= 'Z')
		|| (keysym.sym >= '0' && keysym.sym <= '9')
		|| (keysym.sym == ' ')
	) {
		content.append(1, c);
	}
	
	//Update text
	setText(content.c_str());
}
