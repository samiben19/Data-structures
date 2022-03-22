#pragma once
#define NULL_TELEMENT 0

class Nod;

typedef Nod* PNod;
typedef int TElem;

class TTrip
{
private:
	int i, j;
	TElem e;
public:
	friend class Matrice;
	friend class IteratorMatrice;
	TTrip() = default;
	TTrip(int i, int j, TElem e) {
		this->i = i;
		this->j = j;
		this->e = e;
	}
	friend bool operator==(const TTrip& t1, const TTrip& t2) { return t1.i == t2.i && t1.j == t2.j; }
	friend bool operator!=(const TTrip& t1, const TTrip& t2) { return !(t1 == t2); }

	friend bool operator<(const TTrip& t1, const TTrip& t2) { if (t1.i == t2.i) return t1.j < t2.j; return t1.i < t2.i; }
	friend bool operator>(const TTrip& t1, const TTrip& t2) { if (t1.i == t2.i) return t1.j > t2.j; return t1.i > t2.i; }

	friend bool operator<=(const TTrip& t1, const TTrip& t2) { return !(t1 > t2); }
	friend bool operator>=(const TTrip& t1, const TTrip& t2) { return !(t1 < t2); }
};

class Nod
{
private:
	TTrip e;
	PNod st, dr;
public:
	friend class Matrice;
	friend class IteratorMatrice;
	Nod(TTrip e, PNod st, PNod dr) {
		this->e = e;
		this->st = st;
		this->dr = dr;
	}
};

class IteratorMatrice;

class Matrice {
	friend class IteratorMatrice;
private:
	//* =-=-=-=-= Aici e reprezentarea =-=-=-=-= *//
	PNod radacina;	// pointer catre nodul radacina
	int n, m;	// n linii si m coloane

	//PNod adaugaRec(PNod p, TTrip e);
	PNod cauta(int i, int j) const;		// Functia care cauta indicii i si j si returneaza nodul		Complexitate: O(h), h - inaltimea arborelui
	void sterge(PNod anterior, PNod curent, TTrip triplet);		//					Complexitate: O(h)
	PNod minNod(PNod nod);															
	PNod stergeRec(PNod& curent, TTrip triplet, TElem& old);	//					Complexitate: O(h)

	void distrugeRec(PNod p);									//					Complexitate: O(n*m)	Best case = Theta(1), Worst case = Theta(n*m)
	void afisRec(PNod p);

public:
	void afis();
	// Constructor
	// Se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);						// Theta(1)

	//destructor
	~Matrice();													// Theta(h)

	// Returnare element de pe o linie si o coloana
	//		Se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//		Indicii se considera incepand de la 0
	TElem element(int i, int j) const;							// O(h)			Best case = Theta(1), Worst case = Theta(h)

	// Returnare numar linii
	int nrLinii() const;										// Theta(1)

	// Returnare numar coloane
	int nrColoane() const;										// Theta(1)

	// Modificare element de pe o linie si o coloana si returnarea vechii valori
	//		Se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem e);						// O(h)			Best case = Theta(1), Worst case = Theta(h)

	IteratorMatrice iterator(int coloana) const;				// Theta(h * mat.n)
};

class IteratorMatrice
{
	friend class Matrice;
private:
	IteratorMatrice(const Matrice& m, int coloana);
	/*
	* Preconditii:	m aparine Matrice
	*				coloana numar intreg
	* Postconditii: it apartine IteratorMatrice
	* 
	* Complexitate timp: Theta(h * mat.n)
	* Complexitate spatiu: Theta(mat.n)
	* 
	* Subalgoritm IteratorMatrice(m, coloana, it)
	*	lista <- un nou vector de TElem, cu dimensiunea de mat.n
	*	Pentru k <- 0, k < mat.n executa
	*		lista[k] <- element(mat,k,coloana)
	*	sf_Pentru
	*	i <- 0
	* sf_Subalgoritm
	*/

	int coloana;
	int i;
	const Matrice& mat;

	TElem* lista;
public:
	void anterior();		// Theta(1)
	void urmator();			// Theta(1)
	bool valid() const;		// Theta(1)
	TElem element() const;	// Theta(1)
	~IteratorMatrice();		// Theta(1)
};