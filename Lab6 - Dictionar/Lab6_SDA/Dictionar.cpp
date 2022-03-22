#include "Dictionar.h"
#include "IteratorDictionar.h"
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

void Dictionar::actPrimLiber()
{
	primLiber++;
	while (primLiber < cap && ocupat[primLiber])  //e[primLiber] != NULL_TELEM
		primLiber++;
}

void Dictionar::redim()
{
	int capVechi{ cap };

	TElem* eVechi = new TElem[capVechi];
	int* urmVechi = new int[capVechi];
	bool* ocupatVechi = new bool[capVechi];

	for (int i = 0; i < capVechi; i++) {
		eVechi[i] = e[i];
		urmVechi[i] = urm[i];
		ocupatVechi[i] = ocupat[i];
	}

	cap *= 2;

	delete[] e;
	delete[] urm;
	delete[] ocupat;

	e = new TElem[cap];
	urm = new int[cap];
	ocupat = new bool[cap];

	n = 0;
	primLiber = 0;

	for (int i = 0; i < cap; i++) {
		e[i] = NULL_TELEM;
		urm[i] = NULL_TVALOARE;
		ocupat[i] = false;
	}

	int i = 0;
	while (i < capVechi)
	{
		if (ocupatVechi[i])
			adauga(eVechi[i].first, eVechi[i].second);
		i++;
	}

	delete[] eVechi;
	delete[] urmVechi;
	delete[] ocupatVechi;
}

int Dictionar::dispersie(TCheie c)
{
	return abs(c) % cap;
}

void Dictionar::afis(int start, int final)
{
	cout << setw(20) << "Indice" << setw(20) << "Cheie" << setw(20) << "Urmator\n";
	for (int i = start; i < (final-start)/4; i++)
	{
		cout << setw(10) << i << ' ' << setw(20) << e[i].first << ' ' << setw(20) << urm[i]
			<< setw(10) << i + (final - start) / 4 << ' ' << setw(20) << e[i + (final - start) / 4].first << ' ' << setw(20) << urm[i + (final - start) / 4]
			<< setw(10) << i + (final - start) * 2 / 4 << ' ' << setw(20) << e[i + (final - start) * 2 / 4].first << ' ' << setw(20) << urm[i + (final - start) * 2 / 4]
			<< setw(10) << i + (final - start) * 3 / 4 << ' ' << setw(20) << e[i + (final - start) * 3 / 4].first << ' ' << setw(20) << urm[i + (final - start) * 3 / 4] << '\n';
	}
	cout << "\n\n";
}

Dictionar::Dictionar() : n{ 0 }, primLiber{ 0 }, cap{ MAX },
						e{ new TElem[cap] }, urm{ new int[cap] }, ocupat{ new bool[cap] }
{
	for (int i = 0; i < cap; i++) {
		e[i] = NULL_TELEM;
		urm[i] = NULL_TVALOARE;
		ocupat[i] = false;
	}
}

Dictionar::~Dictionar() {
	delete[] e;
	delete[] urm;
	delete[] ocupat;
}

int Dictionar::adaugaInexistente(Dictionar& d)
{
	int k{ 0 };
	IteratorDictionar id = d.iterator();
	
	while (id.valid())
	{
		TElem el = id.element();
		int i = dispersie(el.first);

		if (cauta(el.first) == NULL_TVALOARE)
		{
			adauga(el.first, el.second);
			k++;
		}

		/*while (e[i].first != el.first && urm[i] != NULL_TVALOARE)
			i = urm[i];

		if (!(e[i].first == el.first && ocupat[i]))
		{
			adauga(el.first, el.second);
			k++;
		}*/
		id.urmator();
	}
	return k;
}


TValoare Dictionar::adauga(TCheie c, TValoare v){
	int i = dispersie(c); // Locatia de dispersie a cheii

	if (!ocupat[i])	// Pozitia e libera
	{
		n++;
		ocupat[i] = true;
		e[i] = TElem(c, v);
		if (i == primLiber)
			actPrimLiber();
		if ((double)n / cap >= 0.75 || primLiber >= cap)
			redim();
		return NULL_TVALOARE;
	}
	if (e[i].first == c) // are acceasi cheie
	{
		TValoare old = e[i].second;
		e[i] = TElem(c, v);
		return old;
	}

	int j = NULL_TVALOARE;
	// Daca pozitia nu e libera sau nu s-a gasit din prima cheia
	while (i != NULL_TVALOARE && e[i].first != c)
	{
		j = i;
		i = urm[i];
	}

	if (i != NULL_TVALOARE) // Am gasit cheia
	{
		TValoare old = e[i].second;
		e[i] = TElem(c, v);
		return old;
	}

	// Cheia nu exista
	n++;
	if (primLiber <= cap - 1) // Tabela nu e plina
	{
		e[primLiber] = TElem(c, v);
		ocupat[primLiber] = true;
		urm[j] = primLiber;
		actPrimLiber();
	}
	if ((double)n / cap >= 0.75 || primLiber >= cap)
		redim();

	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) {
	int i = dispersie(c);

	while (e[i].first != c && urm[i] != NULL_TVALOARE)
		i = urm[i];

	if (e[i].first == c && ocupat[i])
		return e[i].second;
	return NULL_TVALOARE;
}


TValoare Dictionar::sterge(TCheie c){
	if (vid())
		return NULL_TVALOARE;
	int i = dispersie(c);

	// Nu exista coliziune, se poate sterge
	if (urm[i] == NULL_TVALOARE)
	{
		if (e[i].first == c && ocupat[i])
		{
			n--;
			TValoare old = e[i].second;
			e[i] = NULL_TELEM;
			ocupat[i] = false;
			return old;
		}
		return NULL_TVALOARE;
	}

	// Cautam cheia
	int anterior = NULL_TVALOARE;
	while (e[i].first != c && urm[i] != NULL_TVALOARE)
	{
		anterior = i;
		i = urm[i];
	}
	
	// Nu exista cheia
	if(e[i].first != c && ocupat[i])
		return NULL_TVALOARE;

	// Cheia exista pe pozitia i
	TValoare old = e[i].second;
	n--;

	// Este ultimul din inlantuire
	if (urm[i] == NULL_TVALOARE)
	{
		urm[anterior] = NULL_TVALOARE;
		ocupat[i] = false;
		e[i] = NULL_TELEM;
		return old;
	}
	
	int anterior_copie = anterior;
	while (true)
	{
		int j = urm[i];
		anterior_copie = i;

		if (j == NULL_TVALOARE)
			break;

		while (dispersie(e[j].first) != i && j != NULL_TVALOARE)
		{
			anterior_copie = j;
			j = urm[j];
		}

		if (j == NULL_TVALOARE)
			break;
		else
		{
			e[i] = e[j];
			anterior = anterior_copie;
			i = j;
		}
	}
	
	ocupat[i] = false;
	e[i] = NULL_TELEM;
	if (anterior != -1)
		urm[anterior] = urm[i];
	urm[i] = NULL_TVALOARE;
	return old;
}


int Dictionar::dim() const {
	return n;
}

bool Dictionar::vid() const{
	return n == 0;
}


IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}


