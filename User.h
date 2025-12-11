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


	int getId() const;	//su funcion es devolver el ID del usuario
	std::string getName() const;	//su funcion es devolver el nombre del usuario
	Role getRole() const;	//su funcion es devolver el rol del usuario
	double getSanction() const;	//su funcion es devolver el total de la sancion del usuario
	void addSanction(double amount);	//su funcion es agregar una cantidad especifica al monto de la sancion del usuario
	bool isManuallyBlocked() const;	//su funcion es verificar si el usuario ha sido bloqueado manualmente
	void block();	//su funcion es bloquear manualmente al usuario
	void unblock();	//su funcion es desbloquear manualmente al usuario
};