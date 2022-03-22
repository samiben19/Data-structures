#include "TestScurt.h"
#include <assert.h>
#include "Multime.h"
#include "IteratorMultime.h"

void testReuniune()
{
	Multime a;
	Multime b;
	assert(a.vida() == true);
	assert(a.dim() == 0);
	assert(a.adauga(1) == true);
	assert(a.adauga(2) == true);
	assert(a.adauga(3) == true);
	assert(a.adauga(4) == true);

	assert(b.vida() == true);
	assert(b.dim() == 0);
	assert(b.adauga(3) == true);
	assert(b.adauga(4) == true);
	assert(b.adauga(5) == true);
	assert(b.adauga(6) == true);

	assert(a.dim() == 4);
	assert(b.dim() == 4);
	a.reuniune(b);
	assert(a.dim() == 6);
	IteratorMultime im = a.iterator();
	im.prim();
	int s = 0;
	while (im.valid()) {
		TElem e = im.element();
		s += e;
		im.urmator();
	}
	assert(s == 21);
}

void testAll() { //apelam fiecare functie sa vedem daca exista
	Multime m;
	assert(m.vida() == true);
	assert(m.dim() == 0); //adaug niste elemente
	assert(m.adauga(5) == true);
	assert(m.adauga(1) == true);
	assert(m.adauga(10) == true);
	assert(m.adauga(7) == true);
	assert(m.adauga(1) == false);
	assert(m.adauga(10) == false);
	assert(m.adauga(-3) == true);
	assert(m.dim() == 5);
	assert(m.cauta(10) == true);
	assert(m.cauta(16) == false);
	assert(m.sterge(1) == true);
	assert(m.sterge(6) == false);
	assert(m.dim() == 4);


	IteratorMultime im = m.iterator();
	im.prim();
	int s = 0;
	while (im.valid()) {
		TElem e = im.element();
		s += e;
		im.urmator();
	}
	assert(s == 19);
	testReuniune();
}
