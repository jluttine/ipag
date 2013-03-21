#include "UIComponent.h"
#include "Graphics.h"


/**
 * Constructor.
 * @param parent Parent window
 * @param x Location of the upper-left corner
 * @param y Location of the upper-left corner
 */
UIComponent::UIComponent(Window &parent, int x, int y)
	: parentWindow(parent)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;

	this->image = NULL;
}

/**
 * Destructor
 */
UIComponent::~UIComponent() {
}

/**
 * Draws component on screen.
 */
void UIComponent::draw(Graphics &graphics) {
	if (this->image != NULL)
		graphics.drawBitmap(this->image, x, y);
}

/**
 * Relocates component.
 */
void UIComponent::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}
