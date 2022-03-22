#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

// Theta(1)
Iterator::Iterator(const DO& d) : dict(d){
	curent = d.prim;
}

// Theta(1)
void Iterator::prim(){
	curent = dict.prim;
}

// Theta(n)
void Iterator::ultim()
{
	curent = dict.prim;
	while (curent->urmator() != nullptr)
		curent = curent->urmator();
}

// Best case: Theta(1), Worst case: Theta(n) => General O(n)
/*
anterior ()
daca iterator invalid atunci
	arunc exceptie
sf_daca

daca curent = dict.prim atunci
	curent = nullptr
	return
sf_daca

actual <- dict.prim
cat timp actual.urmator != curent executa
	actual <- actual.urmator
curent = actual
*/
void Iterator::anterior()
{
	if (!valid())
		throw exception();
	if (curent == dict.prim)
	{
		curent = nullptr;
		return;
	}
	PNod actual = dict.prim;
	while (actual->urmator() != curent)
		actual = actual->urmator();
	curent = actual;
}

// Theta(1)
void Iterator::urmator(){
	if (!valid())
		throw exception();
	curent = curent->urmator();
}

// Theta(1)
bool Iterator::valid() const{
	if (curent != nullptr)
		return true;
	return false;
}

// Theta(1)
TElem Iterator::element() const{
	if (!valid())
		throw exception();
	return curent->element();
}

