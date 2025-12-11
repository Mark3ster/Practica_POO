#include "Loan.h"
#include "User.h"
#include "Item.h"


Loan::Loan(User* u, Item* i, const std::string& start, const std::string& due)
	: user(u), item(i), startDate(start), dueDate(due), returned(false) {}


bool Loan::isReturned() const {
	return returned; 
}
void Loan::setReturnDate(const std::string& date) {
	returnDate = date; 
	returned = true; 
}
User* Loan::getUser() const {
	return user;
}
Item* Loan::getItem() const {
	return item; 
}
std::string Loan::getDue() const { 
	return dueDate; 
}
std::string Loan::getReturn() const {
	return returnDate; 
}
std::string Loan::getStart() const { 
	return startDate; 
}