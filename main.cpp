#include <iostream>
#include <string>
#include <limits>


#include "Library.h"
#include "Book.h"
#include "Journal.h"
#include "Ebook.h"
#include "Utils.h"


// Declaración de funciones de menú
void showMenu();
void addItemMenu(Library& lib);
void addUserMenu(Library& lib);
void loanItemMenu(Library& lib);
void returnMenu(Library& lib);
void saveLibraryData(Library& lib);
void loadLibraryData(Library& lib);
void searchAuthorMenu(Library& lib);
void exportStatsMenu(Library& lib);
void removeItemMenu(Library& lib);
void editItemMenu(Library& lib);
void blockUserMenu(Library& lib);
void unblockUserMenu(Library& lib);


int main() {
	Library lib;
	int option = 0;
	do {
		showMenu();
		std::cin >> option;
		clearInput();
		switch (option) {
		case 1: addItemMenu(lib);
			break;
		case 2: addUserMenu(lib);
			break;
		case 3: lib.listItems();
			break;
		case 4: loanItemMenu(lib);
			break;
		case 5: returnMenu(lib); 
			break;
		case 6: saveLibraryData(lib);
			break;
		case 7: loadLibraryData(lib); 
			break;
		case 8: searchAuthorMenu(lib);
			break;
		case 9: exportStatsMenu(lib); 
			break;
		case 10: removeItemMenu(lib); 
			break;
		case 11: editItemMenu(lib); 
			break;
		case 12: blockUserMenu(lib);
			break;
		case 13: unblockUserMenu(lib);
			break;
		case 0: break;
		default: std::cout << "Opcion no valida\n"; 
			break;
		}
	} while (option != 0);
}


void showMenu() {
	std::cout << "\n===== BIBLIOTECA =====\n";
	std::cout << "1. Annadir item\n";
	std::cout << "2. Annadir usuario\n";
	std::cout << "3. Listar items\n";
	std::cout << "4. Registrar prestamo\n";
	std::cout << "5. Registrar devolucion\n";
	std::cout << "6. Guardar datos\n";
	std::cout << "7. Cargar datos\n";
	std::cout << "8. Buscar por autor y listado ordenado por titulo\n";
	std::cout << "9.Exportar estadisticas de prestamos activos a CSV\n";
	std::cout << "10. Eliminar item\n";
	std::cout << "11. Editar item\n";
	std::cout << "12. Bloquear usuario\n";
	std::cout << "13. Desbloquear usuario\n";
	std::cout << "0. Salir\n";
	std::cout << "Opcion: ";
	std::cout << std::endl << std::endl;
}

void addItemMenu(Library& lib) {
	int itemType;
	std::string titulo, autor, licencia, expedicion;
	int volumen;
	std::cout << "Seleccione el tipo de item a annadir:\n1. Libro\n2. Revista\n3. Ebook\nOpcion: ";
	std::cin >> itemType;
	clearInput();
	switch (itemType) {
	case 1:
		std::cout << "Titulo: ";
		std::getline(std::cin, titulo);

		std::cout << "Autor: "; 
		std::getline(std::cin, autor);

		lib.addItem(new Book(titulo, autor));
		break;
	case 2:
		std::cout << "Titulo: "; 
		std::getline(std::cin, titulo);

		std::cout << "Volumen: ";
		std::cin >> volumen; clearInput();

		lib.addItem(new Journal(titulo, volumen));
		break;
	case 3:
		std::cout << "Licencia: ";
		std::getline(std::cin, licencia);

		std::cout << "F.expedicion: ";
		std::getline(std::cin, expedicion);

		lib.addItem(new Ebook(licencia, expedicion));
		break;

	default: std::cout << "Opcion no valida\n"; 
		break;
	}
}


