/***********************************************************************
 * Header:
 *    BST
 * Summary:
 *    Our custom implementation of a BST for set and for map
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        BST                 : A class that represents a binary search tree
 *        BST::iterator       : An iterator through BST
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#ifdef DEBUG
#define debug(x) x
#else // !DEBUG
#define debug(x)
#endif // !DEBUG

#include <cassert>
#include <utility>
#include <memory>     // for std::allocator
#include <functional> // for std::less
#include <utility>    // for std::pair

namespace custom
{

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <typename T>
class BST
{
public:
   //
   // Construct
   //
    BST();
    BST(const BST& rhs);
    BST(BST&& rhs);
    BST(const std::initializer_list<T>& il);
   ~BST();

   //
   // Assign
   //
   BST & operator = (const BST &  rhs);
   BST & operator = (      BST && rhs);
   BST & operator = (const std::initializer_list<T>& il);
   void swap(BST & rhs);

   //
   // Iterator
   //
   class iterator;
   iterator   begin() const noexcept;
   iterator   end()   const noexcept { return iterator(nullptr); }

   //
   // Access
   //
   iterator find(const T& t);

   // 
   // Insert
   //
   std::pair<iterator, bool> insert(const T&  t, bool keepUnique = false);
   std::pair<iterator, bool> insert(      T&& t, bool keepUnique = false);

   //
   // Remove
   // 
   iterator erase(iterator& it);
   void   clear() noexcept;

   // 
   // Status
   //
   bool   empty() const noexcept { return true; }
   size_t size()  const noexcept { return 99;   }
   

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   class BNode;
   BNode * root;              // root node of the binary search tree
   size_t numElements;        // number of elements currently in the tree
};


/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree. Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <typename T>
class BST <T> :: BNode
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
   // Insert
   //
   void addLeft (BNode * pNode);
   void addRight(BNode * pNode);
   void addLeft (const T &  t);
   void addRight(const T &  t);
   void addLeft(       T && t);
   void addRight(      T && t);

   // 
   // Status
   //
   bool isRightChild(BNode * pNode) const { return true; }
   bool isLeftChild( BNode * pNode) const { return true; }

   //
   // Data
   //
   T data;                  // Actual data stored in the BNode
   BNode* pLeft;          // Left child - smaller
   BNode* pRight;         // Right child - larger
   BNode* pParent;        // Parent
   bool isRed;              // Red-black balancing stuff
};

/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <typename T>
class BST <T> :: iterator
{
public:
   // constructors and assignment
   iterator(BNode * p = nullptr) {
      pNode = p;
   }

   iterator(const iterator & rhs) { 
      pNode = rhs.pNode;
   }

   iterator & operator = (const iterator & rhs)
   {
      pNode = rhs.pNode;
      return *this;
   }

   // compare
   bool operator == (const iterator & rhs) const
   {
      return rhs.pNode == pNode;
   }
   bool operator != (const iterator & rhs) const
   {
      return rhs.pNode != pNode;
   }

   // de-reference. Cannot change because it will invalidate the BST
   const T & operator * () const 
   {
      return pNode->data;
   }

   // increment and decrement
   iterator & operator ++ ();
   iterator   operator ++ (int postfix)
   {
      iterator it = *this;
      ++(*this);
      return it;
   }
   iterator & operator -- ();
   iterator   operator -- (int postfix)
   {
      iterator it = *this;
      --(*this);
      return it;
   }

   // must give friend status to remove so it can call getNode() from it
   friend BST <T> :: iterator BST <T> :: erase(iterator & it);

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   
    // the node
    BNode * pNode;
};

/*********************************************
 *********************************************
 *********************************************
 ******************** BST ********************
 *********************************************
 *********************************************
 *********************************************/



 /*********************************************
  * BST :: DEFAULT CONSTRUCTOR
  ********************************************/
template <typename T>
BST <T> ::BST()
{
   numElements = 0;
   root = nullptr;
}

/*********************************************
 * BST :: COPY CONSTRUCTOR
 * Copy one tree to another
 ********************************************/
template <typename T>
BST <T> :: BST ( const BST<T>& rhs) 
{
   numElements = 0;
   root = nullptr;

   *this = rhs;
}

/*********************************************
 * BST :: MOVE CONSTRUCTOR
 * Move one tree to another
 ********************************************/
template <typename T>
BST <T> :: BST(BST <T> && rhs) 
{
    root = rhs.root;
    numElements = rhs.numElements;

    rhs.root = nullptr;
    rhs.numElements = 0;
}

/*********************************************
 * BST :: DESTRUCTOR
 ********************************************/
template <typename T>
BST <T> :: ~BST()
{

}

