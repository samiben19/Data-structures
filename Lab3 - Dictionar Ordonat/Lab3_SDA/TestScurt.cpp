#include <assert.h>

#include "DO.h"
#include "Iterator.h"

#include <iostream>
#include <exception>
using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void test_anterior()
{
    DO dictOrd = DO(relatie1);
    assert(dictOrd.dim() == 0);
    assert(dictOrd.vid());
    dictOrd.adauga(2, 2);
    dictOrd.adauga(4, 4);
    dictOrd.adauga(5, 5);
    dictOrd.adauga(1, 1);
    dictOrd.adauga(3, 3);
    dictOrd.adauga(7, 7);
    dictOrd.adauga(6, 6);
    assert(dictOrd.dim() == 7);

    Iterator it = dictOrd.iterator();

    cout << "Elementele parcurse de la sfarsit la inceput: ";
    it.ultim();
    while (it.valid()) {
        TElem e = it.element();
        cout << e.first << ' ';
        assert(e.second != NULL_TVALOARE);
        it.anterior();
    }
}

void testAll(){
    DO dictOrd = DO(relatie1);
    assert(dictOrd.dim() == 0);
    assert(dictOrd.vid());
    dictOrd.adauga(1, 2);
    assert(dictOrd.dim() == 1);
    assert(!dictOrd.vid());
    assert(dictOrd.cauta(1) != NULL_TVALOARE);
    TValoare v = dictOrd.adauga(1, 3);
    assert(v == 2);
    assert(dictOrd.cauta(1) == 3);
    Iterator it = dictOrd.iterator();
    it.prim();
    while (it.valid()) {
        TElem e = it.element();
        assert(e.second != NULL_TVALOARE);
        it.urmator();
    }
    assert(dictOrd.sterge(1) == 3);
    assert(dictOrd.vid());

    test_anterior();
}