void addUserMenu(Library& lib) {
	int id, opcion;
	std::string name;
	
	std::cout << "Ingrese ID de usuario: "; 
	std::cin >> id; 
	clearInput();

	std::cout << "Ingrese nombre de usuario: "; 
	std::getline(std::cin, name);

	std::cout << "Seleccione rol de usuario:\n1. Estudiante\n2. PDI\n3. PAS\nOpcion: "; 
	std::cin >> opcion; 
	clearInput();

	User::Role role = User::Student;
switch (opcion) { 
case 1: 
	role = User::Student; 
	break; 
case 2: 
	role = User::PDI;
	break; 
case 3: 
	role = User::PAS;
	break; 
default: std::cout << "Opcion no valida\n"; 
	return; 
}
						lib.addUser(new User(id, name, role));
}


void loanItemMenu(Library& lib) {
	int userId, itemIndex;
	std::string startDate, dueDate;

	std::cout << "Ingrese ID de usuario: ";
	std::cin >> userId;
	clearInput();

	User* user = lib.findUser(userId);
	if (!user) { 
		std::cout << "Usuario no encontrado.\n";
		return;
	}
	lib.listItemsWithIndex();

	std::cout << "Seleccione el indice del item a prestar: ";
	std::cin >> itemIndex;
	clearInput();

	Item* item = lib.getItem(itemIndex);

	if (!item) { 
		std::cout << "Item no encontrado.\n";
		return; 
	}

	std::cout << "Ingrese fecha de inicio (YYYY-MM-DD): "; 
	std::getline(std::cin, startDate);

	std::cout << "Ingrese fecha de vencimiento (YYYY-MM-DD): ";
	std::getline(std::cin, dueDate);

	lib.loanItem(user, item, startDate, dueDate);
}


void returnMenu(Library& lib) {
	int userId, itemIndex;
	std::string returnDate;
	std::cout << "Ingrese ID de usuario: "; 
	std::cin >> userId; clearInput();

	User* user = lib.findUser(userId);

	if (!user) { 
		std::cout << "Usuario no encontrado.\n"; 
	return; 
	}
	lib.listItemsWithIndex();

	std::cout << "Seleccione el indice del item a devolver: ";
	std::cin >> itemIndex; 
	clearInput();

	Item* item = lib.getItem(itemIndex);
	if (!item) { 
		std::cout << "Item no encontrado.\n"; 
		return;
	}
	std::cout << "Ingrese fecha de devolucion (YYYY-MM-DD): "; 
	std::getline(std::cin, returnDate);

	lib.returnItem(user, item, returnDate);
}

void saveLibraryData(Library& lib) {
	lib.saveItems("items.csv");
	lib.saveUsers("users.csv");
	lib.saveLoans("loans.csv");
}


void loadLibraryData(Library& lib) {
	lib.loadItems("items.csv");
	lib.loadUsers("users.csv");
	lib.loadLoans("loans.csv");
}


void searchAuthorMenu(Library& lib) {
	std::string autor;
	std::cout << "Introduce el autor a buscar: "; 
	std::getline(std::cin, autor);

	auto result = lib.buscarporAutor(autor);

	if (result.empty()) { 
		std::cout << "No se encontraron items del autor: " << autor << std::endl;
		return;
	}
	lib.sortByTitle(result);
	std::cout << "\nResultados ordenados por titulo:\n";
	lib.showItems(result);
}


void exportStatsMenu(Library& lib) {
	std::string filename;
	std::cout << "Nombre del archivo CSV a exportar: "; 
	std::getline(std::cin, filename);

	lib.exportActiveLoansCSV(filename);
}


void removeItemMenu(Library& lib) {
	int idx;
	lib.listItemsWithIndex();
	
	std::cout << "Indice del item a eliminar: "; 
	std::cin >> idx; 
	clearInput(); 

	lib.removeItem(idx);
}


void editItemMenu(Library& lib) {
	int idx;
	lib.listItemsWithIndex(); 
	
	std::cout << "Indice del item a editar: "; 
	std::cin >> idx; 
	clearInput(); 

	lib.editItem(idx);
}


void blockUserMenu(Library& lib) {
	int id; 

	std::cout << "ID del usuario a bloquear: "; 
	std::cin >> id; 
	clearInput(); 

	lib.blockUser(id);
}
void unblockUserMenu(Library& lib) { 
	int id; 

	std::cout << "ID del usuario a desbloquear: ";
	std::cin >> id; 
	clearInput(); 

	lib.unblockUser(id);
}