
#ifndef _ITEM_H_
#define _ITEM_H_

#include <iostream>

/**
 * Author: Jaakko Luttinen
 * Item is a class for items that have name, description and price.
 */
class Item
{
	
public:

	/**
	 * Constructs a new item.
	 * @param name        Name of the item.
	 * @param description Description of the item.
	 * @param price       Price of the item.
	 */
	Item( const std::string &name, const std::string &description,
	      int price );
	
	/**
	 * Constructs a new item from a copy.
	 * @param copy The item to copy.
	 */
	Item( const Item &copy );
	
	/**
	 * Destructs the item.
	 */
	virtual ~Item() {  };
	
	/**
	 * Tells the name of the item.
	 * @return The name of the item.
	 */
	inline const char* getName() const  { return this->name.c_str(); };
	
	/**
	 * Tells the description of the item.
	 * @return The description of the item.
	 */
	inline const char* getDescription() const
		{ return this->description.c_str(); };
	
	/**
	 * Tells the price of the item.
	 * @return The price of the item.
	 */
	inline int getPrice() const  { return this->price; };

private:

	/**
	 * Name of the item.
	 */
	std::string name;
	
	/**
	 * Description of the item.
	 */
	std::string description;
	
	/**
	 * Price of the item.
	 */
	int price;
	
};

#endif //_ITEM_H_
