/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Our custom implementation of std::list
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        List         : A class that represents a List
 *        ListIterator : An iterator through List
 * Author
 *    David Sloan
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
template <typename T>
class list
{
public:  
   // 
   // Construct
   //

   list(); //default constructor
   list(list <T> & rhs); //copy constructor
   list(list <T>&& rhs); //move constructor
   list(size_t num, const T & t); //non-default value fill constructor
   list(size_t num); //non-default empty fill constructor
   list(const std::initializer_list<T>& il); //initializer list constructor
   template <class Iterator> //iterator declaration for the range constructor
   list(Iterator first, Iterator last); //range constructor
  ~list(){} //destructor

   // 
   // Assign
   //

   list <T> & operator = (list &  rhs); //copy-assign operator
   list <T> & operator = (list && rhs); //move-assign operator
   list <T> & operator = (const std::initializer_list<T>& il); //initializer list assign

   //
   // Iterator
   //

   class  iterator;
   iterator begin()  { return iterator(); } //first element read-write iterator
   iterator rbegin() { return iterator(); } //last element read-write iterator
   iterator end()    { return iterator(); } //returns the iterator for last element?

   //
   // Access
   //

   T& front(); //read-write access of the first element
   T& back(); //read-write access of the last element

   //
   // Insert
   //

   void push_front(const T&  data); //copy-insert an element to the front
   void push_front(      T&& data); //move-insert to the front
   void push_back (const T&  data); //copy-insert an element to the back
   void push_back (      T&& data); //move-insert to the back
   iterator insert(iterator it, const T& data); //copy-insert at 'it'
   iterator insert(iterator it, T&& data); //move-insert at 'it'

   //
   // Remove
   //

   void pop_back(); //remove the back element
   void pop_front(); //remove the front element
   void clear(); //remove all elements from the list
   iterator erase(const iterator& it); //erase one element

   // 
   // Status
   //

   bool empty()  const { return true; } //return bool if list is empty or not
   size_t size() const { return numElements;   } //return the size (numElements) of the list


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

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <typename T>
class list <T> :: Node
{
public:
   //
   // Construct
   //
   Node()  
   {
      pNext = pPrev = NULL;
   }
   Node(const T &  data)  
   {
      pNext = pPrev = NULL;
   }
   Node(      T && data)  
   {
      pNext = pPrev = NULL;
   }

   //
   // Data
   //

   T data;                 // user data
   Node * pNext;       // pointer to next node
   Node * pPrev;       // pointer to previous node
};

/*************************************************
 * LIST ITERATOR
 * Iterate through a List, non-constant version
 ************************************************/
template <typename T>
class list <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator() 
   {
      p = new typename list <T> ::Node;
   }
   iterator(Node * p) 
   {
      p = new typename list <T> ::Node;
   }
   iterator(const iterator  & rhs) 
   {
      p = new typename list <T> ::Node;
   }
   iterator & operator = (const iterator & rhs)
   {
      return *this;
   }
   
   // equals, not equals operator
   bool operator == (const iterator & rhs) const { return true; }
   bool operator != (const iterator & rhs) const { return true; }

   // dereference operator, fetch a node
   T & operator * ()
   {
      return *(new T);
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

   // two friends who need to access p directly
   friend iterator list <T> :: insert(iterator it, const T &  data);
   friend iterator list <T> :: insert(iterator it,       T && data);
   friend iterator list <T> :: erase(const iterator & it);

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   typename list <T> :: Node * p;
};

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num, const T & t) 
{
   //TODO: Figure out the logic.
   // if(num) 
   // {
   //    pHead = new Node(T);
   //    pPrevious = new Node(T);
   //    pNew = new Node(T);
   //    pHead.pPrev = nullptr;

   //    for (i = 1; i < num-1; i++)
   //    {
   //       pNew = new Node(T);
   //       pNew.pPrev = pPrev;
   //       pNew.pPrev.pNext = pNew;
   //       pPrevious = pNew
   //    }

   //    pNew.pNext = nullptr;
   //    pTail = pNew;
   // }

   numElements = num;
}

/*****************************************
 * LIST :: ITERATOR constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
template <class Iterator>
list <T> ::list(Iterator first, Iterator last)
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: INITIALIZER constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
list <T> :: list(const std::initializer_list<T>& il)
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> :: list(size_t num)
{
   numElements = 0;
}

/*****************************************
 * LIST :: DEFAULT constructors
 ****************************************/
template <typename T>
list <T> :: list() 
{
   numElements = 0;
   pHead = pTail = nullptr;
}

/*****************************************
 * LIST :: COPY constructors
 ****************************************/
template <typename T>
list <T> :: list(list& rhs) 
{
   numElements = 0;
   pHead = pTail = nullptr;

   //TODO: Maybe set an iterator just for this?
   // for (it = rhs.begin; rhs.end; it++)
   // {
   //    push_back(*it);
   // }

   //NOTE: Able to be used once copy-assign is functional
   // *this = rhs;
}

/*****************************************
 * LIST :: MOVE constructors
 * Steal the values from the RHS
 ****************************************/
template <typename T>
list <T> :: list(list <T>&& rhs)
{
   pHead = rhs.pHead;
   pTail = rhs.pTail;
   numElements = rhs.numElements;

   rhs.pHead = rhs.pTail = nullptr;
   rhs.numElements = 0;
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS 
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (list <T> && rhs)
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
template <typename T>
list <T> & list <T> :: operator = (list <T> & rhs)
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
template <typename T>
list <T>& list <T> :: operator = (const std::initializer_list<T>& rhs)
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
template <typename T>
void list <T> :: clear()
{

}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_back(const T & data)
{

}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_front(const T & data)
{

}

/*********************************************
 * LIST :: POP BACK
 * remove an item from the end of the list
 *    INPUT  : 
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_back()
{

}

/*********************************************
 * LIST :: POP FRONT
 * remove an item from the front of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_front()
{

}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: front()
{
   return *(new T);
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: back()
{
   return *(new T);
}

/******************************************
 * LIST :: REMOVE
 * remove an item from the middle of the list
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location 
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator  list <T> :: erase(const list <T> :: iterator & it)
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
template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
                                                 const T & data) 
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
template <typename T>
void swap(list <T> & lhs, list <T> & rhs)
{
   temphead = new Node();

   tempHead = rhs.pHead;
   rhs.pHead = pHead;
   pHead = tempHead;

   tempTail = rhs.pTail;
   rhs.pTail = pTail;
   pTail = tempTail;

   tempElements = rhs.numElements;
   rhs.numElements = numElements;
   numElements = tempElements;
}
//#endif
}; // namespace custom