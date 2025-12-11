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


	bool isReturned() const;	//su funcion es verificar si el prestamo ha sido devuelto
	void setReturnDate(const std::string& date);	//su funcion es establecer la fecha de devolucion del prestamo


	User* getUser() const;	//su funcion es devolver el usuario asociado al prestamo
	Item* getItem() const;	//su funcion es devolver el item asociado al prestamo
	std::string getDue() const;	//su funcion es devolver el item asociado al prestamo
	std::string getReturn() const;	//su funcion es devolver la fecha de devolucion del prestamo
	std::string getStart() const;	//su funcion es devolver la fecha de inicio del prestamo
};