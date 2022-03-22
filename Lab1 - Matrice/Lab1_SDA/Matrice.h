#pragma once

typedef int TElem;


#define NULL_TELEMENT 0

class Matrice {

private:
	/* aici e reprezentarea */
	int nr_linii;
	int nr_coloane;

	typedef struct
	{
		int linie, coloana;
		TElem val;
	}Triplet;

	int cap;
	int dim;
	Triplet* elems;

	void ensure();
	bool valid(int i, int j) const;

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	// Theta(1)
	Matrice(int nrLinii, int nrColoane);

	//destructor
	// Theta(1)
	~Matrice();


	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	// Best: Theta(1), Worse: Theta(dim) => O(dim/2)
	TElem element(int i, int j) const;

	// returnare numar linii
	// Theta(1)
	int nrLinii() const;

	// returnare numar coloane
	// Theta(1)
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	// Best: Theta(1), Worse: Theta(dim) => O(dim)
	// dim - nr elemente din matrice diferite de 0
	TElem modifica(int i, int j, TElem);
};







