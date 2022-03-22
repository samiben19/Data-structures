#include "Matrice.h"
#include <exception>

using namespace std;

Matrice::Matrice(int n, int m) {
	if (n <= 0 || m <= 0)
		throw exception();
	nr_linii = n;
	nr_coloane = m;

	cap = 2;
	dim = 0;
	elems = new Triplet[cap];
}

Matrice::~Matrice() {
	delete[] elems;
}

bool Matrice::valid(int i, int j) const{
	if (i < 0 || i > nr_linii || j < 0 || j > nr_coloane)
		return false;
	return true;
}

void Matrice::ensure()
{
	if (dim >= cap)
	{
		// Daca nu mai exista spatiu, alocam memorie dubla
		Triplet* elems_new = new Triplet[cap * 2];
		// Copiem vechile valori in noua zona de memorie
		for (int I = 0; I < dim; I++)
			elems_new[I] = elems[I];
		// Dublam capacitatea
		cap *= 2;
		// Eliberam vechea zona
		delete[] elems;
		// Indicam spre noua zona
		elems = elems_new;
	}
}

int Matrice::nrLinii() const{
	return this->nr_linii;
}


int Matrice::nrColoane() const{
	return this->nr_coloane;
}


TElem Matrice::element(int i, int j) const{
	// Daca indicii sunt invalizi
	if (!valid(i,j))
		throw exception();
	int pst = 0, pdr = dim - 1;
	// Cautam sa vedem daca exista in vector
	while (pst <= pdr)
	{
		if (elems[pst].linie == i && elems[pst].coloana == j)
			return elems[pst].val;
		if (elems[pdr].linie == i && elems[pdr].coloana == j)
			return elems[pdr].val;
		pst++;
		pdr--;
	}
	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) {
	// Daca indicii sunt invalizi
	if (!valid(i,j))
		throw exception();
	int st = 0, dr = dim - 1;
	// Cautam sa vedem daca exista in vector
	while (st <= dr)
	{
		if (elems[st].linie == i && elems[st].coloana == j)
		{
			TElem old = elems[st].val;
			elems[st].val = e;
			return old;
		}
		if (elems[dr].linie == i && elems[dr].coloana == j)
		{
			TElem old = elems[dr].val;
			elems[dr].val = e;
			return old;
		}
		st++;
		dr--;
	}

	ensure();

	st = 0;
	dr = dim - 1;
	while (st <= dr)
	{
		if (!(st < dim && (elems[st].linie < i || (elems[st].linie == i && elems[st].coloana < j))))
		{
			break;
		}
		if (!(dr > 0 && (elems[dr].linie > i || (elems[dr].linie == i && elems[dr].coloana > j))))
		{
			st = dr;
			break;
		}
		st++;
		dr--;
	}
	for (int I = dim; I > st; I--)
		elems[I] = elems[I - 1];
	elems[st].linie = i;
	elems[st].coloana = j;
	elems[st].val = e;
	dim++;
	return NULL_TELEMENT;

	//if (elems[dim - 1].linie < i || (elems[dim - 1].linie == i && elems[dim - 1].coloana < j))
	//{
	//	elems[dim].linie = i;
	//	elems[dim].coloana = j;
	//	elems[dim].val = e;
	//	dim++;
	//	return NULL_TELEMENT;
	//}
	//// Daca nu ii gasim in vector cautam pozitia unde ar trebui sa se afle (sa fie in ordine lexicografica)
	//poz = 0;
	//while (poz < dim && (elems[poz].linie < i || (elems[poz].linie == i && elems[poz].coloana < j)))
	//	poz++;
	//for (int I = dim; I > poz; I--)
	//	elems[I] = elems[I - 1];
	//elems[poz].linie = i;
	//elems[poz].coloana = j;
	//elems[poz].val = e;
	//dim++;
	//return NULL_TELEMENT;
}
