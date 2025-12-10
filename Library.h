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


	void addItem(Item* item);
	void addUser(User* u);
	void listItems();
	User* findUser(int id);
	Item* getItem(int index);
	void listItemsWithIndex();
	void loanItem(User* user, Item* item, const std::string& start, const std::string& due);
	Loan* findLoan(User* user, Item* item);
	void returnItem(User* user, Item* item, const std::string& returnDate);


	bool userBlocked(User* user);
	bool bookExpired(class Ebook* ebook, const std::string& startDate);


	void saveItems(const std::string& filename);
	const std::vector<Item*>& catalogItems() const;


	void saveUsers(const std::string& filename);
	void saveLoans(const std::string& filename);


	void loadItems(const std::string& filename);
	void loadUsers(const std::string& filename);
	void loadLoans(const std::string& filename);


	std::vector<Item*> buscarporAutor(const std::string& autor);
	void sortByTitle(std::vector<Item*>& vec);
	void showItems(const std::vector<Item*>& vec);
	void exportActiveLoansCSV(const std::string& filename);
	int findItemIndex(Item* it);
	void removeItem(int index);
	void editItem(int index);
	void blockUser(int userId);
	void unblockUser(int userId);
};
