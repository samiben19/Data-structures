#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>
#include <iostream>

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict{ d } {
	curent = 0;
	deplasare();
}


void IteratorDictionar::deplasare()
{
	while (curent < dict.cap && !dict.ocupat[curent])
		curent++;
}

void IteratorDictionar::prim() {
	curent = 0;
	deplasare();
}


void IteratorDictionar::urmator() {
	if (!valid())
		throw exception("Iterator invalid !\n");
	curent++;
	deplasare();
}


TElem IteratorDictionar::element() const{
	if (!valid())
		throw exception("Iterator invalid !\n");
	return dict.e[curent];
}


bool IteratorDictionar::valid() const {
	return curent < dict.cap && dict.ocupat[curent];
}

