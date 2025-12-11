#pragma once


#include <string>
#include <vector>


std::vector<std::string> dividirCSV(const std::string& line);//funcion que divide una cadena CSV en un vector de cadenas, separando los valores por comas
std::string sanearCSV(const std::string& s);//funcion que elimina los espacios en blanco iniciales y finales de una cadena


int toDays(int year, int month, int day);//funcion que convierte una fecha dada en dias totales desde un punto de referencia fijo
void parseDate(const std::string& s, int& y, int& m, int& d);//funcion que analiza una cadena de fecha en formato "YYYY-MM-DD" y extrae el año, mes y día como enteros
int daysBetween(const std::string& a, const std::string& b);//funcion que calcula la diferencia en dias entre dos fechas dadas en formato "YYYY-MM-DD"
double calculateFineA1(const std::string& dueDate, const std::string& returnDate);//funcion que calcula la multa basada en las fechas de vencimiento y devolución dadas en formato "YYYY-MM-DD"


void clearInput();//para limpiar el buffer
