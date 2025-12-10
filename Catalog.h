#pragma once


#include <vector>
#include "Item.h"


class Catalog {
private:
	std::vector<Item*> items;
public:
	~Catalog();
	void addItem(Item* item);
	void listItems() const;
	Item* get(int index) const;
	int size() const;
	void listItemsWithIndex() const;
	const std::vector<Item*>& getItems() const;
	void replaceItem(int index, Item* newItem);
};