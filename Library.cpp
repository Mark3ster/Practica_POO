#include "Library.h"
#include "Book.h"
#include "Journal.h"
#include "Ebook.h"
#include "Utils.h"


#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>


Library::~Library() {
	for (User* u : users)
		delete u;
	users.clear();

	for (Loan* l : loans)
		delete l;
	loans.clear();
}


void Library::addItem(Item* item) { 
	catalog.addItem(item);
}
void Library::addUser(User* u) { 
	users.push_back(u); 
}
void Library::listItems() {
	catalog.listItems();
}


User* Library::findUser(int id) {
	for (auto u : users) 
		if (u->getId() == id) 
			return u;
	return nullptr;
}


Item* Library::getItem(int index) { 
	return catalog.get(index); 
}
void Library::listItemsWithIndex() { 
	catalog.listItemsWithIndex();
}


void Library::loanItem(User* user, Item* item, const std::string& start, const std::string& due) {
	if (userBlocked(user)) { std::cout << "Usuario bloqueado por sanciones acumuladas" << std::endl; 
	return; 
	}
	Ebook* ebook = dynamic_cast<Ebook*>(item);
	
	if (ebook) {
		if (bookExpired(ebook, start)) {
			std::cout << "No se puede prestar este Ebook. La licencia expiro el " << ebook->getExpiryDate() << std::endl;
			return;
		}
	}
	loans.push_back(new Loan(user, item, start, due));
	std::cout << "Prestamo registrado correctamente" << std::endl;
}


Loan* Library::findLoan(User* user, Item* item) {
	for (auto l : loans) {
		if (l->getUser() == user && l->getItem() == item && !l->isReturned()) 
			return l;
	}
	return nullptr;
}


void Library::returnItem(User* user, Item* item, const std::string& returnDate) {
	double fine;
	Loan* loan = findLoan(user, item);
	if (!loan) { 
		std::cout << "Prestamo no encontrado" << std::endl; 
		return;
	}
	
	loan->setReturnDate(returnDate);
	std::cout << "Devolucion registrada correctamente" << std::endl;


	 fine = calculateFineA1(loan->getDue(), returnDate);

	if (fine > 0) {
		user->addSanction(fine);
		std::cout << "Retraso detectado. Sancion aplicada: " << fine << " €" << std::endl;
		std::cout << "Sancion total acumulada del usuario: " << user->getSanction() << " €" << std::endl;
	}
}

bool Library::userBlocked(User* user) {
	if (user->getSanction() > 10) 
		return true;
	
	if (user->isManuallyBlocked()) 
		return true;
	return false;
}


bool Library::bookExpired(Ebook* ebook, const std::string& startDate) {
	int days = daysBetween(startDate, ebook->getExpiryDate());
	return days < 0;
}


void Library::saveItems(const std::string& filename) {
	std::ofstream file(filename);
	if (!file) { 
		std::cout << "Error al abrir " << filename << std::endl; 
		return; 
	
	}
	
	file << "type,title,author,volume,license,expiry\n";
	for (Item* item : catalogItems()) {
		if (Book* b = dynamic_cast<Book*>(item)) {
			file << "Book," << sanearCSV(b->getTitle()) << "," << sanearCSV(b->getAuthor()) << ",,,\n";
		}
	
		else if (Journal* j = dynamic_cast<Journal*>(item)) {
			file << "Journal," << sanearCSV(j->getTitle()) << ",," << j->getVolume() << ",,\n";
		}
	
		else if (Ebook* e = dynamic_cast<Ebook*>(item)) {
			file << "Ebook,,," << "," << sanearCSV(e->getLicense()) << "," << sanearCSV(e->getExpiryDate()) << "\n";
		}
	}
	
	file.close();
	std::cout << "Items guardados correctamente.\n";
}


const std::vector<Item*>& Library::catalogItems() const { 
	return catalog.getItems();
}


void Library::saveUsers(const std::string& filename) {
	std::ofstream file(filename);
	if (!file) { 
		std::cout << "Error al abrir " << filename << std::endl; 
	return;
	}

	file << "id,name,role,sanction\n";
	for (User* user : users) {
		file << user->getId() << "," << sanearCSV(user->getName()) << "," << user->getRole() << "," << user->getSanction() << "\n";
	
	}
	
	file.close();

	std::cout << "Usuarios guardados correctamente" << std::endl;
}


