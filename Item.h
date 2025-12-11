#pragma once


#include <string>


class Item {
public:
	virtual std::string info() const = 0;	//proporciona una representacion en forma de cadena del item
	virtual ~Item() {}
};