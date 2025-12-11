#pragma once


#include "Item.h"
#include <string>


class Ebook : public Item {
private:
	std::string license;
	std::string expiryDate;
public:
	Ebook(const std::string& l, const std::string& e); // Constructor
	std::string info() const override;	//su funcion es proporcionar una representacion en forma de cadena del ebook, incluyendo su licencia y fecha de expiracion
	std::string getExpiryDate() const;	//su funcion es devolver la fecha de expiracion del ebook
	std::string getLicense() const;		//su funcion es devolver la licencia del ebook
};