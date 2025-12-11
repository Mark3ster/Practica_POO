#pragma once


#include "Item.h"
#include <string>


class Book : public Item {
private:
	std::string title;
	std::string author;
public:
	Book(const std::string& t, const std::string& a); // Constructor
	std::string info() const override;	//su funcion es proporcionar una representacion en forma de cadena del libro, incluyendo su titulo y autor
	std::string getTitle() const;	//su funcion es devolver el titulo del libro
	std::string getAuthor() const;	//su funcion es devolver el autor del libro
};