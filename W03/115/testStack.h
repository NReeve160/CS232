/***********************************************************************
 * Header:
 *    TEST STACK
 * Summary:
 *    Unit tests for stack
 * Author
 *    Br. Helfrich
 ************************************************************************/

#pragma once

#ifdef DEBUG
#include "stack.h"
#include "unitTest.h"
#include "spy.h"

#include <iostream>
#include <cassert>
#include <memory>

#include <stack>
#include <vector>
#include <list>

class TestStack : public UnitTest
{
public:
   void run()
   {
      reset();

      // Construct
      test_construct_default();
      test_constructCopy_empty();
      test_constructCopy_standard();
      test_constructCopy_partiallyFilled();
      test_constructMove_empty();
      test_constructMove_standard();
      test_constructMove_partiallyFilled();
      test_constructInit_empty();
      test_constructInit_standard();
      test_constructInit_emptySTD();
      test_constructInit_standardSTD();
      test_constructInitMove_empty();
      test_constructInitMove_standard();
      test_constructInitMove_emptySTD();
      test_constructInitMove_standardSTD();
      test_destructor_empty();
      test_destructor_standard();
      test_destructor_partiallyFilled();

      // Access
      test_top_readOne();
      test_top_readStandard();
      test_top_writeOne();
      test_top_writeStandard();

      // Insert
      test_pushCopy_empty();
      test_pushCopy_standard();
      test_pushCopy_standardList();
      test_pushMove_empty();
      test_pushMove_standard();
      test_pushMove_standardList();

      // Delete
      test_pop_empty();
      test_pop_one();
      test_pop_standard();
      test_pop_standardList();

      // Status
      test_size_empty();
      test_size_standard();
      test_empty_empty();
      test_empty_standard();

      report("Stack");
   }
   
   /***************************************
    * CONSTRUCTOR - Default
    ***************************************/
   
