#include "Book.h"


Book::Book(const std::string& t, const std::string& a) : title(t), author(a) {}


std::string Book::info() const {
	return "Libro: " + title + " por " + author;
}


std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }