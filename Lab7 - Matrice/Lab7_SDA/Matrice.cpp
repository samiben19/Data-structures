#include "Matrice.h"
#include <exception>
#include <iostream>

using namespace std;

Matrice::Matrice(int nrLinii, int nrColoane) {
	if (nrLinii <= 0 || nrColoane <= 0)
		throw exception("Dimensiune invalida !\n");
	n = nrLinii;
	m = nrColoane;
	radacina = nullptr;
}

void Matrice::distrugeRec(PNod p)
{
	if (p != nullptr) {
		distrugeRec(p->st);
		distrugeRec(p->dr);
		delete p;
	}
}

void Matrice::afisRec(PNod p)
{
	if (p != nullptr) {
		cout << p->e.e << " (" << p->e.i << ", " << p->e.j << ")\n";
		afisRec(p->st);
		afisRec(p->dr);
	}
}

void Matrice::afis()
{
	cout << "Afis:\n";
	afisRec(radacina);
}

Matrice::~Matrice()
{
	distrugeRec(radacina);
}

int Matrice::nrLinii() const {
	return n;
}

int Matrice::nrColoane() const {
	return m;
}

//PNod Matrice::adaugaRec(PNod p, TTrip e)
//{
//	if (p == nullptr)
//		p = new Nod(e, nullptr, nullptr);
//	else
//	{
//		if (e == p->e)
//		{
//			TElem old = p->e.e;
//			p->e = e;
//			throw old;
//		}
//		if (e < p->e)
//			p->st = adaugaRec(p->st, e);
//		else if (e > p->e)
//			p->dr = adaugaRec(p->dr, e);
//	}
//	return p;
//}

PNod Matrice::cauta(int i, int j) const
{
	PNod curent = radacina;
	TTrip cautat{ i,j,NULL_TELEMENT };

	while (curent != nullptr)
	{
		if (curent->e == cautat)
			return curent;
		if (cautat < curent->e)
			curent = curent->st;
		else
			curent = curent->dr;
	}
	return nullptr;
}

TElem Matrice::element(int i, int j) const {
	if (i < 0 || j < 0 || i >= n || j >= m)
		throw exception("Indici invalizi !\n");
	PNod element = cauta(i, j);

	if (element != nullptr)
		return element->e.e;
	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= n || j >= m)
		throw exception("Indici invalizi !\n");

	TTrip triplet{ i, j, e };
	//if (e == 0)	// Stergere
	//{
	//	TElem old = NULL_TELEMENT;
	//	stergeRec(radacina, triplet, old);
	//	return old;
	//}

	// Adaugare sau modificare
	PNod curent = radacina;
	PNod anterior = nullptr;

	while (curent != nullptr) // Cautam indicii
	{
		if (curent->e == triplet)
			break;
		anterior = curent;
		if (triplet < curent->e)
			curent = curent->st;
		else
			curent = curent->dr;
	}

	if (e == 0)
	{
		if (curent == nullptr)	// Nu am gasit, nu am ce sterge
			return NULL_TELEMENT;
		TElem old = curent->e.e;
		sterge(anterior, curent, triplet);
		return old;
	}

	if (radacina == nullptr)	// Initializare radacina
	{
		radacina = new Nod{ triplet,nullptr,nullptr };
		return NULL_TELEMENT;
	}

	if (curent != nullptr)	// Am gasit indicii, deci modificam
	{
		TElem old = curent->e.e;
		curent->e.e = e;
		return old;
	}
	// Nu am gasit indicii, deci adaugam
	PNod nou = new Nod{ triplet,nullptr,nullptr };
	if (triplet < anterior->e)
		anterior->st = nou;
	else
		anterior->dr = nou;

	return NULL_TELEMENT;
}

IteratorMatrice Matrice::iterator(int coloana) const
{
	if (coloana < 0 || coloana >= m)
		throw("Coloana invalida !\n");
	return IteratorMatrice(*this, coloana);
}

