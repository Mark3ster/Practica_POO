#pragma once


#include "Item.h"
#include <string>


class Journal : public Item {
private:
	std::string title;
	int volume;
public:
	Journal(const std::string& t, int v);
	std::string info() const override;
	std::string getTitle() const;
	int getVolume() const;
};