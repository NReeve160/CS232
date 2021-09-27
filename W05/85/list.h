/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Our custom implementation of std::list
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 *
 *
 *    This will contain the class definition of:
 *        List         : A class that represents a List
 *        ListIterator : An iterator through List
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once
#include <cassert>     // for ASSERT
#include <iostream>    // for nullptr
#include <new>         // std::bad_alloc
#include <memory>      // for std::allocator

namespace custom
{
/**************************************************
 * LIST
 * Just like std::list
 **************************************************/
class list
{
public:
   
   //
   // Construct
   //

   list();
   list(list & rhs);
   list(list && rhs);
   list(size_t num, const int & t);
   list(size_t num);
   list(const std::initializer_list<int>& il);
    template <class Iterator>
   list(Iterator first, Iterator last);
   ~list()
   { 

   }

   //
   // Assign
   //

   list & operator = (list &  rhs);
   list & operator = (list && rhs);
   list & operator = (const std::initializer_list<int>& il);

   //
   // Access
   //

   int& front();
   int& back();

   //
   // Iterator
   //

   class iterator;
   iterator begin();
   iterator end();

   //
   // Insert
   //

   void push_front(const int& data);
   void push_front(int&& data);
   void push_back(const int& data);
   void push_back(int&& data);
   iterator insert(iterator it, const int& data);
   iterator insert(iterator it, int&& data);

   //
   // Remove
   //

   void clear();
   void pop_back();
   void pop_front();
   iterator erase(const iterator& it);

   // 
   // Status
   //

   bool empty()  const { return true; }
   size_t size() const { return 99; }
     
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   // nested linked list class
   class Node;
   
   // member variables
   size_t numElements; // though we could count, it is faster to keep a variable
   Node * pHead;    // pointer to the beginning of the list
   Node * pTail;    // pointer to the ending of the list
};
void swap(list & lhs, list & rhs);
/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
class list :: Node
{
public:
   //
   // Construct
   //
   Node()
   {
      pNext = pPrev = this;
   }
   Node(const int & data)
   {
      pNext = pPrev = this;
   }
   Node(int && data)
   {
      pNext = pPrev = this;
   }
   
   //
   // DATA
   //
   
   int data;                 // user data
   Node * pNext;       // pointer to next node
   Node * pPrev;       // pointer to previous node
};


/*************************************************
 * LIST ITERATOR
 * Iterate through a List, non-constant version
 ************************************************/
class list :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator( ) 
   {
      p = new list::Node;
   }
   iterator(Node * p) 
   {
      p = new list::Node;
   }
   iterator(const iterator  & rhs) 
   { 
      p = new list::Node;
   }
   iterator & operator = (const iterator & rhs)
   {
      return *this;
   }
   
   // equals, not equals operator
   bool operator == (const iterator & rhs) const { return true; }
   bool operator != (const iterator & rhs) const { return true; }
   
   // dereference operator, fetch a node
   int & operator * ()
   {
      return *(new int(99));
   }
   
   // postfix increment
   iterator operator ++ (int postfix)
   {
      return *this;
   }
   
   // prefix increment
   iterator & operator ++ ()
   {
      return *this;
   }
   
   // postfix decrement
   iterator operator -- (int postfix)
   {
      return *this;
   }
   
   // prefix decrement
   iterator & operator -- ()
   {
      return *this;
   }
   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   
   typename list :: Node * p;
};


/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
inline list ::list(size_t num, const int & t)
{
   numElements = 99;
   pHead = pTail = new list ::Node();
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
inline list ::list(size_t num) 
{
   numElements = 99;
   pHead = pTail = new list::Node();
}

/*****************************************
 * LIST :: DEFAULT constructor
 ****************************************/
inline list::list() 
{
   numElements = 99;
   pHead = pTail = new list::Node();
}

/*****************************************
 * LIST :: COPY constructor
 ****************************************/
inline list::list(list& rhs)
{
   numElements = 99;
   pHead = pTail = new list::Node();
}

/*****************************************
 * LIST :: INIT constructor
 ****************************************/
inline list::list(const std::initializer_list<int>& il)
{
   numElements = 99;
   pHead = pTail = new list::Node();
}

/*****************************************
 * LIST :: RANGEconstructor
 ****************************************/
template <class Iterator>
inline list::list(Iterator first, Iterator last)
{
   numElements = 99;
   pHead = pTail = new list::Node();
}

/*****************************************
 * LIST :: MOVE constructors
 * Steal the values from the RHS
 ****************************************/
inline list ::list(list && rhs) 
{
   numElements = 99;
   pHead = pTail = new list::Node();
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
inline list & list  :: operator = (list && rhs)
{
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
inline list & list :: operator = (list & rhs)
{
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
inline list & list :: operator = (const std::initializer_list<int>& rhs)
{
   return *this;
}

/**********************************************
 * LIST :: CLEAR
 * Remove all the items currently in the linked list
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
inline void list :: clear()
{

}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
inline void list :: push_back(const int & data)
{

}

inline void list ::push_back(int && data)
{

}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
inline void list :: push_front(const int & data)
{

}

inline void list ::push_front(int && data)
{

}


/*********************************************
 * LIST :: POP BACK
 * remove an item from the end of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
inline void list ::pop_back()
{

}

/*********************************************
 * LIST :: POP FRONT
 * remove an item from the front of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
inline void list ::pop_front()
{

}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  :
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
inline int & list :: front()
{
   return *(new int(99));
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  :
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
inline int & list :: back()
{
   return *(new int(99));
}


/******************************************
 * LIST :: REMOVE
 * remove an item from the middle of the list
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location
 *     COST   : O(1)
 ******************************************/
inline typename list :: iterator  list :: erase(const list :: iterator & it)
{
   return end();
}

/******************************************
 * LIST :: INSERT
 * add an item to the middle of the list
 *     INPUT  : data to be added to the list
 *              an iterator to the location where it is to be inserted
 *     OUTPUT : iterator to the new item
 *     COST   : O(1)
 ******************************************/
inline typename list :: iterator list :: insert(list :: iterator it,
                                                const int & data)
{
   return end();
}

inline typename list ::iterator list  ::insert(list ::iterator it,
                                               int && data)
{
   return end();
}


/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
void swap(list & lhs, list & rhs)
{

}

/*********************************************
 * LIST :: begin
 * returns the first slot of the list
 *     INPUT  :
 *     OUTPUT : teratator
 *     COST   : O(1)
 *********************************************/
inline typename list::iterator list::begin()
{
   return list::iterator ();
   
}

/*********************************************
 * LIST :: end
 * returns the first slot off the end of the list
 *     INPUT  :
 *     OUTPUT : iteratator
 *     COST   : O(1)
 *********************************************/
inline typename list::iterator list::end()
{
   return list::iterator ();
}


}; // namespace custom
