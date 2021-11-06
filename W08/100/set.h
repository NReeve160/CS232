/***********************************************************************
* Header:
*    Set
* Summary:
*      __       ____       ____         __
*     /  |    .'    '.   .'    '.   _  / /
*     `| |   |  .--.  | |  .--.  | (_)/ /
*      | |   | |    | | | |    | |   / / _
*     _| |_  |  `--'  | |  `--'  |  / / (_)
*    |_____|  '.____.'   '.____.'  /_/
*
*    This will contain the class definition of:
*        set                 : A class that represents a Set
*        set::iterator       : An iterator through Set
* Author
*   Everett Tsosie
*      Time: 3.5 hours
*      Challenges:The hardest part was working with the BST file at the same time as working with 
*      the set file. The way they are connected in the UML diagram is slightly confusing for me to
*      understand. Other than that confusion, the functions are rather trivial.
*
*   Nathan Reeve
*      Time: 1 hour
*      Challenges: Because of work requiring overtime I was unable to contribute to the project or 
*      gain a practical understanding of the work
*
*   David Sloan
*      Time: 4 hours
*      Challenges: I mostly worked on getting the iterator set up and trying to figure out how to
*      a for each loop in C++. I also had issues with getting seg fault errors upon compiling after
*      getting certain portions of the code up and running. I had to get the work from another *      teammate to make it work.
*
*   Stephen Harrison
*      Time: N/A
*      Challenges:N/A
*
*   I was unable to contact Stephen for an official comment before we had to turn in the assignment.
*   I know he worked on it and got up to approximately 37% completion as part of what we discussed
*   in our group chat and team meetings.
************************************************************************/

#pragma once

#include <cassert>
#include <iostream>
#include "bst.h"
#include <memory>     // for std::allocator
#include <functional> // for std::less


namespace custom
{

/************************************************
 * SET
 * A class that represents a Set
 ***********************************************/
template <typename T>
class set
{
public:
   
   // 
   // Construct
   //
   set( ) : bst()
   { 
   }
   set(const set &  rhs) : bst(rhs.bst)
   { 
   }
   set(set && rhs) : bst(std::move(rhs.bst))
   { 
   }
   set(const std::initializer_list <T> & il) 
   {
       clear();
       for (T element : il)
           insert(element);
   }
   template <class Iterator>
   set(Iterator first, Iterator last) 
   {
       while (first != last) {
           insert(*first);
           first++;
       }
   }
   ~set() { clear(); }

   //
   // Assign
   //

   set & operator = (const set & rhs)
   {
       clear();
       bst = rhs.bst;
      return *this;
   }
   set & operator = (set && rhs)
   {
       clear();
       swap(rhs);
       return *this;
   }
   set & operator = (const std::initializer_list <T> & il)
   {
       clear();
       for (auto&& element : il)
           insert(element);
      return *this;
   }
   void swap(set& rhs) noexcept
   {
       bst.swap(rhs.bst);
   }

   //
   // Iterator
   //

   class iterator;
   iterator begin() const noexcept 
   { 
      return iterator(bst.begin()); 
   }
   iterator end() const noexcept 
   { 
      return iterator(bst.end()); 
   }

   //
   // Access
   //
   iterator find(const T& t) 
   { 
      return bst.find(t); 
   }

   //
   // Status
   //
   bool   empty() const noexcept 
   { 
      return size() == 0;    
   }
   size_t size() const noexcept 
   { 
      return bst.numElements;     
   }

   //
   // Insert
   //
   std::pair<iterator, bool> insert(const T& t)
   {
      std::pair<iterator, bool> p = bst.insert(t, true);
      return p;
   }
   std::pair<iterator, bool> insert(T&& t)
   {
      std::pair<iterator, bool> p = bst.insert(std::move(t), true);
      return p;
   }
   void insert(const std::initializer_list <T>& il)
   {
       for (auto&& element : il)
           insert(element);
   }
   template <class Iterator>
   void insert(Iterator first, Iterator last)
   {
       while (first != last)
       {
           insert(*first);
           first++;
       }
   }


   //
   // Remove
   //
   void clear() noexcept 
   { 
       bst.clear();
   }
   iterator erase(iterator &it)
   { 
      return iterator(bst.erase(it.it)); 
   }
   size_t erase(const T & t) 
   {
       iterator it = find(t);
       if (it == end())
           return 0;
       erase(it);
       return 1;
   }
   iterator erase(iterator &itBegin, iterator &itEnd)
   {
       while (itBegin != itEnd)
           itBegin = erase(itBegin);
      return iterator(itEnd);
   }

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   
   custom::BST <T> bst;
};


/**************************************************
 * SET ITERATOR
 * An iterator through Set
 *************************************************/
template <typename T>
class set <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator() 
   { 
       it = NULL;
   }
   iterator(const typename custom::BST<T>::iterator& itRHS) 
   {  
       it = itRHS;
   }
   iterator(const iterator & rhs) 
   { 
       it = rhs.it;
   }
   iterator & operator = (const iterator & rhs)
   {
       it = rhs.it;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const 
   { 
      return it != rhs.it; 
   }
   bool operator == (const iterator & rhs) const 
   { 
      return it == rhs.it; 
   }

   // dereference operator: by-reference so we can modify the Set
   const T & operator * () const 
   { 
      return *it; 
   }

   // prefix increment
   iterator & operator ++ ()
   {
       it++;
      return *this;
   }

   // postfix increment
   iterator operator++ (int postfix)
   {
       iterator temp(*this);
       ++it;
      return temp;
   }
   
   // prefix decrement
   iterator & operator -- ()
   {
       it--;
      return *this;
   }
   
   // postfix decrement
   iterator operator-- (int postfix)
   {
       iterator temp(*this);
       --it;
      return temp;
   }
   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   typename custom::BST<T>::iterator it;
};

/***********************************************
 * SET : EQUIVALENCE
 * See if two sets are the same size
 ***********************************************/
template <typename T>
bool operator == (const set <T> & lhs, const set <T> & rhs)
{
   return lhs == rhs;
}

template <typename T>
inline bool operator != (const set <T> & lhs, const set <T> & rhs)
{
   return lhs != rhs;
}

/***********************************************
 * SET : RELATIVE COMPARISON
 * See if one set is lexicographically before the second
 ***********************************************/
template <typename T>
bool operator < (const set <T> & lhs, const set <T> & rhs)
{
   return lhs < rhs;
}

template <typename T>
inline bool operator > (const set <T> & lhs, const set <T> & rhs)
{
   return lhs > rhs;
}

}; // namespace custom