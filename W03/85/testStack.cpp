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

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
#ifdef DEBUG
   // unit tests
   TestStack().run();
#endif // DEBUG
  
   return 0;
}

