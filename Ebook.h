#pragma once


#include "Item.h"
#include <string>


class Ebook : public Item {
private:
	std::string license;
	std::string expiryDate;
public:
	Ebook(const std::string& l, const std::string& e);
	std::string info() const override;
	std::string getExpiryDate() const;
	std::string getLicense() const;
};