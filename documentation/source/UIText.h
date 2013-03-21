#ifndef _UI_TEXT_H_
#define _UI_TEXT_H_

class UIText;

#include "Window.h"
#include "UIComponent.h"

using std::string;

/**
 * UIText is a component that shows static text. It is multi-line capable.
 * Size of the component is adjusted automatically.
 *
 * @author Tapio Auvinen
 */

class UIText : public UIComponent  {
public:
	/**
	 * Constructor
	 * @param &parentWindow Reference to the parent window
	 * @param x location of upper-left window
	 * @param y location of upper-left window
	 */
	UIText(Window &parentWindow, int x, int y);
	
	/**
	 * Constructor
	 * @param &parentWindow Reference to the parent window
	 * @param *text text
	 * @param x location of upper-left window
	 * @param y location of upper-left window
	 */
	UIText(Window &parentWindow, const char *text, int x, int y);
	
	/**
	 * Destructor
	 */
	~UIText();

	/**
	 * Sets text.
	 * @param &text new text
	 */
	void setText(string &text);
	
	/**
	 * Sets text.
	 * @param *text new text
	 */
	void setText(const char *text);
	
	/**
	 * Sets text.
	 * @param number number is converted to text
	 */
	void setText(const int number);
	
	/**
	 * Clears text.
	 */
	void clear();
	
private:
	/**
	 * Updates image of the component. Nothing is drawn on the screen. This
	 * should be called is text is changed.
	 */
	void updateImage();
	
	string content;
};

#endif
