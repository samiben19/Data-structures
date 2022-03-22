#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

int Multime::aloca()
{
	// Sterge primul element din lista spatiului liber
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

void Multime::dealoca(int i)
{
	// Trece pozitia i in lista spatiului liber
	urm[i] = primLiber;
	primLiber = i;
}

int Multime::creeazaNod(TElem e)
{
	if (primLiber == NULL_TELEM)
		redim();
	int i = aloca();

	this->e[i] = e;
	urm[i] = NULL_TELEM;

	return i;
}

void Multime::redim()
{
	int capNou{ 2 * cap };

	TElem* eNou = new TElem[capNou];
	int* urmNou = new int[capNou];

	// Copiem vechile valori in noua zona
	for (int i = 0; i < cap; i++)
	{
		eNou[i] = e[i];
		urmNou[i] = urm[i];
	}

	// Reinitializare spatiului liber
	for (int i = cap; i < capNou - 1; i++)
		urmNou[i] = i + 1;
	urmNou[capNou - 1] = NULL_TELEM;

	// Eliberam vechea zona
	delete[] e;
	delete[] urm;

	// Vectorul indica spre noua zona
	e = eNou;
	urm = urmNou;
	primLiber = cap;
	cap = capNou;
}

Multime::Multime() {
	this->lg = 0;
	this->cap = 4;
	this->e = new TElem[cap];
	this->urm = new int[cap];
	// Lista e vida
	prim = -1;
	// Initializare spatiului liber
	for (int i = 0; i < cap - 1; i++)
		urm[i] = i + 1;
	urm[cap - 1] = NULL_TELEM;
	// Prima pozitie libera
	primLiber = 0;
}


bool Multime::adauga(TElem elem) {
	int i = prim;
	while (i != NULL_TELEM)
	{
		if (e[i] == elem)
			return false;
		i = urm[i];
	}
	lg++;
	int poz_nod = creeazaNod(elem);
	//e[poz_nod] = elem;
	urm[poz_nod] = prim;
	prim = poz_nod;
	return true;
}


bool Multime::sterge(TElem elem) {
	int curent = prim;
	int anterior = NULL_TELEM;
	while (curent != NULL_TELEM)
	{
		if (e[curent] == elem)
		{
			lg--;
			// Sterg dp prima pozitie
			if (curent == prim)
				prim = urm[prim];
			else
				urm[anterior] = urm[curent];
			dealoca(curent);
			return true;
		}
		anterior = curent;
		curent = urm[curent];
	}
	return false;
}


bool Multime::cauta(TElem elem) const {
	int i = prim;
	while (i != NULL_TELEM)
	{
		if (e[i] == elem)
			return true;
		i = urm[i];
	}
	return false;
}


int Multime::dim() const {
	return lg;
}

bool Multime::vida() const {
	return lg == 0;
}


Multime::~Multime() {
	delete[] e;
	delete[] urm;
}

void Multime::reuniune(const Multime& b)
{
	int curentB = b.prim;
	while (curentB != NULL_TELEM)
	{
		adauga(b.e[curentB]);
		curentB = b.urm[curentB];
	}
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

/*for (int i = 0; i < capNou; i++)
	std::cout << eNou[i] << ' ';
std::cout << '\n';
for (int i = 0; i < capNou; i++)
	std::cout << urmNou[i] << ' ';*/