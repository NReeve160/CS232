/***********************************************************************
 * Header:
 *    TEST SET
 * Summary:
 *    Unit tests for set
 * Author
 *    Br. Helfrich
 ************************************************************************/

#pragma once


#ifdef DEBUG

#include "set.h"
#include "unitTest.h"
#include <set>
#include <vector>


#include <iostream>
#include <cassert>
#include <memory>

class TestSet : public UnitTest
{
public:
   void run()
   {
      reset();

      // Constructor
      test_construct_default();

      // Copy Constructor
      test_constructorCopy_empty();
      test_constructorCopy_one();
      test_constructorCopy_standard();

      // Move Constructor
      test_constructorMove_empty();
      test_constructorMove_one();
      test_constructorMove_standard();

      // Initialization List Constructor
      test_constructInit_empty();
      test_constructInit_one();
      test_constructInit_standard();

      // Range Constructor
      test_constructRange_empty();
      test_constructRange_one();
      test_constructRange_standard();

      // Destructor
      test_destructor_empty();
      test_destructor_standard();

      // Size, Empty
      test_empty_empty();
      test_empty_standard();
      test_size_empty();
      test_size_standard();

      // Assignment operator
      test_assign_emptyToEmpty();
      test_assign_standardToEmpty();
      test_assign_emptyToStandard();
      test_assign_oneToStandard();
      test_assign_standardToOne();
      test_assign_standardToStandard();

      // Assignment-Move operator
      test_assignMove_emptyToEmpty();
      test_assignMove_standardToEmpty();
      test_assignMove_emptyToStandard();
      test_assignMove_oneToStandard();
      test_assignMove_standardToOne();
      test_assignMove_standardToStandard();

      // Assignment Initialize List 
      test_assignInit_emptyToEmpty();
      test_assignInit_standardToEmpty();
      test_assignInit_emptyToStandard();
      test_assignInit_oneToStandard();
      test_assignInit_standardToOne();
      test_assignInit_standardToStandard();

      // Swap
      test_swap_emptyToEmpty();
      test_swap_standardToEmpty();
      test_swap_emptyToStandard();
      test_swap_standardToStandard();

      // Clear
      test_clear_empty();
      test_clear_standard();


      // Find
      test_find_empty();
      test_find_standardBegin();
      test_find_standardLast();
      test_find_standardMissing();

      // Insert
      test_insert_empty();
      test_insert_standardEnd();
      test_insert_standardFront();
      test_insert_standardMiddle();
      test_insert_standardDuplicate();
      

      // Insert Move
      test_insertMove_empty();
      test_insertMove_standardEnd();
      test_insertMove_standardFront();
      test_insertMove_standardMiddle();
      test_insertMove_standardDuplicate();

      // Insert iterator list
      test_insertInit_emptyInsertNone();
      test_insertInit_emptyInsertMany();
      test_insertInit_standardInsertNone();
      test_insertInit_standardInsertDuplicates();
      test_insertInit_manyInsertMany();

      test_eraseRange_several();

      // Erase Value
      test_eraseValue_empty();
      test_eraseValue_standardMissing();
      test_eraseValue_noChildren();
      test_eraseValue_oneChild();
      test_eraseValue_twoChildren();


      report("Set");
   }
   
   /***************************************
    * CONSTRUCTORS
    ***************************************/
   // default constructor, no allocaations
   void test_construct_default() 
   {  // setup
      
      // exercise
      custom::set s;
      // verify
      assertEmptyFixture(s);
   }  // teardown


   /***************************************
    * COPY
    ***************************************/

