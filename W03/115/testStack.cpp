/***********************************************************************
 * Header:
 *    Test
 * Summary:
 *    Driver to test stack.h
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef DEBUG
#define DEBUG   // Remove this to skip the unit tests
#endif // DEBUG

#include "testStack.h"       // for the stack unit tests
#include "testSpy.h"         // for the spy unit tests
#include "testVector.h"      // for the vector unit tests
int Spy::counters[] = {};

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
#ifdef DEBUG
   // unit tests
   TestSpy().run();
   TestVector().run();
   TestStack().run();
#endif // DEBUG
  
   return 0;
}

