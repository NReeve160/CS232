/***********************************************************************
 * Header:
 *    Test
 * Summary:
 *    Driver to test bst.h
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef DEBUG
#define DEBUG   // Remove this to skip the unit tests
#endif

#include "testBST.h"        // for the BST unit tests
#include "testSpy.h"        // for the spy unit tests
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
   TestBST().run();
#endif // DEBUG
   
   return 0;
}

