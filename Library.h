#pragma once


#include "Catalog.h"
#include "User.h"
#include "Loan.h"
#include "Item.h"
#include <vector>
#include <string>


class Library {
private:
	Catalog catalog;
	std::vector<User*> users;
	std::vector<Loan*> loans;
public:
	~Library();


	void addItem(Item* item);	//su funcion es agregar un nuevo item al catalogo de la biblioteca	
	void addUser(User* u);	//su funcion es agregar un nuevo usuario a la biblioteca
	void listItems();	//su funcion es listar todos los items presentes en el catalogo de la biblioteca
	User* findUser(int id);	//su funcion es buscar y devolver un usuario especifico basado en su ID
	Item* getItem(int index);	//su funcion es obtener un item especifico del catalogo basado en su indice
	void listItemsWithIndex();	//su funcion es listar todos los items del catalogo junto con sus indices correspondientes
	void loanItem(User* user, Item* item, const std::string& start, const std::string& due);		//su funcion es prestar un item a un usuario especifico, registrando la fecha de inicio y la fecha de vencimiento del prestamo
	Loan* findLoan(User* user, Item* item);		//su funcion es buscar y devolver un prestamo especifico basado en el usuario y el item involucrados
	void returnItem(User* user, Item* item, const std::string& returnDate);	//su funcion es procesar la devolucion de un item prestado por un usuario, registrando la fecha de devolucion


	bool userBlocked(User* user);	//su funcion es verificar si un usuario especifico esta bloqueado para realizar prestamos
	bool bookExpired(class Ebook* ebook, const std::string& startDate);	//su funcion es verificar si un ebook especifico ha expirado en base a la fecha de inicio del prestamo


	void saveItems(const std::string& filename);	//su funcion es guardar los items del catalogo de la biblioteca en un archivo especifico
	const std::vector<Item*>& catalogItems() const;	//su funcion es devolver una referencia constante al vector que contiene todos los items del catalogo de la biblioteca


	void saveUsers(const std::string& filename);	//su funcion es guardar los usuarios de la biblioteca en un archivo especifico
	void saveLoans(const std::string& filename);	//su funcion es guardar los prestamos de la biblioteca en un archivo especifico


	void loadItems(const std::string& filename);	//su funcion es cargar los items del catalogo de la biblioteca desde un archivo especifico
	void loadUsers(const std::string& filename);	//su funcion es cargar los usuarios de la biblioteca desde un archivo especifico
	void loadLoans(const std::string& filename);	//su funcion es cargar los prestamos de la biblioteca desde un archivo especifico


	std::vector<Item*> buscarporAutor(const std::string& autor);	//su funcion es buscar y devolver un vector de punteros a items que coinciden con un autor especifico
	void sortByTitle(std::vector<Item*>& vec);	//su funcion es ordenar un vector de punteros a items en orden alfabetico basado en sus titulos
	void showItems(const std::vector<Item*>& vec);	//su funcion es mostrar la informacion de cada item en un vector de punteros a items
	void exportActiveLoansCSV(const std::string& filename);	//su funcion es exportar los prestamos activos de la biblioteca a un archivo CSV especifico
	int findItemIndex(Item* it);	//su funcion es buscar y devolver el indice de un item especifico en el catalogo de la biblioteca
	void removeItem(int index);	//su funcion es eliminar un item del catalogo de la biblioteca basado en su indice
	void editItem(int index);	//su funcion es editar un item existente en el catalogo de la biblioteca en un indice especifico
	void blockUser(int userId);	//su funcion es bloquear a un usuario especifico para que no pueda realizar prestamos
	void unblockUser(int userId);	//su funcion es desbloquear a un usuario especifico para que pueda realizar prestamos nuevamente
};	
