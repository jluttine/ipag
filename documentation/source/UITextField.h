#ifndef _UI_TEXT_FIELD_H_
#define _UI_TEXT_FIELD_H_

#include "Window.h"
#include "UIComponent.h"

using std::string;

/**
 * UITextField is a component where user can enter text.
 * @author Tapio Auvinen
 */

class UITextField : public UIComponent  {
public:
	/**
	 * Constructor.
	 * @param &parentWindow Reference to the parent window
	 * @param length Maximum length of content in characters.
	 */
	UITextField(Window &parentWindow, unsigned int length, int x, int y);
	
	/**
	 * Destructor
	 */
	~UITextField();

	/**
	 * Handles key down events.
	 */
	void keyDown(SDL_keysym keysym);
	
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
	 * Returns copy of the content. Remember to delete the returned string
	 * after you are done with it.
	 * @return pointer to the new string, NULL if component is empty
	 */
	char *getText();
	
	/**
	 * Clears content.
	 */
	void clear();
	
private:
	/**
	 * Updates image of the component. Nothing is drawn on the screen. This
	 * should be called is text is changed.
	 */
	void updateImage();
	
	string content;
	unsigned int maxLength;  //Maximum legnth of content in characters
};

#endif
