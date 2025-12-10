#include "Utils.h"


#include <sstream>
#include <algorithm>


std::vector<std::string> dividirCSV(const std::string& line) {
	std::vector<std::string> result;
	std::string field;
	bool insideQuotes = false;


	for (size_t i = 0; i < line.size(); ++i) {
		char c = line[i];
		if (c == '"') {
			// manejar comillas escapadas "" dentro de campo
			if (insideQuotes && i + 1 < line.size() && line[i + 1] == '"') {
				field.push_back('"');
				++i; // saltar la comilla escapada
			}
			else {
				insideQuotes = !insideQuotes;
			}
		}
		else if (c == ',' && !insideQuotes) {
			result.push_back(field);
			field.clear();
		}
		else {
			field.push_back(c);
		}
	}
	result.push_back(field);
	return result;
}


std::string sanearCSV(const std::string& s) {
	std::string result = s;
	size_t pos = 0;
	while ((pos = result.find('"', pos)) != std::string::npos) {
		result.insert(pos, "\"");
		pos += 2; // avanzar más allá de la comilla insertada
	}
	if (result.find(',') != std::string::npos || result.find('"') != std::string::npos) {
		result = '"' + result + '"';
	}
	return result;
}

int toDays(int year, int month, int day) {
	if (month < 3) {
		year--;
		month += 12;
	}
	return 365 * year + year / 4 - year / 100 + year / 400 + (153 * (month - 3) + 2) / 5 + day - 1;
}


void parseDate(const std::string& s, int& y, int& m, int& d) {
	char dash1, dash2;
	std::stringstream ss(s);
	ss >> y >> dash1 >> m >> dash2 >> d;
}


int daysBetween(const std::string& a, const std::string& b) {
	int y1, m1, d1;
	int y2, m2, d2;
	parseDate(a, y1, m1, d1);
	parseDate(b, y2, m2, d2);
	int dayA = toDays(y1, m1, d1);
	int dayB = toDays(y2, m2, d2);
	return dayB - dayA;
}


double calculateFineA1(const std::string& dueDate, const std::string& returnDate) {
	int delay = daysBetween(dueDate, returnDate);
	if (delay <= 0) return 0.0;
	double fine = delay * 0.10;
	if (fine > 15.0) fine = 15.0;
	return fine;
}


#include <iostream>
#include <limits>
void clearInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}