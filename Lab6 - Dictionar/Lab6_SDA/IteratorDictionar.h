#pragma once
#include "Dictionar.h"

class IteratorDictionar
{
	friend class Dictionar;
private:

    // Constructorul primeste o referinta catre Container
    //		Iteratorul va referi primul element din container
	IteratorDictionar(const Dictionar& d);				// Theta(1)			Best case = Worst case = Average case = Theta(1)

	// Contine o referinta catre containerul pe care il itereaza
	const Dictionar& dict;
	
	//* =-=-=-=-= Aici e reprezentarea specifica a iteratorului =-=-=-=-= *//
	int curent;
	void deplasare();									// Theta(n)			Best case = Worst case = Average case = Theta(n)
public:

		// Reseteaza pozitia iteratorului la inceputul containerului
		void prim();									// Theta(1)			Best case = Worst case = Average case = Theta(1)

		// Muta iteratorul in container
		//		Arunca exceptie daca iteratorul nu e valid
		void urmator();									// Theta(1)			Best case = Worst case = Average case = Theta(1)

		// Verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;								// Theta(1)			Best case = Worst case = Average case = Theta(1)

		// Returneaza valoarea elementului din container referit de iterator
		//		Arunca exceptie daca iteratorul nu e valid
		TElem element() const;							// Theta(1)			Best case = Worst case = Average case = Theta(1)
};
