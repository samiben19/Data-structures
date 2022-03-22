#pragma once

class Multime;
typedef int TElem;

class IteratorMultime
{
	friend class Multime;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(const Multime& m);	// Theta(1)		Best case = Worst case = Average case = Theta(1)

	//contine o referinta catre containerul pe care il itereaza
	const Multime& multime;
	/* aici e reprezentarea  specifica a iteratorului */
	int curent;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();					// Theta(1)		Best case = Worst case = Average case = Theta(1)
			
		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();					// Theta(1)		Best case = Worst case = Average case = Theta(1)

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;				// Theta(1)		Best case = Worst case = Average case = Theta(1)

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;			// Theta(1)		Best case = Worst case = Average case = Theta(1)
};
