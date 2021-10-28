/***********************************************************************
 * Header:
 *    BINARY NODE
 * Summary:
 *    One node in a binary tree (and the functions to support them).
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        BNode         : A class representing a BNode
 *    Additionally, it will contain a few functions working on Node
 * Author
 *  David Sloan
 *      Time: 3 Hours
 *      Challenges: Trying to keep up with the rest of the team as they
 *      started and nearly finished the project on Monday before I was
 *      able to even get started. I dedicated most of my time trying to
 *      work on specific problems like the assign and swap functions.
 *  Nathan Reeve
 *      Time: 6 Hours
 *      Challenges: The biggest problem I had was figuring out how the 
 *      data was moving through the program and making sure that the 
 *      pointers and access points were all going where they were 
 *      supposed to go. I ended up making it more complicated than I 
 *      needed to when adding to either the left or the right of the tree 
 *      as well as swapping.
 *  Everett Tsosie
 *      Time: 3 Hours
 *      Challenges: At first I thought assign() would have been the 
 *      hardest to figure out. Then I realized that attaching the parents
 *      to the child nodes was just like the exercise done in the copy()
 *      function. The other error that stopped my momentum was setting
 *      the deleted value in clear() to NULL right after deletion.
 *  Stephen Harrison
 *      Time: 5 Hours
 *      Challenges: Assigning parent nodes.
 ************************************************************************/

#pragma once

#include <iostream>  // for OFSTREAM
#include <cassert>

/*****************************************************************
 * BNODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BNode
{
public:
   // 
   // Construct
   //
   BNode()
   {
      pParent = pLeft = pRight = NULL;
      data = T();
   }
   BNode(const T& t)
   {
       pParent = pLeft = pRight = NULL;
       data = t;
   }
   BNode(T&& t)
   {
       pParent = pLeft = pRight = NULL;
       data = t;
   }

   //
   // Data
   //
   BNode <T>* pLeft;
   BNode <T>* pRight;
   BNode <T>* pParent;
   T data;
};

/*******************************************************************
 * SIZE BTREE
 * Return the size of a b-tree under the current node
 *******************************************************************/
template <class T>
inline size_t size(const BNode <T> * p)
{
    if (!p)
        return 0;
    else
        return size(p->pLeft) + 1 + size(p->pRight);
}


/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft(BNode <T> * pNode, BNode <T> * pAdd)
{
    if (pAdd)
        pAdd->pParent = pNode;
    pNode->pLeft = pAdd;
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
inline void addRight (BNode <T> * pNode, BNode <T> * pAdd)
{
    if (pAdd)
        pAdd->pParent = pNode;
    pNode->pRight = pAdd;
}

/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft (BNode <T> * pNode, const T & t)
{
    BNode <T> * pAdd = new BNode <T> (t);
    pAdd->pParent = pNode;
    pNode->pLeft = pAdd;
}

template <class T>
inline void addLeft(BNode <T>* pNode, T && t)
{
    BNode <T>* pAdd = new BNode <T>(t);
    pAdd->pParent = pNode;
    pNode->pLeft = pAdd;
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
void addRight (BNode <T> * pNode, const T & t)
{
    BNode <T>* pAdd = new BNode <T>(t);
    pAdd->pParent = pNode;
    pNode->pRight = pAdd;
}

template <class T>
void addRight(BNode <T>* pNode, T && t)
{
    BNode <T>* pAdd = new BNode <T>(t);
    pAdd->pParent = pNode;
    pNode->pRight = pAdd;
}

/*****************************************************
 * DELETE BINARY TREE
 * Delete all the nodes below pThis including pThis
 * using postfix traverse: LRV
 ****************************************************/
template <class T>
void clear(BNode <T> * & pThis)
{
    if (!pThis)
        return;
    clear(pThis->pLeft);
    clear(pThis->pRight);

    delete pThis;
    pThis = nullptr;
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(BNode <T>*& pLHS, BNode <T>*& pRHS)
{
    BNode <T> * tempNode = pRHS; 
    pRHS = pLHS;
    pLHS = tempNode;

}

/**********************************************
 * COPY BINARY TREE
 * Copy pSrc->pRight to pDest->pRight and
 * pSrc->pLeft onto pDest->pLeft
 *********************************************/
template <class T>
BNode <T> * copy(const BNode <T> * pSrc)
{
    if (!pSrc)
        return nullptr;
    BNode <T>* destination = new BNode <T> (pSrc->data);

    destination->pLeft = copy(pSrc->pLeft);
    if (destination->pLeft)
        destination->pLeft->pParent = destination;
    destination->pRight = copy(pSrc->pRight);
    if (destination->pRight)
        destination->pRight->pParent = destination;
   
    return destination;
}

/**********************************************
 * assign
 * copy the values from pSrc onto pDest preserving
 * as many of the nodes as possible.
 *********************************************/
template <class T>
void assign(BNode <T> * & pDest, const BNode <T>* pSrc)
{
   
    if (!pSrc) {
        clear(pDest);
        return;
    }
    if (!pDest && pSrc) {
        pDest = new BNode <T> (pSrc->data);
        
        assign(pDest->pRight, pSrc->pRight);
        assign(pDest->pLeft, pSrc->pLeft);
        if (pDest->pRight)
            pDest->pRight->pParent = pDest;
        if (pDest->pLeft)
            pDest->pLeft->pParent = pDest;
    }
    if (pDest && pSrc) {
        
        pDest->data = pSrc->data;
        
        assign(pDest->pRight, pSrc->pRight);
        assign(pDest->pLeft, pSrc->pLeft);
        if (pDest->pRight)
            pDest->pRight->pParent = pDest;
        if (pDest->pLeft)
            pDest->pLeft->pParent = pDest;
    }
}