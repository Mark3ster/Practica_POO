#pragma once


#include <string>
#include <vector>


std::vector<std::string> dividirCSV(const std::string& line);
std::string sanearCSV(const std::string& s);


int toDays(int year, int month, int day);
void parseDate(const std::string& s, int& y, int& m, int& d);
int daysBetween(const std::string& a, const std::string& b);
double calculateFineA1(const std::string& dueDate, const std::string& returnDate);


void clearInput();
