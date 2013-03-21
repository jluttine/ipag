
#include "Item.h"

/**
 * Constructs a new item.
 * @param name        Name of the item.
 * @param description Description of the item.
 * @param price       Price of the item.
 */
Item::Item( const std::string &name, const std::string &description,
            int price )
{
	
	this->name = name;
	this->description = description;
	this->price = price;
	
}

/**
 * Constructs a new item from a copy.
 * @param copy The item to copy.
 */
Item::Item( const Item &copy )
{
	
	this->name = copy.name;
	this->description = copy.description;
	this->price = copy.price;
	
}
