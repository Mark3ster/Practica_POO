#pragma once


#include <string>


class Item {
public:
	virtual std::string info() const = 0;
	virtual ~Item() {}
};