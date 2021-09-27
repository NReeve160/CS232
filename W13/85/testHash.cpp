/***********************************************************************
 * Header:
 *    Test
 * Summary:
 *    Driver to test hash.h
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef DEBUG
#define DEBUG   // Remove this to skip the unit tests
#endif // DEBUG

#include "testHash.h"       // for the hash unit tests

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
#ifdef DEBUG
   // unit tests
   TestHash().run();
#endif // DEBUG
   
   // driver
   return 0;
}