void Library::saveLoans(const std::string& filename) {
	int itemIndex;
	std::ofstream file(filename);
	if (!file) { 
		std::cout << "Error al abrir " << filename << std::endl;
		return;
	}
	
	
	file << "userId,itemIndex,startDate,dueDate,returnDate\n";
	for (Loan* loan : loans) {
		 itemIndex = findItemIndex(loan->getItem());
		file << loan->getUser()->getId() << "," << itemIndex << "," << loan->getStart() << "," << loan->getDue() << "," << (loan->isReturned() ? loan->getReturn() : "") << "\n";
	}
	
	file.close();
	std::cout << "Prestamos guardados correctamente" << std::endl;
}

int Library::findItemIndex(Item* it) {
	const auto& list = catalog.getItems();

	for (int i = 0; i < static_cast<int>(list.size()); ++i) 
		if (list[i] == it) 
		return i;
	return -1;
}


void Library::removeItem(int index) {
	const auto& items = catalog.getItems();

	if (index < 0 || index >= static_cast<int>(items.size())) { 
		std::cout << "Índice inválido.\n"; 
		return; 
	}

	Item* target = items[index];
	for (Loan* l : loans) {
		
		if (l->getItem() == target && !l->isReturned()) {
			std::cout << "No se puede eliminar: el item tiene un préstamo activo.\n"; 
			return;
		}
	}

	delete items[index];
	std::vector<Item*>& modifiable = const_cast<std::vector<Item*>&>(items);
	modifiable.erase(modifiable.begin() + index);

	std::cout << "Item eliminado correctamente.\n";
}


void Library::editItem(int index) {
	const auto& items = catalog.getItems();
	if (index < 0 || index >= static_cast<int>(items.size())) { 
		std::cout << "Índice inválido.\n";
		return; 
	}

	Item* old = items[index];
	
	if (Book* b = dynamic_cast<Book*>(old)) {

		std::string newTitle, newAuthor;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Nuevo titulo: ";
		std::getline(std::cin, newTitle);

		std::cout << "Nuevo autor: ";
		std::getline(std::cin, newAuthor);

		Item* replacement = new Book(newTitle, newAuthor);
		catalog.replaceItem(index, replacement);

		std::cout << "Libro editado correctamente.\n";
		return;
	}
	
	if (Journal* j = dynamic_cast<Journal*>(old)) {
		std::string newTitle;
		int newVolume;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Nuevo título: ";
		std::getline(std::cin, newTitle);

		std::cout << "Nuevo volumen: ";
		std::cin >> newVolume;

		Item* replacement = new Journal(newTitle, newVolume);
		catalog.replaceItem(index, replacement);

		std::cout << "Revista editada correctamente.\n";
		return;
	}
	
	if (Ebook* e = dynamic_cast<Ebook*>(old)) {
		std::string newLic, newExp;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Nueva licencia: ";
		std::getline(std::cin, newLic);

		std::cout << "Nueva fecha de expiración (YYYY-MM-DD): ";
		std::getline(std::cin, newExp);

		Item* replacement = new Ebook(newLic, newExp);
		catalog.replaceItem(index, replacement);

		std::cout << "Ebook editado correctamente.\n";
		return;
	}
	std::cout << "Tipo de item no editable.\n";
}

void Library::loadItems(const std::string& filename) {
	std::ifstream file(filename);
	int volume;
	if (!file) { 
		std::cout << "No se pudo abrir " << filename << std::endl;
	return;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		if (line.empty()) 
			continue;

		auto cols = dividirCSV(line);

		std::string type = cols.size() > 0 ? cols[0] : "";

		if (type == "Book") {
			std::string title = cols.size() > 1 ? cols[1] : "";
			std::string author = cols.size() > 2 ? cols[2] : "";
			
			addItem(new Book(title, author));
		}
		
		else if (type == "Journal") {
			std::string title = cols.size() > 1 ? cols[1] : "";
			 volume = cols.size() > 3 ? std::stoi(cols[3]) : 0;
			
			addItem(new Journal(title, volume));
		}
		
		else if (type == "Ebook") {
			std::string license = cols.size() > 4 ? cols[4] : "";
			std::string expiry = cols.size() > 5 ? cols[5] : "";
			
			addItem(new Ebook(license, expiry));
		}
	}

	std::cout << "Items cargados correctamente\n";
}


