#include "User.h"


User::User(int id_, const std::string& name_, Role role_) : id(id_), name(name_), role(role_), sanctionAmount(0.0), manuallyBlocked(false) {}


int User::getId() const { return id; }
std::string User::getName() const { return name; }
User::Role User::getRole() const { return role; }
double User::getSanction() const { return sanctionAmount; }
void User::addSanction(double amount) { sanctionAmount += amount; }
bool User::isManuallyBlocked() const { return manuallyBlocked; }
void User::block() { manuallyBlocked = true; }
void User::unblock() { manuallyBlocked = false; }