/*********************************************
 * BST :: ASSIGNMENT OPERATOR
 * Copy one tree to another
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (const BST <T> & rhs)
{
   //  assign(root, rhs.root);
   //  numElements = rhs.numElements;
   return *this;
}

/*********************************************
 * BST :: ASSIGNMENT OPERATOR with INITIALIZATION LIST
 * Copy nodes onto a BTree
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (const std::initializer_list<T>& il)
{
    clear();
    for (int i = 0; i < il; i++)
        insert(i);
    return *this;

}

/*********************************************
 * BST :: ASSIGN-MOVE OPERATOR
 * Move one tree to another
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (BST <T> && rhs)
{
    clear();
    swap(rhs);

   return *this;
}

/*********************************************
 * BST :: SWAP
 * Swap two trees
 ********************************************/
template <typename T>
void BST <T> :: swap (BST <T>& rhs)
{
    BNode* tempRoot = rhs.root;
    rhs.root = root;
    root = tempRoot;

    size_t tempElements = rhs.numElements;
    rhs.numElements = numElements;
    numElements = tempElements;
}

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <typename T>
std::pair<typename BST <T> :: iterator, bool> BST <T> :: insert(const T & t, bool keepUnique)
{
   std::pair<iterator, bool> pairReturn(end(), false);
   return pairReturn;
}

template <typename T>
std::pair<typename BST <T> ::iterator, bool> BST <T> ::insert(T && t, bool keepUnique)
{
   std::pair<iterator, bool> pairReturn(end(), false);
   return pairReturn;
}

/*************************************************
 * BST :: ERASE
 * Remove a given node as specified by the iterator
 ************************************************/
template <typename T>
typename BST <T> :: iterator BST <T> :: erase(iterator & it) {
   //TODO: Just the Pseudocode comeback and make sure it works.
   // //Case 1 No Children
   // if(it.pRight == NULL && it.pLeft == NULL) { // if(!it.pRight && !it.pLeft) {
   //    if(it.pParent != NULL && it.pParent.pRight == it) { // if(it.pParent && it.pParent.pRight == it)
   //       it.pParent.pRight = NULL;
   //    }
      
   //    if(it.pParent != NULL && it.pParent.pLeft == it) { // if(it.pParent && it.pParent.pLeft == it)
   //       it.pParent.pLeft = NULL;
   //    }

   //    delete it;
   // }

   // //Case 2 One Child
   // if(it.pRight == NULL && it.pLeft != NULL) { // if(!it.pRight && it.pLeft) {
   //    it.pLeft.pParent = it.pParent;
   //    if(it.pParent != NULL && it.pParent.pRight == it) { // if(it.pParent && it.pParent.pRight == it)
   //       it.pParent.pRight = it.pLeft;
   //    }

   //    if(it.pParent != NULL && it.pParent.pLeft == it) { // if(it.pParent && it.pParent.pLeft == it)
   //       it.pParent.pLeft = it.pLeft;
   //    }

   //    delete it;
   // }

   // if(it.pLeft == NULL && it.pRight != NULL) { // if(!it.pLeft && it.pRight)
   //    it.pRight.pParent = it.pParent;
   //    if(it.pParent != NULL && it.pParent.pRight == it) { // if(it.pParent && it.pParent.pRight == it)
   //       it.pParent.pRight = it.pRight;
   //    }

   //    if(it.pParent != NULL && it.pParent.pLeft == it)  { // if(it.pParent && it.pParent.pLeft == it)
   //       it.pParent.pLeft = it.pRight;
   //    }

   //    delete it;
   // }

   // //Case 3 Two Children
   // //TODO

   return end();
}

/*****************************************************
 * BST :: CLEAR
 * Removes all the BNodes from a tree
 ****************************************************/
template <typename T>
void BST <T> ::clear() noexcept
{

}

/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <typename T>
typename BST <T> :: iterator custom :: BST <T> :: begin() const noexcept
{
    if (empty())
        return end();
    BNode * p = root;
    while (p->pLeft) {
        p = p->pLeft;
    }
    return iterator(p);
}


/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <typename T>
typename BST <T> :: iterator BST<T> :: find(const T & t)
{
    BNode * p = root;

    while(p) {
        if (p->data == t) {
            return iterator(p);
        }
        else if(t < p->data) {
            p = p->pLeft;
        }
        else
            p = p->pRight;
    }
   return end();
}

/******************************************************
 ******************************************************
 ******************************************************
 *********************** B NODE ***********************
 ******************************************************
 ******************************************************
 ******************************************************/

 
/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <typename T>
void BST <T> :: BNode :: addLeft (BNode * pNode)
{

}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <typename T>
void BST <T> :: BNode :: addRight (BNode * pNode)
{

}

/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <typename T>
void BST<T> :: BNode :: addLeft (const T & t)
{

}

/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <typename T>
void BST<T> ::BNode::addLeft(T && t)
{

}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <typename T>
void BST <T> :: BNode :: addRight (const T & t)
{

}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <typename T>
void BST <T> ::BNode::addRight(T && t)
{

}



/*************************************************
 *************************************************
 *************************************************
 ****************** ITERATOR *********************
 *************************************************
 *************************************************
 *************************************************/     

/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <typename T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
{
   return *this;  
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <typename T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
{
   return *this;

}


} // namespace custom