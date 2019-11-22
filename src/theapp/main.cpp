#include <iostream>
#include "mylib_1.h"
using namespace std;

int main()
{
   cout << "Hello world from The App!" << endl;

   MyLibClass mylibclass_obj;
#ifdef TEST
   cout << "INside theapp - TEST MODE" << endl;
#endif

#ifdef MYTEST
   cout << "INside theapp - MYTEST MODE" << endl;
#endif


   mylibclass_obj.PrintHello();
   MyLibClass_2 mylibclass2_obj;

   cout << "Calling nested dependent library" << endl;
   mylibclass2_obj.PrintHelloMyLib_2();
   getchar();
   return 0;
}