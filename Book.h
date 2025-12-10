#pragma once


#include "Item.h"
#include <string>


class Book : public Item {
private:
	std::string title;
	std::string author;
public:
	Book(const std::string& t, const std::string& a);
	std::string info() const override;
	std::string getTitle() const;
	std::string getAuthor() const;
};