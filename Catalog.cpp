#include "Catalog.h"
#include <iostream>


Catalog::~Catalog() {
	for (Item* it : items) delete it;
	items.clear();
}


void Catalog::addItem(Item* item) { items.push_back(item); }


void Catalog::listItems() const {
	for (const auto& it : items) std::cout << it->info() << std::endl;
}


Item* Catalog::get(int index) const { return items.at(index); }
int Catalog::size() const { return static_cast<int>(items.size()); }


void Catalog::listItemsWithIndex() const {
	for (int i = 0; i < static_cast<int>(items.size()); ++i) {
		std::cout << i << " - " << items[i]->info() << std::endl;
	}
}


const std::vector<Item*>& Catalog::getItems() const { return items; }


void Catalog::replaceItem(int index, Item* newItem) {
	if (index < 0 || index >= static_cast<int>(items.size())) return;
	delete items[index];
	items[index] = newItem;
}