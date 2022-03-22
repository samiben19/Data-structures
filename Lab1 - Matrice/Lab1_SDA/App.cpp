//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"

using std::cout;

int main()
{
	testAll();
	testAllExtins();
	//_CrtDumpMemoryLeaks();
	cout<<"End";
	return 0;
}