void Library::loadUsers(const std::string& filename) {
	std::ifstream file(filename);
	int id, role;
	if (!file) {
		std::cout << "No se pudo abrir " << filename << std::endl;
		return;
	}

	std::string line;

	std::getline(file, line);
	while (std::getline(file, line)) {
		if (line.empty()) 
			continue;

		auto cols = dividirCSV(line);

		 id = cols.size() > 0 ? std::stoi(cols[0]) : 0;
		std::string name = cols.size() > 1 ? cols[1] : "";
		 role = cols.size() > 2 ? std::stoi(cols[2]) : 0;

		double sanction = cols.size() > 3 ? std::stod(cols[3]) : 0.0;
		User* u = new User(id, name, static_cast<User::Role>(role));
		u->addSanction(sanction);

		addUser(u);
	}
	std::cout << "Usuarios cargados correctamente.\n";
}


void Library::loadLoans(const std::string& filename) {
	std::ifstream file(filename);
	int userId, itemIndex;
	if (!file) { 
		std::cout << "No se pudo abrir " << filename << std::endl; 
		return; 
	}
	
	std::string line;
	std::getline(file, line);
	
	while (std::getline(file, line)) {
		if (line.empty()) 
			continue;

		auto cols = dividirCSV(line);
		 userId = cols.size() > 0 ? std::stoi(cols[0]) : -1;
		 itemIndex = cols.size() > 1 ? std::stoi(cols[1]) : -1;
		std::string start = cols.size() > 2 ? cols[2] : "";

		std::string due = cols.size() > 3 ? cols[3] : "";
		std::string returnDate = cols.size() > 4 ? cols[4] : "";
		User* u = findUser(userId);

		Item* it = nullptr;
		try {
			it = getItem(itemIndex);
		}
		catch (...) { 
			it = nullptr;
		}

		if (!u || !it)
			continue;

		Loan* l = new Loan(u, it, start, due);
		if (!returnDate.empty()) l->setReturnDate(returnDate);
		loans.push_back(l);
	}
	std::cout << "Prestamos cargados correctamente\n";
}


std::vector<Item*> Library::buscarporAutor(const std::string& autor) {
	std::vector<Item*> resultados;
	for (Item* item : catalogItems()) {
		if (Book* b = dynamic_cast<Book*>(item)) {
			if (b->getAuthor() == autor) resultados.push_back(item);
		}
	}
	return resultados;
}

void Library::sortByTitle(std::vector<Item*>& vec) {
	std::sort(vec.begin(), vec.end(), [](Item* a, Item* b) {
		std::string titleA, titleB;

		if (Book* ba = dynamic_cast<Book*>(a)) 
			titleA = ba->getTitle();

		else if (Journal* ja = dynamic_cast<Journal*>(a))
			titleA = ja->getTitle();

		else titleA = a->info();

		if (Book* bb = dynamic_cast<Book*>(b)) 
			titleB = bb->getTitle();

		else if (Journal* jb = dynamic_cast<Journal*>(b)) 
			titleB = jb->getTitle();

		else titleB = b->info();

		return titleA < titleB;
		});
}


void Library::showItems(const std::vector<Item*>& vec) {
	for (Item* it : vec) std::cout << it->info() << std::endl;
}


void Library::exportActiveLoansCSV(const std::string& filename) {
	std::ofstream file(filename);
	if (!file) { 
		std::cout << "Error al abrir archivo " << filename << std::endl; 
	return;
	}

	file << "userid,item,start,due\n";

	for (Loan* l : loans) {
		if (!l->isReturned()) {
			file << l->getUser()->getId() << "," << sanearCSV(l->getItem()->info()) << "," << l->getStart() << "," << l->getDue() << "\n";
		}
	}

	file.close();
	std::cout << "Estadisticas exportadas correctamente a " << filename << std::endl;
}


void Library::blockUser(int userId) {
	User* u = findUser(userId);
	if (!u) {
		std::cout << "Usuario no encontrado.\n";
		return;
	}
	
	u->block();
	std::cout << "Usuario bloqueado manualmente.\n";
}


void Library::unblockUser(int userId) {
	User* u = findUser(userId);
	if (!u) {
		std::cout << "Usuario no encontrado.\n"; 
		return; 
	}
	
	
	u->unblock();
	std::cout << "Usuario desbloqueado correctamente.\n";
}