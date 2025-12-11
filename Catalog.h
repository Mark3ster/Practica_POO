#pragma once


#include <vector>
#include "Item.h"


class Catalog {
private:
	std::vector<Item*> items;
public:
	~Catalog();
	void addItem(Item* item);	//su funcion es agregar un nuevo item al catalogo
	void listItems() const;	//su funcion es listar todos los items presentes en el catalogo
	Item* get(int index) const;	//su funcion es obtener un item especifico del catalogo basado en su indice
	int size() const;	//su funcion es devolver el numero total de items presentes en el catalogo
	void listItemsWithIndex() const;	//su funcion es listar todos los items del catalogo junto con sus indices correspondientes
	const std::vector<Item*>& getItems() const;	//su funcion es devolver una referencia constante al vector que contiene todos los items del catalogo
	void replaceItem(int index, Item* newItem);	//su funcion es reemplazar un item existente en el catalogo en un indice especifico con un nuevo item proporcionado
};