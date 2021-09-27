/***********************************************************************
 * Header:
 *    BINARY NODE
 * Summary:
 *    One node in a binary tree (and the functions to support them).
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 *
 *
 *    This will contain the class definition of:
 *        BNode         : A class representing a BNode
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    <your names here> 
 ************************************************************************/

#pragma once

#include <iostream>  // for OFSTREAM
#include <cassert>

/*****************************************************************
 * BNODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
class BNode
{
public:
   // 
   // Construct
   //
   BNode()             
   {
      pLeft = pRight = this;
      data = 88;
   }
   BNode(const int &  t) 
   {
      pLeft = pRight = this;
      data = 88;
   }
   BNode(int && t) 
   {
      pLeft = pRight = this;
      data = 88;
   }

   // 
   // Data
   //
   BNode * pLeft;
   BNode * pRight;
   BNode * pParent;

   // the data of unknown type: cannot validate so is public
   int data;
};

/*******************************************************************
 * SIZE BTREE
 * Return the size of a b-tree under the current node
 *******************************************************************/
inline size_t size(const BNode * p)
{
   return 99;
}


/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
inline void addLeft(BNode * pNode, BNode * pAdd)
{

}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
inline void addRight (BNode * pNode, BNode * pAdd)
{

}

/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
inline void addLeft (BNode  * pNode, const int & t)
{

}

inline void addLeft(BNode * pNode, int && t)
{

}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
void addRight (BNode  * pNode, const int & t)
{

}

void addRight(BNode * pNode, int && t)
{

}

/*****************************************************
 * DELETE BINARY TREE
 * Delete all the nodes below pThis including pThis
 * using postfix traverse: LRV
 ****************************************************/
void clear(BNode  * & pThis)
{

}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
inline void swap(BNode *& pLHS, BNode *& pRHS)
{

}

/**********************************************
 * COPY BINARY TREE
 * Copy pSrc->pRight to pDest->pRight and
 * pSrc->pLeft onto pDest->pLeft
 *********************************************/
BNode  * copy(const BNode  * pSrc)
{
   return new BNode;
}

/**********************************************
 * assign
 * copy the values from pSrc onto pDest preserving
 * as many of the nodes as possible.
 *********************************************/
void assign(BNode  * & pDest, const BNode * pSrc)
{

}
