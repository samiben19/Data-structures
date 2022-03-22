#pragma once

#define NULL_TVALOARE -1
#include <utility>

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class Iterator;
class Nod;
typedef Nod* PNod;

typedef bool(*Relatie)(TCheie, TCheie);



class Nod
{
private:
	TElem e;
	PNod urm;
public:
	friend class DO;
	// Constructor
	Nod(TElem e, PNod urm);

	TElem element();
	PNod urmator();
};

class DO {
	friend class Iterator;
    private:
	/* aici e reprezentarea */
		PNod prim;
		int dimnr;
		Relatie rel;
    public:

	// constructorul implicit al dictionarului
	DO(Relatie r);


	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	//verifica daca dictionarul e vid
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;


	// destructorul dictionarului
	~DO();

};
