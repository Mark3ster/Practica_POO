#pragma once


#include "Item.h"
#include <string>


class Journal : public Item {
private:
	std::string title;
	int volume;
public:
	Journal(const std::string& t, int v); // Constructor
	std::string info() const override;	//su funcion es proporcionar una representacion en forma de cadena del diario, incluyendo su titulo y volumen
	std::string getTitle() const;	//su funcion es devolver el titulo del diario
	int getVolume() const;	//su funcion es devolver el volumen del diario
};