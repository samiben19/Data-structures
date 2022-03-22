#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"

int main(){
    testAll();
    testAllExtins();
    _CrtDumpMemoryLeaks();
    std::cout<<"\nFinished Tests!"<<std::endl;
}