void Matrice::sterge(PNod anterior, PNod curent, TTrip triplet)
{
	// Cazul 1 - Frunza
	if (curent->st == nullptr && curent->dr == nullptr)
	{
		if (curent == radacina)
		{
			delete curent;
			radacina = nullptr;
			return;
		}
		if (anterior->st == curent)
			anterior->st = nullptr;
		else
			anterior->dr = nullptr;
		delete curent;
		return;
	}
	// Cazul 2 - Un singur fiu (stanga)
	if (curent->st != nullptr && curent->dr == nullptr)
	{
		if (anterior == nullptr)
		{
			radacina = curent->st;
			delete curent;
			return;
		}
		if (anterior->st == curent)
			anterior->st = curent->st;
		else
			anterior->dr = curent->st;
		delete curent;
		return;
	}
	// Cazul 3 - Un singur fiu (dreapta)
	if (curent->dr != nullptr && curent->st == nullptr)
	{
		if (anterior == nullptr)
		{
			radacina = curent->dr;
			delete curent;
			return;
		}
		if (anterior->st == curent)
			anterior->st = curent->dr;
		else
			anterior->dr = curent->dr;
		delete curent;
		return;
	}
	// Cazul 4 - Am si stanga si dreapta
	PNod maxp = curent->st;
	anterior = curent;
	while (maxp->dr != nullptr)
	{
		anterior = maxp;
		maxp = maxp->dr;
	}
	if (anterior == curent)
		anterior->st = nullptr;
	else
		anterior->dr = nullptr;
	/*if (maxp == curent)
	{
		radacina->e = curent->e;
		delete curent;
		return;
	}
	*/
	curent->e = maxp->e;
	delete maxp;
}

PNod Matrice::minNod(PNod nod)
{
	while (nod->st != nullptr)
		nod = nod->st;
	return nod;
}

PNod Matrice::stergeRec(PNod& curent, TTrip triplet, TElem& old)
{
	if (curent == nullptr)
		return curent;
	if (triplet < curent->e)	// Cautam nodul pe partea stanga
		curent->st = stergeRec(curent->st, triplet, old);
	else
		if (triplet > curent->e)	// Cautam nodul pe partea dreapta
			curent->dr = stergeRec(curent->dr, triplet, old);
		else // Am gasit nodul
		{
			if (old == NULL_TELEMENT)
				old = curent->e.e;
			// Cazul 1 - Frunza
			if (curent->st == nullptr && curent->dr == nullptr)
			{
				delete curent;
				curent = nullptr;
				return curent;
			}
			else
				// Cazul 2 - Are doar dreapta
				if (curent->st == nullptr)
				{
					PNod urm = curent->dr;
					delete curent;
					return urm;
				}
				else
					// Cazul 3 - Are doar stanga
					if (curent->dr == nullptr)
					{
						PNod urm = curent->st;
						delete curent;
						return urm;
					}
			// Cazul 4 - Are si stanga si dreapta
			PNod minP = minNod(curent->dr);		// Cautam cel mai din stanga nod al subarborelui drept (cel mai mic nod de pe dreapta)
			curent->e = minP->e;	// Inlocuim valoarea nodului de sters cu cea a nodului gasit si vom sterge acest nod t
			// Vom intra din nou intr-unul din cazurile 1,2 sau 3
			curent->dr = stergeRec(curent->dr, minP->e, old);
		}
	return curent;
}

IteratorMatrice::IteratorMatrice(const Matrice& m, int coloana): mat{m}, coloana{coloana}
{
	lista = new TElem[mat.n];
	for (int k = 0; k < mat.n; k++)
		lista[k] = mat.element(k, coloana);
	i = 0;
}

void IteratorMatrice::anterior()
{
	if (i < 0)
		throw exception("Iterator invalid !\n");
	i--;
}

void IteratorMatrice::urmator()
{
	if (i >= mat.n)
		throw exception("Iterator invalid !\n");
	i++;
}

bool IteratorMatrice::valid() const
{
	return i >= 0 && i < mat.n;
}

TElem IteratorMatrice::element() const
{
	if (!valid())
		throw exception("Iterator invalid !\n");
	return lista[i];
}

IteratorMatrice::~IteratorMatrice()
{
	delete[] lista;
}