    // copy an empty set
   void test_constructorCopy_empty()
   {  // setup
      custom::set sSrc;
      
      // exercise
      custom::set sDest(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // copy a set that has one element
   void test_constructorCopy_one()
   {  // setup
      //            (50b)
      custom::set sSrc;
      sSrc.bst.root = new custom::BST<int>::BNode(int(50));
      sSrc.bst.numElements = 1;
      
      // exercise
      custom::set sDest(sSrc);
      // verify
      assertUnit(sSrc.bst.root != sDest.bst.root);
      //            (50b)
      assertUnit(sSrc.bst.numElements == 1);
      assertUnit(sSrc.bst.root != nullptr);
      if (sSrc.bst.root)
      {
         assertUnit(sSrc.bst.root->data == int(50));
         assertUnit(sSrc.bst.root->pLeft == nullptr);
         assertUnit(sSrc.bst.root->pRight == nullptr);
         assertUnit(sSrc.bst.root->pParent == nullptr);
      }
      //            (50b)
      assertUnit(sDest.bst.numElements == 1);
      assertUnit(sDest.bst.root != nullptr);
      if (sDest.bst.root)
      {
         assertUnit(sDest.bst.root->data == int(50));
         assertUnit(sDest.bst.root->pLeft == nullptr);
         assertUnit(sDest.bst.root->pRight == nullptr);
         assertUnit(sDest.bst.root->pParent == nullptr);
      }
      // teardown
      if (sSrc.bst.root)
         delete sSrc.bst.root;
      sSrc.bst.root = nullptr;
      sSrc.bst.numElements = 0;
      if (sDest.bst.root)
         delete sDest.bst.root;
      sDest.bst.root = nullptr;
      sDest.bst.numElements = 0;
   }

   // copy a standard set
   void test_constructorCopy_standard()
   {  // setup
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sSrc;
      setupStandardFixture(sSrc);
      
      // exercise
      custom::set  sDest(sSrc);
      // verify
      assertUnit(sSrc.bst.root != sDest.bst.root);
      if (sSrc.bst.root && sDest.bst.root)
      {
         assertUnit(sSrc.bst.root->pLeft != sDest.bst.root->pLeft);
         assertUnit(sSrc.bst.root->pRight != sDest.bst.root->pRight);
      }
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(sSrc);
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }


   /***************************************
    * MOVE CONSTRUCTOR
    ***************************************/

    // move an empty set
   void test_constructorMove_empty()
   {  // setup
      custom::set sSrc;
      
      // exercise
      custom::set sDest(std::move(sSrc));
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // move a set with a single node
   void test_constructorMove_one()
   {
      // setup
      //            (50b)
      custom::set  sSrc;
      sSrc.bst.root = new custom::BST<int>::BNode(int(50));
      sSrc.bst.numElements = 1;
      
      // exercise
      custom::set  sDest(std::move(sSrc));
      // verify
      assertUnit(sSrc.bst.root != sDest.bst.root);
      //           
      assertEmptyFixture(sSrc);
      //            (50b)
      assertUnit(sDest.bst.numElements == 1);
      assertUnit(sDest.bst.root != nullptr);
      assertUnit(sDest.bst.root != nullptr);
      if (sDest.bst.root)
      {
         assertUnit(sDest.bst.root->data == int(50));
         assertUnit(sDest.bst.root->pLeft == nullptr);
         assertUnit(sDest.bst.root->pRight == nullptr);
         assertUnit(sDest.bst.root->pParent == nullptr);
      }
      // teardown
      if (sDest.bst.root)
         delete sDest.bst.root;
      sDest.bst.root = nullptr;
      sDest.bst.numElements = 0;
   }

   // move the standard fixture
   void test_constructorMove_standard()
   {  // setup
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sSrc;
      setupStandardFixture(sSrc);
      
      // exercise
      custom::set  sDest(std::move(sSrc));
      // verify
      assertEmptyFixture(sSrc);
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sDest);
   }

     /***************************************
      * RANGE CONSTRUCTOR
      ***************************************/

      // create a new set using an empty range
   void test_constructRange_empty()
   {  // setup
      std::initializer_list<int> il{ int(50), int(30), int(70), int(20), int(40), int(60), int(80) };
      auto itBegin = il.begin();
      auto itEnd = il.end();
      
      // exercise
      custom::set  s(itBegin, itEnd);
      // verify
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // create a new set using a range of one element
   void test_constructRange_one()
   {  // setup
      std::initializer_list<int> il{ int(50), int(30), int(70), int(20), int(40), int(60), int(80) };
      auto itBegin = il.begin();
      auto itEnd = il.begin();
      itEnd++;
      
      // exercise
      custom::set  s(itBegin, itEnd);
      // verify
      //            (99b)
      assertUnit(s.bst.numElements == 1);
      assertUnit(s.bst.root != nullptr);
      if (s.bst.root)
      {
         assertUnit(s.bst.root->data == int(50));
         assertUnit(s.bst.root->pLeft == nullptr);
         assertUnit(s.bst.root->pRight == nullptr);
         assertUnit(s.bst.root->pParent == nullptr);
      }
      // teardown
      if (s.bst.root)
         delete s.bst.root;
      s.bst.root = nullptr;
      s.bst.numElements = 0;
   }

   // create a new set using a range created in order
   void test_constructRange_standard()
   {  // setup
      std::initializer_list<int> il{ int(50), int(30), int(70), int(20), int(40), int(60), int(80) };
      auto itBegin = il.begin();
      auto itEnd = il.end();
      
      // exercise
      custom::set  s(itBegin, itEnd);
      // verify
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   /***************************************
    * CONSTRUCTOR INITIALIZE LIST
    ***************************************/

   // create a new set using an empty initialize list
   void test_constructInit_empty()
   {  // setup
      
      // exercise
      custom::set  s{};
      // verify
      assertEmptyFixture(s);
   }  // teardown

   // create a new set using an initialize list of one element
   void test_constructInit_one()
   {  // setup
      std::initializer_list<int> il{ int(99) };
      
      // exercise
      custom::set  s(il);
      // verify
      //            (99b)
      assertUnit(s.bst.numElements == 1);
      assertUnit(s.bst.root != nullptr);
      if (s.bst.root)
      {
         assertUnit(s.bst.root->data == int(99));
         assertUnit(s.bst.root->pLeft == nullptr);
         assertUnit(s.bst.root->pRight == nullptr);
         assertUnit(s.bst.root->pParent == nullptr);
      }
      // teardown
      if (s.bst.root)
         delete s.bst.root;
      s.bst.root = nullptr;
      s.bst.numElements = 0;
   }

   // create a new set using an initialize list created in order
   void test_constructInit_standard()
   {  // setup
      std::initializer_list<int> il{ int(50), int(30), int(70), int(20), int(40), int(60), int(80) };
      
      // exercise
      custom::set  s(il);
      // verify
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   /***************************************
    * DESTRUCTOR
    ***************************************/

   // destroy an empty set
   void test_destructor_empty()
   {  // setup
      {
         custom::set s;
         
      }  // exercise
      // verify
   }  // teardown

   // destroy the standard fixture
   void test_destructor_standard()
   {  // setup
      {
         //                (50b)
         //          +-------+-------+
         //        (30b)           (70b)
         //     +----+----+     +----+----+
         //   (20r)     (40r) (60r)     (80r)
         custom::set  s;
         setupStandardFixture(s);
         
      }  // exercise
      // verify
   }  // teardown


   /***************************************
    * EMPTY and SIZE
    ***************************************/

    // is the empty BST empty?
   void test_empty_empty()
   {  // setup
      custom::set s;
      
      // exercise
      bool empty = s.empty();
      // verify
      assertUnit(empty == true);
      assertEmptyFixture(s);
   }  // teardown

   // is the standard fixture empty?
   void test_empty_standard()
   {  // setup
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s;
      setupStandardFixture(s);
      
      // exercise
      bool empty = s.empty();
      // verify
      assertUnit(empty == false);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // what is the size of an empty BST?
   void test_size_empty()
   {  // setup
      custom::set s;
      
      // exercise
      size_t size = s.size();
      // verify
      assertUnit(size == 0);
      assertEmptyFixture(s);
   }  // teardown

   // what is the size of the standard fixture?
   void test_size_standard()
   {  // setup
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s;
      setupStandardFixture(s);
      
      // exercise
      size_t size = s.size();
      // verify
      assertUnit(size == 7);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }


   /***************************************
    * Assignment
    *    set::operator=(const set &)
    ***************************************/

    // assignment operator: empty = empty
   void test_assign_emptyToEmpty()
   {  // setup
      custom::set  sSrc;
      custom::set  sDest;
      
      // exercise
      sDest = sSrc;
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // assignment operator: empty = standard
   void test_assign_standardToEmpty()
   {  // setup
      //                (50b) = sSrc
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sSrc;
      setupStandardFixture(sSrc);
      custom::set  sDest;
      
      // exercise
      sDest = sSrc;
      // verify
      assertUnit(sSrc.bst.root != sDest.bst.root);
      if (sSrc.bst.root && sDest.bst.root)
      {
         assertUnit(sSrc.bst.root->pLeft != sDest.bst.root->pLeft);
         assertUnit(sSrc.bst.root->pRight != sDest.bst.root->pRight);
      }
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(sSrc);
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   // assignment operator: standard = empty
   void test_assign_emptyToStandard()
   {  // setup
      custom::set  sSrc;
      //                (50b) = sDest
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sDest;
      setupStandardFixture(sDest);
      
      // exercise
      sDest = sSrc;
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // assignment operator : one = standard
   void test_assign_oneToStandard()
   {  // setup
      //                (50b) = sSrc
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sSrc;
      setupStandardFixture(sSrc);
      //                (99) = sDest
      custom::set  sDest;
      custom::BST<int> ::BNode* p99 = new custom::BST<int>::BNode(int(99));
      sDest.bst.root = p99;
      sDest.bst.numElements = 1;
      
      // exercise
      sDest = sSrc;
      // verify
      assertUnit(sDest.bst.root != sSrc.bst.root);
      if (sSrc.bst.root && sDest.bst.root)
      {
         assertUnit(sSrc.bst.root->pLeft != sDest.bst.root->pLeft);
         assertUnit(sSrc.bst.root->pRight != sDest.bst.root->pRight);
      }
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(sSrc);
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   // assignment operator : standard = one
   void test_assign_standardToOne()
   {  // setup
      //                (99) = sSrc
      custom::set  sSrc;
      custom::BST<int>::BNode* p99 = new custom::BST<int>::BNode(int(99));
      sSrc.bst.root = p99;
      sSrc.bst.numElements = 1;
      //                (50b) = sDest
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sDest;
      setupStandardFixture(sDest);
      
      // exercise
      sDest = sSrc;
      // verify
      assertUnit(sDest.bst.root != sSrc.bst.root);
      //                (99) = sSrc.bst
      assertUnit(sSrc.bst.root != nullptr);
      if (sSrc.bst.root)
      {
         assertUnit(sSrc.bst.root->data == int(99));
         assertUnit(sSrc.bst.root->pParent == nullptr);
         assertUnit(sSrc.bst.root->pLeft == nullptr);
         assertUnit(sSrc.bst.root->pRight == nullptr);
      }
      //                (99) = sDest.bst
      assertUnit(sDest.bst.root != nullptr);
      if (sDest.bst.root)
      {
         assertUnit(sDest.bst.root->data == int(99));
         assertUnit(sDest.bst.root->pParent == nullptr);
         assertUnit(sDest.bst.root->pLeft == nullptr);
         assertUnit(sDest.bst.root->pRight == nullptr);
      }
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   // assignment operator : standard = standard
   void test_assign_standardToStandard()
   {  // setup
      //                (50b) = bstSrc
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sSrc;
      setupStandardFixture(sSrc);
      //                (50b) = bstDest
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sDest;
      setupStandardFixture(sDest);
      
      // exercise
      sDest = sSrc;
      // verify
      assertUnit(sDest.bst.root != sSrc.bst.root);
      if (sSrc.bst.root && sDest.bst.root)
      {
         assertUnit(sSrc.bst.root->pLeft != sDest.bst.root->pLeft);
         assertUnit(sSrc.bst.root->pRight != sDest.bst.root->pRight);
      }
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(sSrc);
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   /***************************************
    * Assignment-Move
    *    set::operator=(set &&)
    ***************************************/

 // assignment-move operator: empty = std::move(empty)
   void test_assignMove_emptyToEmpty()
   {  // setup
      custom::set  bstSrc;
      custom::set  bstDest;
      
      // exercise
      bstDest = std::move(bstSrc);
      // verify
      assertEmptyFixture(bstSrc);
      assertEmptyFixture(bstDest);
   }  // teardown

   // assignment-move operator: empty = move(standard)
   void test_assignMove_standardToEmpty()
   {  // setup
      //                (50b) = sSrc
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  bstSrc;
      setupStandardFixture(bstSrc);
      custom::set  bstDest;
      
      // exercise
      bstDest = std::move(bstSrc);
      // verify
      assertStandardFixture(bstDest);
      assertEmptyFixture(bstSrc);
      // teardown
      teardownStandardFixture(bstDest);
   }

   // assignment-move operator: standard = move(empty)
   void test_assignMove_emptyToStandard()
   {  // setup
      custom::set  sSrc;
      //                (50b) = sDest
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sDest;
      setupStandardFixture(sDest);
      
      // exercise
      sDest = std::move(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // assignment-move operator : one = standard
   void test_assignMove_oneToStandard()
   {  // setup
      //                (50b) = sSrc
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sSrc;
      setupStandardFixture(sSrc);
      //                (99) = bstDest
      custom::set  sDest;
      custom::BST<int> ::BNode* p99 = new custom::BST<int>::BNode(int(99));
      sDest.bst.root = p99;
      sDest.bst.numElements = 1;
      
      // exercise
      sDest = std::move(sSrc);
      // verify
      //                (50b)
      //          +-------+-------+
      //        (30r)           (70r)
      //     +----+----+     +----+----+
      //   (20b)     (40b) (60b)     (80b)
      assertStandardFixture(sDest);
      assertEmptyFixture(sSrc);
      // teardown
      teardownStandardFixture(sDest);
   }

   // assignment operator : standard = one
   void test_assignMove_standardToOne()
   {  // setup
      //                (99) = sSrc
      custom::set  sSrc;
      custom::BST<int>::BNode* p99 = new custom::BST<int>::BNode(int(99));
      sSrc.bst.root = p99;
      sSrc.bst.numElements = 1;
      //                (50b) = sDest
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sDest;
      setupStandardFixture(sDest);
      
      // exercise
      sDest = std::move(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      //                (99) = bstDest
      assertUnit(sDest.bst.root != nullptr);
      if (sDest.bst.root)
      {
         assertUnit(sDest.bst.root->data == int(99));
         assertUnit(sDest.bst.root->pParent == nullptr);
         assertUnit(sDest.bst.root->pLeft == nullptr);
         assertUnit(sDest.bst.root->pRight == nullptr);
      }
      // teardown
      teardownStandardFixture(sDest);
   }

   // assignment operator : standard = standard
   void test_assignMove_standardToStandard()
   {  // setup
      //                (50b) = sSrc
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sSrc;
      setupStandardFixture(sSrc);
      //                (50b) = sDest
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  sDest;
      setupStandardFixture(sDest);
      
      // exercise
      sDest = std::move(sSrc);
      // verify
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(sDest);
      assertEmptyFixture(sSrc);
      // teardown
      teardownStandardFixture(sDest);
   }

   /***************************************
    * Assignment
    *    set::operator=(const std::initializer_list<T>& il)
    ***************************************/

    // assignment operator: empty = {}
   void test_assignInit_emptyToEmpty()
   {  // setup
      custom::set  s;
      std::initializer_list<int> il{ };
      
      // exercise
      s = il;
      // verify
      assertEmptyFixture(s);
   }  // teardown

   // assignment operator: empty = {50, 30, 70, 20, 40, 60, 80}
   void test_assignInit_standardToEmpty()
   {  // setup
      custom::set  s;
      std::initializer_list<int> il{ int(50), int(30), int(70), int(20), int(40), int(60), int(80) };
      
      // exercise
      s = il;
      // verify
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // assignment operator: standard = {}
   void test_assignInit_emptyToStandard()
   {  // setup
      //                (50b) = sDest
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s;
      setupStandardFixture(s);
      std::initializer_list<int> il{ };
      
      
      // exercise
      s = il;
      // verify
      assertEmptyFixture(s);
   }  // teardown

   // assignment operator : one = {50, 30, 70, 20, 40, 60, 80}
   void test_assignInit_oneToStandard()
   {  // setup
      std::initializer_list <int>il{ int(50), int(30), int(70), int(20), int(40), int(60), int(80) };
      //                (99) = s
      custom::set  s;
      custom::BST<int>::BNode* p99 = new custom::BST<int>::BNode(int(99));
      s.bst.root = p99;
      s.bst.numElements = 1;
      
      // exercise
      s = il;
      // verify
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // assignment operator : standard = {99}
   void test_assignInit_standardToOne()
   {  // setup
      std::initializer_list<int> il{ int(99) };
      //                (50b) = s
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s;
      setupStandardFixture(s);
      
      // exercise
      s = il;
      // verify
      //                (99) = s.bst
      assertUnit(s.bst.root != nullptr);
      if (s.bst.root)
      {
         assertUnit(s.bst.root->data == int(99));
         assertUnit(s.bst.root->pParent == nullptr);
         assertUnit(s.bst.root->pLeft == nullptr);
         assertUnit(s.bst.root->pRight == nullptr);
      }
      // teardown
      teardownStandardFixture(s);
   }

   // assignment operator : standard = {50, 30, 70, 20, 40, 60, 80}
   void test_assignInit_standardToStandard()
   {  // setup
      std::initializer_list<int> il{ int(50), int(30), int(70), int(20), int(40), int(60), int(80) };
      //                (50b) = s
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s;
      setupStandardFixture(s);
      
      // exercise
      s = il;
      // verify
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }


   /***************************************
    * Swap
    *    set::swap(set &)
    ***************************************/

    // empty.swap(empty)
   void test_swap_emptyToEmpty()
   {  // setup
      custom::set  s1;
      custom::set  s2;
      
      // exercise
      s1.swap(s2);
      // verify
      assertEmptyFixture(s1);
      assertEmptyFixture(s2);
   }  // teardown

   // swap: standard.swap(empty)
   void test_swap_standardToEmpty()
   {  // setup
      //                (50b) = bst1
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s1;
      setupStandardFixture(s1);
      custom::set  s2;
      
      // exercise
      s1.swap(s2);
      // verify
      assertStandardFixture(s2);
      assertEmptyFixture(s1);
      // teardown
      teardownStandardFixture(s2);
   }

   // swap: empty.swap(standard)
   void test_swap_emptyToStandard()
   {  // setup
      custom::set  s1;
      //                (50b) = bst2
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s2;
      setupStandardFixture(s2);
      
      // exercise
      s1.swap(s2);
      // verify
      assertStandardFixture(s1);
      assertEmptyFixture(s2);
      // teardown
      teardownStandardFixture(s1);
   }

   // swap : standard.swap(standard)
   void test_swap_standardToStandard()
   {  // setup
      //                (50b) = s1
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s1;
      setupStandardFixture(s1);
      //                (50b) = s2
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s2;
      setupStandardFixture(s2);
      
      // exercise
      s1.swap(s2);
      // verify
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(s1);
      assertStandardFixture(s2);
      // teardown
      teardownStandardFixture(s1);
      teardownStandardFixture(s2);
   }


   /***************************************
    * CLEAR
    *    BST::clear()
    ***************************************/

    // clear an already empty fixture
   void test_clear_empty()
   {  // setup
      custom::set s;
      
      // exercise
      s.clear();
      // verify
      assertEmptyFixture(s);
   }  // teardown

   // clear the standard fixture
   void test_clear_standard()
   {  // setup
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s;
      setupStandardFixture(s);
      
      // exercise
      s.clear();
      // verify
      assertEmptyFixture(s);
   }  // teardown



   /***************************************
    * Find
    *    set::find(const T &)
    ***************************************/

 // attempt to find something in an empty BST
   void test_find_empty()
   {  // setup
      custom::set s;
      bool fFound;
      int num(50);
      
      // exercise
      fFound = s.find(num);
      // verify
      assertUnit(fFound == false);
      assertEmptyFixture(s);
   }  // teardown

   // attemp to find something where it is at the beginning
   void test_find_standardBegin()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      bool fFound;
      int num(20);
      
      // exercise
      fFound = s.find(num);
      // verify
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //  [[20]]      40    60        80  
      assertUnit(fFound == true);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // attempt to find something where it is the last element
   void test_find_standardLast()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      bool fFound;
      int num(80);
      
      // exercise
      fFound = s.find(num);
      // verify
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60      [[80]]
      assertUnit(fFound == true);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // attempt to find something where it is not there
   void test_find_standardMissing()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      bool fFound;
      int num(42);
      
      // exercise
      fFound = s.find(num);
      // verify
      assertUnit(fFound == false);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }


   /***************************************
    * INSERT
    *  set::insert(const T &)
    ***************************************/
   
   // insert an element when empty
   void test_insert_empty() 
   {  // setup
      custom::set s;
      int num(50);
      
      // exercise
      bool fReturn = s.insert(num);
      // verify
      assertUnit(fReturn == true);
      //            (50b)
      assertUnit(s.bst.root != nullptr);
      assertUnit(s.bst.numElements == 1);

      if (s.bst.root)
      {
         assertUnit(s.bst.root->data == int(50));
         assertUnit(s.bst.root->pLeft == nullptr);
         assertUnit(s.bst.root->pRight == nullptr);
         assertUnit(s.bst.root->pParent == nullptr);
      }
      // teardown
      delete s.bst.root;
      s.bst.root = nullptr;
      s.bst.numElements = 0;
   }

   // insert onto the end when there is excess capacity
   void test_insert_standardEnd()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+
      //    20        40    60     
      custom::set  s;
      setupStandardFixture(s);
      delete s.bst.root->pRight->pRight;
      s.bst.root->pRight->pRight = nullptr;
      s.bst.numElements = 6;
      int num(80);
      
      // exercise
      bool fReturn = s.insert(num);
      // verify
      assertUnit(fReturn == true);
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // insert to the beginning when we need to reallocat
   void test_insert_standardFront()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //          +----+     +----+----+
      //              40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      delete s.bst.root->pLeft->pLeft;
      s.bst.root->pLeft->pLeft = nullptr;
      s.bst.numElements = 6;
      int num(20);
      
      // exercise
      bool fReturn = s.insert(num);
      // verify
      assertUnit(fReturn == true);
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // insert into the middle when there is excess capacity
   void test_insert_standardMiddle() 
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+          +----+
      //    20        40              80  
      custom::set  s;
      setupStandardFixture(s);
      delete s.bst.root->pRight->pLeft;
      s.bst.root->pRight->pLeft = nullptr;
      s.bst.numElements = 6;
      int num(60);
      
      // exercise
      bool fReturn = s.insert(num);
      // verify
      assertUnit(fReturn == true);
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // insert when the elements are already there. Nothing is added
   void test_insert_standardDuplicate() 
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      int num(60);
      
      // exercise
      bool fReturn = s.insert(num);
      // verify
      assertUnit(fReturn == false);
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   
   /***************************************
    * INSERT MOVE
    *  set::insert(T &&)
    ***************************************/

 // insert an element when empty
   void test_insertMove_empty()
   {  // setup
      custom::set s;
      int num(50);
      
      // exercise
      bool fReturn = s.insert(std::move(num));
      // verify
      assertUnit(num == 50);
      assertUnit(fReturn == true);
      //            (50b)
      assertUnit(s.bst.root != nullptr);
      assertUnit(s.bst.numElements == 1);

      if (s.bst.root)
      {
         assertUnit(s.bst.root->data == int(50));
         assertUnit(s.bst.root->pLeft == nullptr);
         assertUnit(s.bst.root->pRight == nullptr);
         assertUnit(s.bst.root->pParent == nullptr);
      }
      // teardown
      delete s.bst.root;
      s.bst.root = nullptr;
      s.bst.numElements = 0;
   }

   // insert onto the end when there is excess capacity
   void test_insertMove_standardEnd()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+
      //    20        40    60     
      custom::set  s;
      setupStandardFixture(s);
      delete s.bst.root->pRight->pRight;
      s.bst.root->pRight->pRight = nullptr;
      s.bst.numElements = 6;
      int num(80);
      
      // exercise
      bool fReturn = s.insert(std::move(num));
      // verify
      assertUnit(num == 80);
      assertUnit(fReturn == true);
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // insert to the beginning when we need to reallocat
   void test_insertMove_standardFront()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //          +----+     +----+----+
      //              40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      delete s.bst.root->pLeft->pLeft;
      s.bst.root->pLeft->pLeft = nullptr;
      s.bst.numElements = 6;
      int num(20);
      
      // exercise
      bool fReturn = s.insert(std::move(num));
      // verify
      assertUnit(num == 20);
      assertUnit(fReturn = true);
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // insert into the middle when there is excess capacity
   void test_insertMove_standardMiddle()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+          +----+
      //    20        40              80  
      custom::set  s;
      setupStandardFixture(s);
      delete s.bst.root->pRight->pLeft;
      s.bst.root->pRight->pLeft = nullptr;
      s.bst.numElements = 6;
      int num(60);
      
      // exercise
      bool fReturn = s.insert(std::move(num));
      // verify
      assertUnit(num == 60);
      assertUnit(fReturn == true);
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // insert when the elements are already there. Nothing is added
   void test_insertMove_standardDuplicate()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      int num(60);
      
      // exercise
      bool fReturn = s.insert(std::move(num));
      // verify
      assertUnit(fReturn == false);
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   /***************************************
    * Insert Initializer
    *    set::insert(const std::initializer_list<T>& il)
    ***************************************/

   // insert: empty.insert({})
   void test_insertInit_emptyInsertNone()
   {  // setup
      custom::set  s;
      std::initializer_list<int> il{ };
      
      // exercise
      s.insert(il);
      // verify
      assertEmptyFixture(s);
   }  // teardown

   // insert: empty.insert({50, 30, 70, 20, 40, 60, 80})
   void test_insertInit_emptyInsertMany()
   {  // setup
      custom::set  s;
      std::initializer_list<int> il{ int(50), int(30), int(70), int(20), int(40), int(60), int(80) };
      
      // exercise
      s.insert(il);
      // verify
      //                (50b)
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // insert: standard.insert({})
   void test_insertInit_standardInsertNone()
   {  // setup
      //                (50b) = s
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s;
      setupStandardFixture(s);
      std::initializer_list<int> il{ };
      
      // exercise
      s.insert(il);
      // verify
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }  

   // insert : standard.insert({50, 30})
   void test_insertInit_standardInsertDuplicates()
   {  // setup
      std::initializer_list<int> il{ int(50), int(40) };
      //                (50b) = s
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      custom::set  s;
      setupStandardFixture(s);
      
      // exercise
      s.insert(il);
      // verify
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // assignment operator : standard = {99}
   void test_insertInit_manyInsertMany()
   {  // setup
      //                (50b) = s
      //          +-------+-------+
      //        (30b)           (70b)
      custom::set  s;
      custom::BST<int>::BNode* p50 = new custom::BST<int>::BNode(int(50));
      custom::BST<int>::BNode* p30 = new custom::BST<int>::BNode(int(30));
      custom::BST<int>::BNode* p70 = new custom::BST<int>::BNode(int(70));
      s.bst.root = p30->pParent = p70->pParent = p50;
      p50->pRight = p70;
      p50->pLeft  = p30;
      s.bst.numElements = 3;
      std::initializer_list<int> il{ int(20), int(40), int(60), int(80) };
      
      // exercise
      s.insert(il);
      // verify
      //                (50b) = s
      //          +-------+-------+
      //        (30b)           (70b)
      //     +----+----+     +----+----+
      //   (20r)     (40r) (60r)     (80r)
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   /***************************************
    * Insert Range
    *    set::insert(itBegin, itBEnd)
    ***************************************/

 // erase from an empty BST
   void test_eraseRange_several()
   {  // setup
      //                 40 
      //          +-------+-------+
      //         20              60  
      custom::set s{40, 20, 60};
      std::vector<int> v{30, 50, 70, 90};
      auto itBegin = v.begin();
      auto itEnd = v.begin();
      ++itEnd;
      ++itEnd;
      // exercise
      s.insert(itBegin, itEnd);
      // verify
      //                 40 
      //          +-------+-------+
      //         20              60  
      //          +---+       +---+
      //              30      50
      assertUnit(s.bst.numElements == 5);
      assertUnit(s.bst.root != nullptr);
      if (s.bst.root)
      {
         assertUnit(s.bst.root->data == 40);
         assertUnit(s.bst.root->pLeft != nullptr);
         assertUnit(s.bst.root->pRight != nullptr);
         if (s.bst.root->pLeft)
         {
            assertUnit(s.bst.root->pLeft->data == 20);
            assertUnit(s.bst.root->pLeft->pLeft == nullptr);
            assertUnit(s.bst.root->pLeft->pRight != nullptr);
            if (s.bst.root->pLeft->pRight)
               assertUnit(s.bst.root->pLeft->pRight->data == 30);
         }
         if (s.bst.root->pRight)
         {
            assertUnit(s.bst.root->pRight->data == 60);
            assertUnit(s.bst.root->pRight->pLeft != nullptr);
            if (s.bst.root->pRight->pLeft)
               assertUnit(s.bst.root->pRight->pLeft->data == 50);
            assertUnit(s.bst.root->pRight->pRight == nullptr);
         }
      }      
      // teardown
   }

  
 
   /***************************************
    * Erase Value
    *    set::erase(const T &)
    ***************************************/

    // erase from an empty BST
   void test_eraseValue_empty()
   {  // setup
      custom::set  s;
      int newInt(99);
      
      // exercise
      size_t num = s.erase(newInt);
      // verify
      assertUnit(num == 0);
      assertEmptyFixture(s);
   }  // teardown

   // erase with an empty iterator
   void test_eraseValue_standardMissing()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      int newInt(65);
      
      // exercise
      size_t num = s.erase(newInt);
      // verify
      assertUnit(num == 0);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }  // teardown

   // remove a leaf node from the standard fixture
   void test_eraseValue_noChildren()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         30              70  
      //     +----+----+     +----+----+
      //    20        40    60        80  
      custom::set  s;
      setupStandardFixture(s);
      int newInt(60);
      
      // exercise
      size_t num = s.erase(newInt);
      // verify
      //                 50 
      //          +-------+-------+
      //         30            [[70]]
      //     +----+----+          +----+
      assertUnit(num == 1);
      assertUnit(s.bst.root->pRight->pLeft == nullptr);
      assertUnit(s.bst.numElements == 6);
      s.bst.root->pRight->pLeft = new custom::BST<int>::BNode(int(60));
      s.bst.root->pRight->pLeft->pParent = s.bst.root->pRight;
      s.bst.numElements = 7;
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }  // teardown

   void test_eraseValue_oneChild()
   {  // setup
      //                 50 
      //          +-------+-------+
      //         10              60
      //          +----+     
      //              30          
      //            +--+--+
      //           20    40
      custom::set  s;
      auto p10 = new custom::BST<int>::BNode(10);
      auto p20 = new custom::BST<int>::BNode(20);
      auto p30 = new custom::BST<int>::BNode(30);
      auto p40 = new custom::BST<int>::BNode(40);
      auto p50 = new custom::BST<int>::BNode(50);
      auto p60 = new custom::BST<int>::BNode(60);
      s.bst.root = p10->pParent = p60->pParent = p50;
      p50->pLeft = p30->pParent = p10;
      p50->pRight = p60;
      p10->pRight = p20->pParent = p40->pParent = p30;
      p30->pLeft = p20;
      p30->pRight = p40;
      s.bst.numElements = 6;
      // exercise
      size_t num = s.erase(10);
      // verify
      //                 50
      //          +-------+-------+
      //         30              60
      //     +----+----+
      //  [[20]]      40
      assertUnit(num == 1);
      assertUnit(s.bst.numElements == 5);
      assertUnit(s.bst.root == p50);
      assertUnit(p50->pLeft == p30);
      assertUnit(p50->pRight == p60);
      assertUnit(p30->pLeft == p20);
      assertUnit(p30->pRight = p40);
      assertUnit(p30->pParent == p50);
      assertUnit(p20->pParent == p30);
      assertUnit(p40->pParent == p30);
      assertUnit(p60->pParent == p50);
      assertUnit(p20->data == 20);
      assertUnit(p30->data == 30);
      assertUnit(p40->data == 40);
      assertUnit(p50->data == 50);
      assertUnit(p60->data == 60);
      // teardown
      delete p20;
      delete p30;
      delete p40;
      delete p50;
      delete p60;
      s.bst.numElements = 0;
      s.bst.root = nullptr;
   }

   void test_eraseValue_twoChildren()
   {  // setup
      //                 70 
      //          +-------+-------+
      //         20              80
      //     +----+----+     
      //    10        50          
      //            +--+--+
      //           30    60
      //            +-+
      //              40 
      custom::set  s;
      auto p10 = new custom::BST<int>::BNode(10);
      auto p20 = new custom::BST<int>::BNode(20);
      auto p30 = new custom::BST<int>::BNode(30);
      auto p40 = new custom::BST<int>::BNode(40);
      auto p50 = new custom::BST<int>::BNode(50);
      auto p60 = new custom::BST<int>::BNode(60);
      auto p70 = new custom::BST<int>::BNode(70);
      auto p80 = new custom::BST<int>::BNode(80);
      s.bst.root = p20->pParent = p80->pParent = p70;
      p10->pParent = p50->pParent = p70->pLeft = p20;
      p70->pRight = p80;
      p20->pLeft = p10;
      p20->pRight = p30->pParent = p60->pParent = p50;
      p50->pLeft = p40->pParent = p30;
      p50->pRight = p60;
      p30->pRight = p40;
      s.bst.numElements = 8;
      // exercise
      size_t num = s.erase(20);
      // verify
      //                 70
      //          +-------+-------+
      //       [[30]]            80
      //     +----+----+     
      //    10        50    
      //            +--+--+
      //           40    60
      assertUnit(num == 1);
      assertUnit(s.bst.root == p70);
      assertUnit(s.bst.numElements == 7);
      assertUnit(p70->pLeft == p30);
      assertUnit(p70->pRight == p80);
      assertUnit(p30->pLeft == p10);
      assertUnit(p30->pRight = p50);
      assertUnit(p50->pLeft == p40);
      assertUnit(p50->pRight = p60);
      assertUnit(p30->pParent == p70);
      assertUnit(p80->pParent == p70);
      assertUnit(p10->pParent == p30);
      assertUnit(p50->pParent == p30);
      assertUnit(p40->pParent == p50);
      assertUnit(p60->pParent == p50);
      assertUnit(p10->data == 10);
      assertUnit(p30->data == 30);
      assertUnit(p40->data == 40);
      assertUnit(p50->data == 50);
      assertUnit(p60->data == 60);
      assertUnit(p70->data == 70);
      assertUnit(p80->data == 80);
      // teardown
      delete p10;
      delete p30;
      delete p40;
      delete p50;
      delete p60;
      delete p70;
      delete p80;
      s.bst.numElements = 0;
      s.bst.root = nullptr;
   }


   /*************************************************************
    * SETUP STANDARD FIXTURE
    *                (50b)
    *          +-------+-------+
    *        (30b)           (70b)
    *     +----+----+     +----+----+
    *   (20r)     (40r) (60r)     (80r)
    *************************************************************/
   void setupStandardFixture(custom::set& s)
   {
      // make sure that bst is clean
      assertUnit(s.bst.numElements == 0);
      assertUnit(s.bst.root == nullptr);

      // allocate
      custom::BST<int>::BNode* p20 = new custom::BST<int>::BNode(int(20));
      custom::BST<int>::BNode* p30 = new custom::BST<int>::BNode(int(30));
      custom::BST<int>::BNode* p40 = new custom::BST<int>::BNode(int(40));
      custom::BST<int>::BNode* p50 = new custom::BST<int>::BNode(int(50));
      custom::BST<int>::BNode* p60 = new custom::BST<int>::BNode(int(60));
      custom::BST<int>::BNode* p70 = new custom::BST<int>::BNode(int(70));
      custom::BST<int>::BNode* p80 = new custom::BST<int>::BNode(int(80));

      // hook up the pointers down
      p30->pLeft = p20;
      p30->pRight = p40;
      p50->pLeft = p30;
      p50->pRight = p70;
      p70->pLeft = p60;
      p70->pRight = p80;

      // hook up the pointers up
      p20->pParent = p40->pParent = p30;
      p30->pParent = p70->pParent = p50;
      p60->pParent = p80->pParent = p70;

      // color everything

      // now assign everything to the bst
      s.bst.root = p50;
      s.bst.numElements = 7;
   }

   /*************************************************************
    * TEARDOWN STANDARD FIXTURE
    *************************************************************/
   void teardownStandardFixture(custom::set& s)
   {
      s.bst.clear();
   }

   /*************************************************************
    * VERIFY EMPTY FIXTURE
    *************************************************************/
   void assertEmptyFixtureParameters(const custom::set &s, int line, const char* function)
   {
      assertIndirect(s.bst.root == nullptr);
      assertIndirect(s.bst.numElements == 0);
   }


   /*************************************************************
    * VERIFY STANDARD FIXTURE
    *                (50b)
    *          +-------+-------+
    *        (30b)           (70b)
    *     +----+----+     +----+----+
    *   (20r)     (40r) (60r)     (80r)
    *************************************************************/
   void assertStandardFixtureParameters(const custom::set& s, int line, const char* function)
   {
      // verify the member variables
      assertIndirect(s.bst.numElements == 7);
      assertIndirect(s.bst.root != nullptr);

      // verify the pointers down
      assertIndirect(s.bst.root != nullptr);
      if (s.bst.root)
      {
         assertIndirect(s.bst.root->data == int(50));
         assertIndirect(s.bst.root->pParent == nullptr);
         assertIndirect(s.bst.root->pLeft != nullptr);
         if (s.bst.root->pLeft)
         {
            assertIndirect(s.bst.root->pLeft->data == int(30));
            assertIndirect(s.bst.root->pLeft->pParent == s.bst.root);
            assertIndirect(s.bst.root->pLeft->pLeft != nullptr);
            if (s.bst.root->pLeft->pLeft)
            {
               assertIndirect(s.bst.root->pLeft->pLeft->data == int(20));
               assertIndirect(s.bst.root->pLeft->pLeft->pParent == s.bst.root->pLeft);
               assertIndirect(s.bst.root->pLeft->pLeft->pLeft == nullptr);
               assertIndirect(s.bst.root->pLeft->pLeft->pRight == nullptr);
            }
            assertIndirect(s.bst.root->pLeft->pRight != nullptr);
            if (s.bst.root->pLeft->pRight)
            {
               assertIndirect(s.bst.root->pLeft->pRight->data == int(40));
               assertIndirect(s.bst.root->pLeft->pRight->pParent == s.bst.root->pLeft);
               assertIndirect(s.bst.root->pLeft->pRight->pLeft == nullptr);
               assertIndirect(s.bst.root->pLeft->pRight->pRight == nullptr);
            }
         }
         assertIndirect(s.bst.root->pRight != nullptr);
         if (s.bst.root->pRight)
         {
            assertIndirect(s.bst.root->pRight->data == int(70));
            assertIndirect(s.bst.root->pRight->pParent == s.bst.root);
            assertIndirect(s.bst.root->pRight->pLeft != nullptr);
            if (s.bst.root->pRight->pLeft)
            {
               assertIndirect(s.bst.root->pRight->pLeft->data == int(60));
               assertIndirect(s.bst.root->pRight->pLeft->pParent == s.bst.root->pRight);
               assertIndirect(s.bst.root->pRight->pLeft->pLeft == nullptr);
               assertIndirect(s.bst.root->pRight->pLeft->pRight == nullptr);
            }
            assertIndirect(s.bst.root->pRight->pRight != nullptr);
            if (s.bst.root->pRight->pRight)
            {
               assertIndirect(s.bst.root->pRight->pRight->data == int(80));
               assertIndirect(s.bst.root->pRight->pRight->pParent == s.bst.root->pRight);
               assertIndirect(s.bst.root->pRight->pRight->pLeft == nullptr);
               assertIndirect(s.bst.root->pRight->pRight->pRight == nullptr);
            }
         }
      }
   }


};

#endif // DEBUG
