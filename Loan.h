#pragma once


#include <string>


class User;
class Item;


class Loan {
private:
	User* user;
	Item* item;
	std::string startDate;
	std::string dueDate;
	std::string returnDate;
	bool returned;
public:
	Loan(User* u, Item* i, const std::string& start, const std::string& due);
	~Loan() = default;


	bool isReturned() const;
	void setReturnDate(const std::string& date);


	User* getUser() const;
	Item* getItem() const;
	std::string getDue() const;
	std::string getReturn() const;
	std::string getStart() const;
};