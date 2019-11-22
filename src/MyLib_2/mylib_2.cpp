#include "mylib_2.h"
#include "newheader.h"
#include "newheader2.h"

void MyLibClass_2::PrintHelloMyLib_2()
{
#ifdef MYTEST
	std::cout << "Inside PrintHelloMyLib_2() - MYTEST" << std::endl;
#endif

	std::cout << "Inside PrintHelloMyLib_2()" << std::endl;
	printhellofrom_newheader();
	printhellofrom_newheader2();
}