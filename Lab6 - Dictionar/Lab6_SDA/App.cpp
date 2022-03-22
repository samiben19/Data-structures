#include "TestExtins.h"
#include "TestScurt.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtins();
	_CrtDumpMemoryLeaks();

	cout << "That's all!" << endl;
	return 0;
}

