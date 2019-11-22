#include "mylib_1.h"

void MyLibClass::PrintHelloMyLib_1()
{
	std::cout << "Inside PrintHelloMyLib_1()" << std::endl;
}

void MyLibClass::PrintHello()
{
	std::cout << "Inside PrintHello()" << std::endl;
	PrintHelloMyLib_1();
	MyLibClass_2 mylibclass_2obj;
	mylibclass_2obj.PrintHelloMyLib_2();
}
