#include "Ebook.h"


Ebook::Ebook(const std::string& l, const std::string& e) : license(l), expiryDate(e) {}


std::string Ebook::info() const {
	return "Ebook || Licencia: " + license + ", Expira: " + expiryDate;
}


std::string Ebook::getExpiryDate() const { 
	return expiryDate;
}
std::string Ebook::getLicense() const { 
	return license; 
}