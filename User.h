#pragma once


#include <string>


class User {
public:
	enum Role { Student, PDI, PAS };
private:
	int id;
	std::string name;
	Role role;
	double sanctionAmount;
	bool manuallyBlocked;
public:
	User(int id, const std::string& name, Role role);
	~User() = default;


	int getId() const;
	std::string getName() const;
	Role getRole() const;
	double getSanction() const;
	void addSanction(double amount);
	bool isManuallyBlocked() const;
	void block();
	void unblock();
};