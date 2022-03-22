#include <assert.h>
#include "Dictionar.h"
#include "IteratorDictionar.h"

void testAll1();
void testAll2();

void test_cerinta()
{
	Dictionar a;
	assert(a.adauga(5, 5) == NULL_TVALOARE);
	assert(a.adauga(-1, -1) == NULL_TVALOARE);
	assert(a.adauga(10, 10) == NULL_TVALOARE);
	assert(a.adauga(7, 7) == NULL_TVALOARE);

	Dictionar b;
	assert(b.adauga(5, 5) == NULL_TVALOARE);
	assert(b.adauga(-1, -1) == NULL_TVALOARE);
	assert(b.adauga(10, 10) == NULL_TVALOARE);
	assert(b.adauga(7, 7) == NULL_TVALOARE);
	assert(b.adauga(-7, -7) == NULL_TVALOARE);

	assert(b.adaugaInexistente(a) == 0);
	assert(b.adaugaInexistente(b) == 0);
	assert(a.adaugaInexistente(b) == 1);
}

void testAll() 
{ //apelam fiecare functie sa vedem daca exista
	Dictionar d;
	assert(d.vid() == true);
	assert(d.dim() == 0); //adaug niste elemente
	assert(d.adauga(5, 5) == NULL_TVALOARE);
	assert(d.adauga(1, 111) == NULL_TVALOARE);
	assert(d.adauga(10, 110) == NULL_TVALOARE);
	assert(d.adauga(7, 7) == NULL_TVALOARE);
	assert(d.adauga(1, 1) == 111);
	assert(d.adauga(10, 10) == 110);
	assert(d.adauga(-3, -3) == NULL_TVALOARE);
	assert(d.dim() == 5);
	assert(d.cauta(10) == 10);
	assert(d.cauta(16) == NULL_TVALOARE);
	assert(d.sterge(1) == 1);
	assert(d.sterge(6) == NULL_TVALOARE);
	assert(d.dim() == 4);

	TElem e;
	IteratorDictionar id = d.iterator();
	id.prim();
	int s1 = 0, s2 = 0;
	while (id.valid()) 
	{
		e = id.element();
		s1 += e.first;
		s2 += e.second;
		id.urmator();
	}
	assert(s1 == 19);
	assert(s2 == 19);
	//testAll1();
	//testAll2();
	test_cerinta();
}

void testAll1()
{
	Dictionar d;
	assert(d.vid() == true);
	assert(d.dim() == 0); //adaug niste elemente
	assert(d.adauga(5, 5) == NULL_TVALOARE);
	assert(d.adauga(15, 15) == NULL_TVALOARE);
	assert(d.adauga(13, 13) == NULL_TVALOARE);
	assert(d.adauga(22, 22) == NULL_TVALOARE);
	assert(d.adauga(20, 20) == NULL_TVALOARE);
	assert(d.adauga(35, 35) == NULL_TVALOARE);
	assert(d.adauga(30, 30) == NULL_TVALOARE);
	assert(d.adauga(32, 32) == NULL_TVALOARE);
	assert(d.adauga(2, 2) == NULL_TVALOARE);
	assert(d.dim() == 9);
	//d.afis();
	d.sterge(5);
	assert(d.dim() == 8);
	//d.afis();
}

void testAll2()
{
	Dictionar d;
	assert(d.vid() == true);
	assert(d.dim() == 0); //adaug niste elemente
	assert(d.adauga(25, 25) == NULL_TVALOARE);
	assert(d.adauga(5, 5) == NULL_TVALOARE);
	assert(d.adauga(10, 10) == NULL_TVALOARE);
	assert(d.adauga(15, 15) == NULL_TVALOARE);
	assert(d.adauga(11, 11) == NULL_TVALOARE);
	assert(d.adauga(3, 3) == NULL_TVALOARE);
	assert(d.adauga(2, 2) == NULL_TVALOARE);
	assert(d.dim() == 7);
	//d.afis();
	assert(d.sterge(10) == 10);
	assert(d.dim() == 6);
	//d.afis();
}