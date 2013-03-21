#ifndef _UI_BUTTON_H_
#define _UI_BUTTON_H_

#include "Window.h"
#include "UIComponent.h"

/**
 * UIButton is a UI component. Currently it works pretty much the same way
 * as UIText but in future buttons may have a special look.
 * 
 * Width and height of the button are adjusted automatically.
 *
 * @author Tapio Auvinen
 */

class UIButton : public UIComponent {
public:
	/**
	 * Constructor. 
	 * @param &parentWindow Reference to the parent window
	 * @param *text Text
	 * @param x Location of the upper-left corner.
	 * @param y Location of the upper-left corner.
	 */
	UIButton(Window &parentWindow, const char *text, int x, int y);
	
	/**
	 * Destructor
	 */
	~UIButton();

	/**
	 * Changes text.
	 * @param text new text
	 */
	void setText(const char *text);
	
private:
	char *text;  //Text of the button
};

#endif
