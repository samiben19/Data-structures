#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

using std::exception;

IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	curent = m.prim;
}


void IteratorMultime::prim() {
	curent = multime.prim;
}


void IteratorMultime::urmator() {
	if (!valid())
		throw exception("Iterator invalid !\n");
	curent = multime.urm[curent];
}


TElem IteratorMultime::element() const {
	if (!valid())
		throw exception("Iterator invalid !\n");
	return multime.e[curent];
}

bool IteratorMultime::valid() const {
	return curent != NULL_TELEM;
}
