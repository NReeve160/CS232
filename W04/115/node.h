/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    One node in a linked list (and the functions to support them).
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *    This will contain the class definition of:
 *        Node         : A class representing a Node
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    Everett Tsosie, Nathan Reeve, David Sloan
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

    Node() : data(T())
   { 
       pNext = NULL;
       pPrev = NULL;
   }
   Node(const T& data) : data(data)
   {
       pNext = NULL;
       pPrev = NULL;
   }

   Node(T&& data) : data(data)
   {
       pNext = NULL;
       pPrev = NULL;
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
inline Node <T> * copy(const Node <T> * pSource) 
{
    // Don't copy nullptrs (special case)
    if (pSource == nullptr)
        return nullptr;

    // Setup Destination variable (copy) to be returned
    Node<T>* pDestination = new Node<T>(pSource->data);
    const Node<T>* pSrc = pSource;
    Node<T>* pDes = pDestination;

    // iterate through Src and insert its data into Des
    for (pSrc = pSrc->pNext; pSrc; pSrc = pSrc->pNext)
        pDes = insert(pDes, pSrc->data, true);

    return pDestination; // done!
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
    const Node<T>* pSrc = pSource;
    Node<T>* pDes = pDestination;
    Node<T>* pDesPrevious = pDes;

    // While Src and Des both have data
    while (pSrc != NULL && pDes != NULL) {
        pDes->data = pSrc->data; // assign data
        pDesPrevious = pDes; // to remember pDes->pPrev
        // iterate
        pDes = pDes->pNext; 
        pSrc = pSrc->pNext;
    }

    // if Src list is longer than Des
    if (pSrc != NULL) {
        pDes = pDesPrevious; // remembered pDes->pPrev
        while (pSrc != NULL) {
            pDes = insert(pDes, pSrc->data, true);
            if (pDestination == NULL)
                pDestination = pDes;
            pSrc = pSrc->pNext;
        }
    }
    // if Des list is longer than Src
    else if (pDes != NULL) {
        // Special case var (when pSrc is empty)
        bool setToNull = false;
        
        // Safety
        if (pDes->pPrev)
            // Detach pDes from linked list
            pDes->pPrev->pNext = NULL;
        else
            setToNull = true;

        // Free extra data in pDes
        clear(pDes);

        // Handle special case (when pSrc is empty)
        if (setToNull)
            // Assign destination to be empty
            pDestination = NULL;
    }
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(Node <T>* &pLHS, Node <T>* &pRHS)
{
    Node<T>* pTemp = pLHS;
    pLHS = pRHS;
    pRHS = pTemp;
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
    if (NULL == pRemove)
        return NULL;

    // detach pRemove from the linked list
    if (pRemove->pPrev)
        pRemove->pPrev->pNext = pRemove->pNext;
    if (pRemove->pNext)
        pRemove->pNext->pPrev = pRemove->pPrev;

    // initialize reference node to return
    Node<T>* pReturn;
    if (pRemove->pPrev) {
        pReturn = pRemove->pPrev;
    }
    else {
        pReturn = pRemove->pNext;
    }
    delete pRemove; // Delete/Remove
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
                  bool after = false)
{
    Node<T>* pNew = new Node<T>(t);

    // Set up pointers for Node BEFORE pCurrent
    if (pCurrent != NULL && after == false) {
        pNew->pNext = pCurrent;
        pNew->pPrev = pCurrent->pPrev;
        pCurrent->pPrev = pNew;
        if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;
    }
    // Set up pointers for Node AFTER pCurrent
    if (pCurrent != NULL && after == true) {
        pNew->pPrev = pCurrent;
        pNew->pNext = pCurrent->pNext;
        pCurrent->pNext = pNew;
        if (pNew->pNext)
            pNew->pNext->pPrev = pNew;
    }

   return pNew;
}

/******************************************************
 * FIND
 * Find a given node in an unsorted linked list.  Return
 * a pointer to the node if it is found, NULL otherwise.
 *  INPUT   : a pointer to the head of the linked list
 *            the value to be found
 *  OUTPUT  : a pointer to the node if it is found
 *  COST    : O(n)
 ********************************************************/
template <class T>
inline size_t size(const Node <T> * pHead)
{
    int num = 0;
    for (const Node<T>* p = pHead; p; p = p->pNext)
        num++; // Count nodes in list
   return num;
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
 * FREE DATA
 * Free all the data currently in the linked list
 *   INPUT   : pointer to the head of the linked list
 *   OUTPUT  : pHead set to NULL
 *   COST    : O(n)
 ****************************************************/
template <class T>
inline void clear(Node <T> * & pHead)
{
    // iterate through and delete each node
    while (pHead != NULL) {
        Node<T>* pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
    }
}