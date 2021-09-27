/***********************************************************************
 * Header:
 *    Test
 * Summary:
 *    Driver to test bnode.h
 * Author
 *    Br. Helfrich
 ************************************************************************/


#ifndef DEBUG
#define DEBUG   // Remove this to skip the unit tests
#endif // DEBUG

#include "testBNode.h"       // for the BST unit tests

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
#ifdef DEBUG
   // unit tests
   TestBNode().run();
#endif // DEBUG
   
   
   return 0;
}