   // default constructor, no allocations
   void test_construct_default()
   {  // setup
      Spy::reset();
      // exercise
      custom::stack<Spy> s;
      // verify
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numEquals() == 0);
      assertUnit(Spy::numLessthan() == 0);
      assertUnit(Spy::numSwap() == 0);
      assertEmptyFixture(s);
      // teardown
      teardownStandardFixture(s);
   } 


   /***************************************
    * DESTRUCTOR
    ***************************************/

    // destructor of an empty collection
   void test_destructor_empty()
   {  // setup
      {
         custom::stack<Spy> s;
         Spy::reset();
      } // exercise
      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
   }  // verify

   // destructor of a 4-element collection
   void test_destructor_standard()
   {  // setup
      {
         //      0    1    2    3
         //    +----+----+----+----+
         //    | 26 | 49 | 67 | 89 |
         //    +----+----+----+----+
         custom::stack<Spy> s;
         setupStandardFixture(s);
         Spy::reset();
      } // exercise
      // verify
      assertUnit(Spy::numDestructor() == 4); // destructor for [26,49,67,89]
      assertUnit(Spy::numDelete() == 4);     // delete [26,49,67,89]
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAssign() == 0);
   }

   // destructor of a 2-element, 4-capacity collection
   void test_destructor_partiallyFilled()
   {  // setup
      {
         //      0    1    2    3
         //    +----+----+----+----+
         //    | 26 | 49 |    |    |
         //    +----+----+----+----+
         custom::stack<Spy> s;
         s.container.reserve(4);
         s.container.push_back(Spy(26));
         s.container.push_back(Spy(49));
         Spy::reset();
      }  // exercise
      assertUnit(Spy::numDestructor() == 2); // destructor for [26,49]
      assertUnit(Spy::numDelete() == 2);     // delete [26,49]
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAssign() == 0);
   }

   /***************************************
    * COPY CONSTRUCTOR
    ***************************************/

    // copy constructor of an empty stack
   void test_constructCopy_empty()
   {  // setup
      custom::stack<Spy> sSrc;
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(sSrc);
      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // copy constructor of a 4-element collection
   void test_constructCopy_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy> sSrc;
      setupStandardFixture(sSrc);
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(sSrc);
      // verify
      assertUnit(Spy::numCopy() == 4);     // copy constructor for [26,49,67,89]
      assertUnit(Spy::numAlloc() == 4);    // allocate [26,49,67,89]
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   // copy constructor of a 2-element, 4-capacity collection
   void test_constructCopy_partiallyFilled()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      custom::stack<Spy> sSrc;
      sSrc.container.reserve(4);
      sSrc.container.push_back(Spy(26));
      sSrc.container.push_back(Spy(49));
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(sSrc);
      // verify
      assertUnit(Spy::numCopy() == 2);     // copy constructor [26,49]
      assertUnit(Spy::numAlloc() == 2);    // allocate [26,49]
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      assertUnit(sSrc.container.size() == 2);
      if (sSrc.container.size() >= 2)
      { 
         assertUnit(sSrc.container[0] == Spy(26));
         assertUnit(sSrc.container[1] == Spy(49));
      }
      assertUnit(sSrc.container.capacity() == 4);
      //      0    1
      //    +----+----+
      //    | 26 | 49 |
      //    +----+----+
      assertUnit(sDest.container.size() == 2);
      if (sDest.container.size() >= 2)
      {
         assertUnit(sDest.container[0] == Spy(26));
         assertUnit(sDest.container[1] == Spy(49));
      }
      assertUnit(sDest.container.capacity() == 2);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }


   /***************************************
    * MOVE CONSTRUCTOR
    ***************************************/

    // move constructor of an empty stack
   void test_constructMove_empty()
   {  // setup
      custom::stack<Spy> sSrc;
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(std::move(sSrc));
      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructMove_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy> sSrc;
      setupStandardFixture(sSrc);
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(std::move(sSrc));
      // verify      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertEmptyFixture(sSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   // move constructor of a 2-element, 4-capacity collection
   void test_constructMove_partiallyFilled()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      custom::stack<Spy> sSrc;
      sSrc.container.reserve(4);
      sSrc.container.push_back(Spy(26));
      sSrc.container.push_back(Spy(49));
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(std::move(sSrc));
      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertEmptyFixture(sSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      assertUnit(sDest.container.size() == 2);
      if (sDest.container.size() >= 2)
      {
         assertUnit(sDest.container[0] == Spy(26));
         assertUnit(sDest.container[1] == Spy(49));
      }
      assertUnit(sDest.container.capacity() == 4);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   /***************************************
    * INITIALIZE CONSTRUCTOR
    ***************************************/

    // initialize constructor of an empty stack
   void test_constructInit_empty()
   {  // setup
      custom::vector<Spy> vSrc;
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(vSrc);
      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(vSrc.empty() == true);
      assertEmptyFixture(sDest);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructInit_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector<Spy> vSrc{Spy(26), Spy(49), Spy(67), Spy(89)};
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(vSrc);
      // verify      // verify
      assertUnit(Spy::numCopy() == 4);     // create   [26,49,67,89]
      assertUnit(Spy::numAlloc() == 4);    // allocate [26,49,67,89]
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(vSrc.size() == 4);
      assertUnit(vSrc.capacity() == 4);
      if (vSrc.size() >= 4)
      {
         assertUnit(vSrc[0] == Spy(26));
         assertUnit(vSrc[1] == Spy(49));
         assertUnit(vSrc[2] == Spy(67));
         assertUnit(vSrc[3] == Spy(89));
      }
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sDest);
   }

   // initialize constructor of an empty stack
   void test_constructInit_emptySTD()
   {  // setup
      std::vector<Spy> vSrc;
      Spy::reset();
      // exercise
      custom::stack<Spy, std::vector<Spy>> sDest(vSrc);
      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(vSrc.empty() == true);
      assertUnit(sDest.container.size() == 0);
      assertUnit(sDest.container.capacity() == 0);
      assertUnit(vSrc.size() == 0);
      assertUnit(vSrc.capacity() == 0);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructInit_standardSTD()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      std::vector<Spy> vSrc{ Spy(26), Spy(49), Spy(67), Spy(89) };
      Spy::reset();
      // exercise
      custom::stack<Spy, std::vector<Spy>> sDest(vSrc);
      // verify      // verify
      assertUnit(Spy::numCopy() == 4);     // create   [26,49,67,89]
      assertUnit(Spy::numAlloc() == 4);    // allocate [26,49,67,89]
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(vSrc.size() == 4);
      assertUnit(vSrc.capacity() == 4);
      if (vSrc.size() >= 4)
      {
         assertUnit(vSrc[0] == Spy(26));
         assertUnit(vSrc[1] == Spy(49));
         assertUnit(vSrc[2] == Spy(67));
         assertUnit(vSrc[3] == Spy(89));
      }
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(sDest.container.size() == 4);
      assertUnit(sDest.container.capacity() == 4);
      if (sDest.container.size() >= 4)
      {
         assertUnit(sDest.container[0] == Spy(26));
         assertUnit(sDest.container[1] == Spy(49));
         assertUnit(sDest.container[2] == Spy(67));
         assertUnit(sDest.container[3] == Spy(89));
      }
      // teardown
      sDest.container.clear();
   }

   /***************************************
    * INITIALIZE CONSTRUCTOR
    ***************************************/

    // initialize constructor of an empty stack
   void test_constructInitMove_empty()
   {  // setup
      custom::vector<Spy> vSrc;
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(std::move(vSrc));
      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(vSrc.empty() == true);
      assertEmptyFixture(sDest);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructInitMove_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector<Spy> vSrc{ Spy(26), Spy(49), Spy(67), Spy(89) };
      Spy::reset();
      // exercise
      custom::stack<Spy> sDest(std::move(vSrc));
      // verify      // verify
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(vSrc.size() == 0);
      assertUnit(vSrc.capacity() == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sDest);
   }

   // initialize constructor of an empty stack
   void test_constructInitMove_emptySTD()
   {  // setup
      std::vector<Spy> vSrc;
      Spy::reset();
      // exercise
      custom::stack<Spy, std::vector<Spy>> sDest(std::move(vSrc));
      // verify
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(vSrc.empty() == true);
      assertUnit(sDest.container.size() == 0);
      assertUnit(sDest.container.capacity() == 0);
      assertUnit(vSrc.size() == 0);
      assertUnit(vSrc.capacity() == 0);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructInitMove_standardSTD()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      std::vector<Spy> vSrc{ Spy(26), Spy(49), Spy(67), Spy(89) };
      Spy::reset();
      // exercise
      custom::stack<Spy, std::vector<Spy>> sDest(std::move(vSrc));
      // verify
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(vSrc.size() == 0);
      assertUnit(vSrc.capacity() == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(sDest.container.size() == 4);
      assertUnit(sDest.container.capacity() == 4);
      if (sDest.container.size() >= 4)
      {
         assertUnit(sDest.container[0] == Spy(26));
         assertUnit(sDest.container[1] == Spy(49));
         assertUnit(sDest.container[2] == Spy(67));
         assertUnit(sDest.container[3] == Spy(89));
      }
      // teardown
      sDest.container.clear();
   }


   /***************************************
    * SIZE EMPTY CAPACITY
    ***************************************/

   // size of empty stack
   void test_size_empty()
   {  // setup
      custom::stack<Spy> s;
      Spy::reset();
      // exercise
      size_t size = s.size();
      // verify
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(size == 0);
      assertEmptyFixture(s);
   }  // teardown

   // size of standard stack
   void test_size_standard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy> s;
      setupStandardFixture(s);
      Spy::reset();
      // exercise
      size_t size = s.size();
      // verify
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(size == 4);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   } 

   // is an empty stack empty
   void test_empty_empty()
   {  // setup
      custom::stack<Spy> s;
      Spy::reset();
      // exercise
      bool empty = s.empty();
      // verify
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(empty == true);
      assertEmptyFixture(s);
   }  // teardown

   // is a standard stack empty
   void test_empty_standard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy> s;
      setupStandardFixture(s);
      Spy::reset();
      // exercise
      bool empty = s.empty();
      // verify
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(empty == false);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   /***************************************
    * TOP
    ***************************************/

   // read an element from a stack with one element
   void test_top_readOne()
   {  // setup
      //    +----+
      //    | 26 |
      //    +----+
      custom::stack<Spy> s;
      s.container.push_back(Spy(26));
      Spy value(99);
      Spy::reset();
      // exercise
      value = s.top();
      // verify
      assertUnit(Spy::numAssign() == 1);   // assign [99] <- [26]
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      //    +----+
      //    | 26 |
      //    +----+
      assertUnit(s.container.size() == 1);
      assertUnit(s.container.capacity() == 1);
      if (s.container.size() >= 1)
         assertUnit(s.container[0] == Spy(26));
      assertUnit(value == Spy(26));
      // teardown
      teardownStandardFixture(s);
   }

   // read an element from a stack with many elements
   void test_top_readStandard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy> s;
      setupStandardFixture(s);
      Spy value(99);
      Spy::reset();
      // exercise
      value = s.top();
      // verify
      assertUnit(Spy::numAssign() == 1);   // assign [99] <- [89]
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(value == Spy(89));
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // when there is one element in the stack, write to it
   void test_top_writeOne()
   {  // setup
      //    +----+
      //    | 26 |
      //    +----+
      custom::stack<Spy> s;
      s.container.push_back(Spy(26));
      Spy value(99);
      Spy::reset();
      // exercise
      s.top() = value;
      // verify
      assertUnit(Spy::numAssign() == 1);   // assign [26] <- [99]
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      //    +----+
      //    | 99 |
      //    +----+
      assertUnit(s.container.size() == 1);
      assertUnit(s.container.capacity() == 1);
      if (s.container.size() > 1)
         assertUnit(s.container[0] == Spy(99));
      assertUnit(value == Spy(99));
      // teardown
      teardownStandardFixture(s);
   }

   // when there are many elements in the stackm write to the top one
   void test_top_writeStandard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 0  |
      //    +----+----+----+----+
      custom::stack<Spy> s;
      setupStandardFixture(s);
      s.container[3] = Spy(0);
      Spy value(89);
      Spy::reset();
      // exercise
      s.top() = value;
      // verify
      assertUnit(Spy::numAssign() == 1);   // assign [0] <- [89]
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }


   /***************************************
    * PUSH - COPY
    ***************************************/

    // add an element when the stack is empty
   void test_pushCopy_empty()
   {  // setup
      custom::stack<Spy> s;
      Spy value(99);
      Spy::reset();
      // exercise
      s.push(value);
      // verify
      assertUnit(Spy::numCopy() == 1);    // copy-create [99]
      assertUnit(Spy::numAlloc() == 1);   // allocate    [99]
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(value == Spy(99));
      //    +----+
      //    | 99 |
      //    +----+
      assertUnit(s.container.size() == 1);
      if (s.container.size() >= 1)
         assertUnit(s.container[0] == Spy(99));
      // teardown
      teardownStandardFixture(s);
   }

   // add an element when there is room. Capacity remains unchanged
   void test_pushCopy_standard()
   {  // setup
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 |    |    |
      //    +----+----+----+----+----+----+
      custom::stack<Spy> s;
      setupStandardFixture(s);
      s.container.reserve(6);
      Spy value(99);
      Spy::reset();
      // exercise
      s.push(value);
      // verify
      assertUnit(Spy::numCopy() == 1);    // copy-create [99]
      assertUnit(Spy::numAlloc() == 1);   // allocate    [99]
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(value == Spy(99));
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 |    |
      //    +----+----+----+----+----+----+
      assertUnit(s.container.size() == 5);
      if (s.container.size() >= 5)
      {
         assertUnit(s.container[0] == Spy(26));
         assertUnit(s.container[1] == Spy(49));
         assertUnit(s.container[2] == Spy(67));
         assertUnit(s.container[3] == Spy(89));
         assertUnit(s.container[4] == Spy(99));
      }
      // teardown
      teardownStandardFixture(s);
   }

   // add an element to a std::list stck
   void test_pushCopy_standardList()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy, std::list<Spy>> s;
      s.container.push_back(Spy(26));
      s.container.push_back(Spy(49));
      s.container.push_back(Spy(67));
      s.container.push_back(Spy(89));
      Spy value(99);
      Spy::reset();
      // exercise
      s.push(value);
      // verify
      assertUnit(Spy::numCopy() == 1);    // copy-create [99]
      assertUnit(Spy::numAlloc() == 1);   // allocate    [99]
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(value == Spy(99));
      //    +----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 |
      //    +----+----+----+----+----+
      assertUnit(s.container.size() == 5);
      if (s.container.size() >= 5)
      {
         auto it = s.container.begin();
         assertUnit(*(it++) == Spy(26));
         assertUnit(*(it++) == Spy(49));
         assertUnit(*(it++) == Spy(67));
         assertUnit(*(it++) == Spy(89));
         assertUnit(*(it++) == Spy(99));
         assertUnit(it == s.container.end());
      }
      // teardown
      s.container.clear();
   }

   /***************************************
    * PUSH - MOVE
    ***************************************/

    // add an element when the stack is empty
   void test_pushMove_empty()
   {  // setup
      custom::stack<Spy> s;
      Spy value(99);
      Spy::reset();
      // exercise
      s.push(std::move(value));
      // verify
      assertUnit(Spy::numCopyMove() == 1);  // copy-constructor of [99]
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(value.empty());
      //    +----+
      //    | 99 |
      //    +----+
      assertUnit(s.container.size() == 1);
      if (s.container.size() >= 1)
         assertUnit(s.container[0] == Spy(99));
      // teardown
      teardownStandardFixture(s);
   }

   // add an element when there is room. Capacity remains unchanged
   void test_pushMove_standard()
   {  // setup
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 |    |    |
      //    +----+----+----+----+----+----+
      custom::stack<Spy> s;
      setupStandardFixture(s);
      s.container.reserve(6);
      Spy value(99);
      Spy::reset();
      // exercise
      s.push(std::move(value));
      // verify
      assertUnit(Spy::numCopyMove() == 1);  // copy-constructor of [99]
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(value.empty());
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 |    |
      //    +----+----+----+----+----+----+
      assertUnit(s.container.size() == 5);
      if (s.container.size() >= 5)
      {
         assertUnit(s.container[0] == Spy(26));
         assertUnit(s.container[1] == Spy(49));
         assertUnit(s.container[2] == Spy(67));
         assertUnit(s.container[3] == Spy(89));
         assertUnit(s.container[4] == Spy(99));
      }
      // teardown
      teardownStandardFixture(s);
   }

   // add an element to a std::list stck
   void test_pushMove_standardList()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy, std::list<Spy>> s;
      s.container.push_back(Spy(26));
      s.container.push_back(Spy(49));
      s.container.push_back(Spy(67));
      s.container.push_back(Spy(89));
      Spy value(99);
      Spy::reset();
      // exercise
      s.push(std::move(value));
      // verify
      assertUnit(Spy::numCopyMove() == 1);  // copy-constructor of [99]
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertUnit(value.empty());
      //    +----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 |
      //    +----+----+----+----+----+
      assertUnit(s.container.size() == 5);
      if (s.container.size() >= 5)
      {
         auto it = s.container.begin();
         assertUnit(*(it++) == Spy(26));
         assertUnit(*(it++) == Spy(49));
         assertUnit(*(it++) == Spy(67));
         assertUnit(*(it++) == Spy(89));
         assertUnit(*(it++) == Spy(99));
         assertUnit(it == s.container.end());
      }
      // teardown
      s.container.clear();
   }

   /***************************************
    * POP
    ***************************************/

    // remove an element from an empty stack
   void test_pop_empty()
   {  // setup
      custom::stack<Spy> s;
      Spy::reset();
      // exercise
      s.pop();
      // verify
      assertUnit(Spy::numCopyMove() == 0); 
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDelete() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(Spy::numDestructor() == 0);
      assertEmptyFixture(s);
   }  // teardown

   // remove one element from a stack
   void test_pop_one()
   {  // setup
      //    +----+
      //    | 26 |
      //    +----+
      custom::stack<Spy> s;
      s.container.push_back(Spy(26));
      Spy::reset();
      // exercise
      s.pop();
      // verify
      assertUnit(Spy::numDestructor() == 1);  // destroy [26]
      assertUnit(Spy::numDelete() == 1);      // delete  [26]
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      assertUnit(s.container.size() == 0);
      assertUnit(s.container.empty() == true);
      // teardown
      teardownStandardFixture(s);
   }

   // remove one element when there are many
   void test_pop_standard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy> s;
      setupStandardFixture(s);
      Spy::reset();
      // exercise
      s.pop();
      // verify
      assertUnit(Spy::numDestructor() == 1);  // destroy [89]
      assertUnit(Spy::numDelete() == 1);      // delete  [89]
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      //    +----+----+----+----+
      //    | 26 | 49 | 67 |    |
      //    +----+----+----+----+
      assertUnit(s.container.size() == 3);
      if (s.container.size() >= 3)
      {
         assertUnit(s.container[0] == Spy(26));
         assertUnit(s.container[1] == Spy(49));
         assertUnit(s.container[2] == Spy(67));
      }
      // teardown
      teardownStandardFixture(s);
   }

   // remove one element when there are many
   void test_pop_standardList()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack<Spy, std::list<Spy>> s;
      s.container.push_back(Spy(26));
      s.container.push_back(Spy(49));
      s.container.push_back(Spy(67));
      s.container.push_back(Spy(89));
      Spy::reset();
      // exercise
      s.pop();
      // verify
      assertUnit(Spy::numDestructor() == 1);  // destroy [89]
      assertUnit(Spy::numDelete() == 1);      // delete  [89]
      assertUnit(Spy::numCopyMove() == 0);
      assertUnit(Spy::numCopy() == 0);
      assertUnit(Spy::numAlloc() == 0);
      assertUnit(Spy::numAssign() == 0);
      assertUnit(Spy::numDefault() == 0);
      assertUnit(Spy::numNondefault() == 0);
      assertUnit(Spy::numAssignMove() == 0);
      //    +----+----+----+
      //    | 26 | 49 | 67 |
      //    +----+----+----+
      assertUnit(s.container.size() == 3);
      if (s.container.size() == 3)
      {
         auto it = s.container.begin();
         assertUnit(*(it++) == Spy(26));
         assertUnit(*(it++) == Spy(49));
         assertUnit(*(it++) == Spy(67));
         assert(it == s.container.end());
      }
      // teardown
      s.container.clear();
   }


   
   /*************************************************************
    * SETUP STANDARD FIXTURE
    *      0    1    2    3
    *    +----+----+----+----+
    *    | 26 | 49 | 67 | 89 |
    *    +----+----+----+----+
    *************************************************************/
   void setupStandardFixture(custom::stack<Spy>& s)
   {
      s.container.resize(4);
      s.container[0] = Spy(26);
      s.container[1] = Spy(49);
      s.container[2] = Spy(67);
      s.container[3] = Spy(89);
   }
   
   /*************************************************************
    * TEARDOWN STANDARD FIXTURE
    *      0    1    2    3
    *    +----+----+----+----+
    *    |    |    |    |    |
    *    +----+----+----+----+
    *************************************************************/
   void teardownStandardFixture(custom::stack<Spy>& s)
   {
      s.container.clear();
   }
   
   /*************************************************************
    * VERIFY EMPTY FIXTURE
    *************************************************************/
   void assertEmptyFixtureParameters(const custom::stack<Spy>& s, int line, const char* function)
   {
      assertIndirect(s.container.empty());
      assertIndirect(s.container.size() == 0);
      assertIndirect(s.container.capacity() == 0);
   }

   /*************************************************************
    * VERIFY STANDARD FIXTURE
    *      0    1    2    3
    *    +----+----+----+----+
    *    | 26 | 49 | 67 | 89 |
    *    +----+----+----+----+
    *************************************************************/
   void assertStandardFixtureParameters(const custom::stack<Spy>& s, int line, const char* function)
   {
      assertIndirect(s.container.size() == 4);
      assertIndirect(s.container.capacity() == 4);
      
      if (s.container.size() >= 4)
      {
         assertIndirect(s.container[0] == Spy(26));
         assertIndirect(s.container[1] == Spy(49));
         assertIndirect(s.container[2] == Spy(67));
         assertIndirect(s.container[3] == Spy(89));
      }
   }


};

#endif // DEBUG
