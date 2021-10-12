/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    One node in a linked list (and the functions to support them).
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        Node         : A class representing a Node
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    David Sloan
 ************************************************************************/

#pragma once

#include <cassert>     // for ASSERT
#include <iostream>    // for NULL

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <class T>
class Node
{
public:

   //
   // Construct
   //

   Node()
   {
      pPrev = pNext = NULL;
   }
   Node(const T &  data)
   {
      pPrev = pNext = NULL;
   }
   Node(      T && data)
   {
      pPrev = pNext = NULL;
   }

   //
   // Member variables
   //

   T data;                 // user data
   Node <T> * pNext;       // pointer to next node
   Node <T> * pPrev;       // pointer to previous node
};

/***********************************************
 * COPY
 * Copy the list from the pSource and return
 * the new list
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline Node <T> * copy(const Node <T> * pSource) {
   if (pSource == nullptr) {
        return nullptr;
   }
   
   Node <T> * pDestination = new Node <T> (pSource->data);

   const Node <T> * pSrc = pSource;
   Node <T> * pDes = pDestination;

   for (pSrc = pSrc->pNext; pSrc; pSrc->pNext) {
      pDes = insert(pDes, pSrc->data, true);
   }
   
   return pDestination;
}

/***********************************************
 * Assign
 * Copy the values from pSource into pDestination
 * reusing the nodes already created in pDestination if possible.
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline void assign(Node <T> * & pDestination, const Node <T> * pSource)
{
   
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(Node <T>* &pLHS, Node <T>* &pRHS)
{

}

/***********************************************
 * REMOVE
 * Remove the node pSource in the linked list
 *   INPUT  : the node to be removed
 *   OUTPUT : the pointer to the parent node
 *   COST   : O(1)
 **********************************************/
template <class T>
inline Node <T> * remove(const Node <T> * pRemove) 
{
   if (pRemove == NULL) {
      return nullptr;
   }

   if (pRemove->pPrev) {
      pRemove->pPrev->pNext = pRemove->pNext;
   }

   if (pRemove->pNext) {
      pRemove->pNext->pPrev = pRemove->pPrev;
   }

   Node <T> * pReturn;

   if (pRemove->pPrev) {
      pReturn = pRemove->pPrev;
   } else {
      pReturn = pRemove->pNext;
   }

   delete pRemove;
   return pReturn;
}

/**********************************************
 * INSERT 
 * Insert a new node the the value in "t" into a linked
 * list immediately before the current position.
 *   INPUT   : t - the value to be used for the new node
 *             pCurrent - a pointer to the node before which
 *                we will be inserting the new node
 *             after - whether we will be inserting after
 *   OUTPUT  : return the newly inserted item
 *   COST    : O(1)
 **********************************************/
template <class T>
inline Node <T> * insert(Node <T> * pCurrent,
                  const T & t,
                  bool after)
{
   Node <T> * pNew = new Node <T> (t);

   if (pCurrent != NULL && after == false) {
      pNew->pNext = pCurrent;
      pNew->pPrev = pCurrent->pPrev;
      pCurrent->pPrev = pNew;

      if (pNew->pPrev) {
         pNew->pPrev->pNext = pNew;
      }

   } 
   
   if (pCurrent != NULL && after == true) {
      pNew->pNext = pCurrent;
      pNew->pPrev = pCurrent->pPrev;
      pCurrent->pNext = pNew;

      if (pNew->pNext) {
         pCurrent->pPrev = pNew;
      }
   }

   return pNew;
}

/******************************************************
 * Size
 * Return the size of the linked list.
 *  INPUT   : a pointer to the head of the linked list.
 *  OUTPUT  : the number of the size of the linked list.
 *  COST    : O(n)
 ********************************************************/
template <class T>
inline size_t size(const Node <T> * pHead)
{
   int s = 0;

   const Node <T> * p;

   for (p = pHead; p; p = p->pNext) {
     s++;
   }

   return s;
}

/***********************************************
 * DISPLAY
 * Display all the items in the linked list from here on back
 *    INPUT  : the output stream
 *             pointer to the linked list
 *    OUTPUT : the data from the linked list on the screen
 *    COST   : O(n)
 **********************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
{
   return out;
}

/*****************************************************
 * CLEAR
 * Free all the data currently in the linked list
 *   INPUT   : pointer to the head of the linked list
 *   OUTPUT  : pHead set to NULL
 *   COST    : O(n)
 ****************************************************/
template <class T>
inline void clear(Node <T> * & pHead)
{
   Node <T> * pDelete;

   while (pHead != NULL) {
      pDelete = pHead;

      pHead = pHead->pNext;

      delete pDelete;
   }
}