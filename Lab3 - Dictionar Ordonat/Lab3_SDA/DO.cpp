#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <exception>

using namespace std;

Nod::Nod(TElem e, PNod urm){
	this->e = e;
	this->urm = urm;
}
// Theta(1)

TElem Nod::element() {
	return e;
}
// Theta(1)

PNod Nod::urmator() {
	return urm;
}
// Theta(1)

DO::DO(Relatie r) {
	prim = nullptr;
	dimnr = 0;
	rel = r;
}
// Theta(1)

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
	// Best case: Theta(1), Worst case: O(n) => General O(n)
TValoare DO::adauga(TCheie c, TValoare v) {
	PNod curent = prim;
	PNod anterior = nullptr;
	while (curent != nullptr && rel(curent->e.first, c))
	{
		if (curent->e.first == c)
		{
			TValoare old = curent->e.second;
			curent->e.second = v;
			return old;
		}
		anterior = curent;
		curent = curent->urm;
	}
	dimnr++;
	TElem nou;
	nou.first = c;
	nou.second = v;
	PNod nod_nou = new Nod(nou, nullptr);

	// Daca trebuie adaugat pe prima pozitie
	if (curent == prim)
	{
		nod_nou->urm = prim;
		prim = nod_nou;
	}
	// Daca trebuie adaugat la sfarsit
	else if (curent == nullptr)
	{
		//nod_nou->urm = nullptr;
		anterior->urm = nod_nou;
	}
	// Daca trebuie adaugat undeva in interior
	else
	{
		nod_nou->urm = curent;
		anterior->urm = nod_nou;
	}
	return NULL_TVALOARE;
}


//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
	// Best case: Theta(1), Worst case: Theta(n) => General O(n)
TValoare DO::cauta(TCheie c) const {
	PNod curent = prim;
	if (curent != nullptr)
		if (!rel(prim->e.first, c))
			return NULL_TVALOARE;
	while (curent != nullptr)
	{
		if (!rel(curent->e.first, c))
			return NULL_TVALOARE;
		if (curent->e.first == c)
			return curent->e.second;
		curent = curent->urm;
	}
	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
	// Best case: Theta(1), Worst case: Theta(n) => General O(n)
TValoare DO::sterge(TCheie c) {
	PNod curent = prim;
	if (curent != nullptr)
		if (!rel(prim->e.first, c))
			return NULL_TVALOARE;
	PNod anterior = nullptr;
	while (curent != nullptr)
	{
		//if (!rel(curent->e.first, c))
			//return NULL_TVALOARE;
		if (curent->e.first == c)
		{
			dimnr--;
			TValoare old = curent->e.second;
			// Daca e pe prima pozitie
			if (anterior == nullptr)
			{
				prim = prim->urm;
				delete curent;
			}
			// Daca e pe ultima
			else if (curent->urm == nullptr)
			{
				anterior->urm = nullptr;
				delete curent;
			}
			// Daca e undeva la mijloc
			else
			{
				anterior->urm = curent->urm;
				delete curent;
			}
			return old;
		}
		anterior = curent;
		curent = curent->urm;
	}
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
	// Theta(1)
int DO::dim() const {
	return dimnr;
}

//verifica daca dictionarul e vid
	// Theta(1)
bool DO::vid() const {
	if (prim != nullptr)
		return false;
	return true;
}

// Theta(1)
Iterator DO::iterator() const {
	return Iterator(*this);
}

// Theta(1)
DO::~DO() {
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
}
