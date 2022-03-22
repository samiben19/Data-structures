#include <assert.h>
#include "Matrice.h"
//#include <iostream>

using namespace std;

void testStergere()
{
	Matrice m(15, 15);
	assert(m.nrLinii() == 15);
	assert(m.nrColoane() == 15);
	m.modifica(0, 8, 8);
	m.modifica(0, 3, 3);
	m.modifica(0, 1, 1);
	m.modifica(0, 10, 10);
	m.modifica(0, 14, 14);
	m.modifica(0, 12, 12);
	m.modifica(0, 6, 6);
	m.modifica(0, 4, 4);
	m.modifica(0, 7, 7);
	m.modifica(0, 13, 13);
	//m.afis();
	assert(m.modifica(0, 3, 0) == 3);
	assert(m.modifica(0, 8, 0) == 8);
	assert(m.modifica(0, 10, 0) == 10);
	assert(m.modifica(0, 10, 0) == 0);
	assert(m.modifica(0, 6, 0) == 6);
	assert(m.modifica(0, 4, 0) == 4);
	assert(m.modifica(0, 7, 0) == 7);
	assert(m.modifica(0, 12, 0) == 12);
	assert(m.modifica(0, 13, 0) == 13);
	assert(m.modifica(0, 1, 0) == 1);
	assert(m.modifica(0, 14, 0) == 14);
	//m.afis();
}

void testIterator()
{
	int linii{ 4 }, coloane{ 6 };
	Matrice m(linii, coloane);
	assert(m.nrLinii() == linii);
	assert(m.nrColoane() == coloane);
	int e{ 0 };
	for (int i = 0; i < linii; i++)
		for (int j = 0; j < coloane; j++)
			m.modifica(i, j, e++);

	for (int j = 0; j < coloane; j++)
	{
		IteratorMatrice it = m.iterator(j);
		int el = j;
		while (it.valid())
		{
			assert(it.element() == el);
			el += coloane;
			it.urmator();
		}
		assert(!it.valid());
		it.anterior();
		el -= coloane;
		while (it.valid())
		{
			assert(it.element() == el);
			el -= coloane;
			it.anterior();
		}
	}
}

void testAll()	//apelam fiecare functie sa vedem daca exista
{	
	Matrice m(4, 4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modifica(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEMENT);
	//testStergere();
	testIterator();
}
