/***********************************************************************
 * Header:
 *    PRIORITY QUEUE
 * Summary:
 *    Our custom implementation of std::priority_queue
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        priority_queue          : A class that represents a Priority Queue
 * Author
 *    David Sloan
 ************************************************************************/

#pragma once

#include <cassert>
#include "vector.h"

namespace custom
{

/*************************************************
 * P QUEUE
 * Create a priority queue.
 *************************************************/
template<class T>
class priority_queue
{
public:

   //
   // construct
   //
   priority_queue() {
      container.numElements = 0;
   }

   priority_queue(const priority_queue &  rhs) {
      // *this = rhs;
   }

   priority_queue(priority_queue && rhs) {
      // *this = std::move(rhs);
   }

   template <class Iterator>
   priority_queue(Iterator first, Iterator last) {
      container.reserve(last - first);
      for (int element = first; last; first++)
      {
         push(element);
         first == first++;
      }
      
   }

   explicit priority_queue (custom::vector<T> && rhs) {
      //TODO
   }

   explicit priority_queue (custom::vector<T>& rhs) {
      //TODO
   }

  ~priority_queue() {}

   //
   // Access
   //
   const T & top() const;

   //
   // Insert
   //
   void  push(const T& t);
   void  push(T&& t);     

   //
   // Remove
   //
   void  pop(); 

   //
   // Status
   //
   size_t size()  const { 
      return 99;   
   }

   bool empty() const { 
      return false;  
   }
   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   bool percolateDown(size_t indexHeap);      // fix heap from index down. This is a heap index!

   custom::vector<T> container; 

};

/************************************************
 * P QUEUE :: TOP
 * Get the maximum item from the heap: the top item.
 ***********************************************/
template <class T>
const T & priority_queue <T> :: top() const {
   return container.front();
}

/**********************************************
 * P QUEUE :: POP
 * Delete the top item from the heap.
 **********************************************/
template <class T>
void priority_queue <T> :: pop() {
   //TODO
}

/*****************************************
 * P QUEUE :: PUSH
 * Add a new element to the heap, reallocating as necessary
 ****************************************/
template <class T>
void priority_queue <T> :: push(const T & t) {
   //TODO
}

template <class T>
void priority_queue <T> :: push(T && t) {
   //TODO
}

/************************************************
 * P QUEUE :: PERCOLATE DOWN
 * The item at the passed index may be out of heap
 * order. Take care of that little detail!
 * Return TRUE if anything changed.
 ************************************************/
template <class T>
bool priority_queue <T> :: percolateDown(size_t indexHeap) {
   return false;
}

};

template <class T>
inline void swap(custom::priority_queue <T> & lhs,
                 custom::priority_queue <T> & rhs) {
   //TODO
}
