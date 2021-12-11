/***********************************************************************
 * Header:
 *    DEQUE
 * Summary:
 *    Our custom implementation of a deque
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        deque           : A class that represents a binary search tree
 *        deque::iterator : An iterator through BST
 * Author
 *    David Sloan
 *       Hours: 2 hours
 *       Challenges: I didn't get a lot of work done before my othe team
 *       members finished the project. I had the hardest time trying to
 *       make sure I get enough time dedicated to the project before
 *       Saturday.
 *    Stephen Harrison
 *       Hours: 4 hours
 *       Challenges: interesting wrapping my head around the iterator on 
 *       this one
 *    Everett Tsosie
 *       Hours: 7 hours
 *       Challenges: The function that I had struggle with most was working
 *       with the assignment operator for a deque. There was an error when 
 *       trying to call a member function of a constant object. Instead of 
 *       following the pseudocode I ended up using other member variables 
 *       and created my own loop to solve the issue.
 ************************************************************************/

#pragma once

// Debug stuff
#include <cassert>


namespace custom
{

/******************************************************
 * DEQUE
 *   0   1   2   3   4
 * +---+---+---+---+---+
 * |   | A | B | C |   |
 * +---+---+---+---+---+
 * iaFront = 1
 * numElements = 3
 * numCapacity = 5
 *****************************************************/
template <class T>
class deque
{
public:

   // 
   // Construct
   //
    deque() : data(NULL), numElements(NULL),
        numCapacity(NULL), iaFront(NULL)
    {
    }
   deque(int newCapacity);
   deque(const deque <T> & rhs);
   ~deque()
   { 
   }

   //
   // Assign
   //
   deque<T> & operator = (const deque <T> & rhs);

   //
   // Iterator
   //
   class iterator;
   iterator begin()
   {
      return iterator(this, 0);
   }
   iterator end()
   {
      return iterator(this, numElements);
   }

   //
   // Access
   //
   T& front();
   T& back();
   const T & front() const;
   const T & back()  const;
   const T & operator[](size_t index) const;
   T& operator[](size_t index);

   // 
   // Insert
   //
   void push_front(const T& t);
   void push_back(const T& t);

   //
   // Remove
   //
   void clear()
   { 
       if (numCapacity == 0)
           return;
       for (int id = 0; id < numElements - 1; id++)
           data[iaFromID(id)] = NULL;
       numElements = 0;
   }
   void pop_front();
   void pop_back();

   // 
   // Status
   //
   size_t size() const 
   { 
      return numElements; 
   }
   bool empty() const 
   { 
      return size() == 0; 
   }

   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   
   // fetch array index from the deque index
   int iaFromID(int id) const
   {
       int temp = iaFront + id;
       if (temp < 0)
           while (temp < 0)
               temp += numCapacity;
       int iaReturn = temp % numCapacity;
       return iaReturn;
   }
   void resize(int newCapacity = 0);

   // member variables
   T * data;           // dynamically allocated data for the deque
   size_t numCapacity; // the size of the data array
   size_t numElements; // number of elements in the deque
   int iaFront;        // the index of the first item in the array
};



/**********************************************************
 * DEQUE ITERATOR
 * Forward and reverse iterator through a deque, just call
 *********************************************************/
template <typename T>
class deque <T> ::iterator
{
public:
   //
   // Construct
   //
   iterator() : id(NULL), pDeque(NULL) {   }
   iterator(custom::deque<T> *pDeque, int id)
   {
       this->id = id;
       this->pDeque = pDeque;
   }
   iterator(const iterator& rhs)
   {
       this->id = rhs.id;
       this->pDeque = rhs.pDeque;
   }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
       this->id = rhs.id;
       this->pDeque = rhs.pDeque;
      return *this;
   }

   //
   // Compare
   //
   bool operator == (const iterator& rhs) const { return this == rhs; }
   bool operator != (const iterator& rhs) const { return this != rhs; }

   // 
   // Access
   //
   const T & operator * () const
   {
      return pDeque->data[id];
   }
   T& operator * () 
   {
      return pDeque->data[id];
   }

   // 
   // Arithmetic
   //
   int operator - (iterator it) const
   {
      return 99;
   }
   iterator& operator += (int offset)
   {
       id += offset;
      return *this;
   }
   iterator& operator ++ ()
   {
       ++id;
      return *this;
   }
   iterator operator ++ (int postfix)
   {
       auto temp = id;
       ++id;
      return temp;
   }
   iterator& operator -- ()
   {
       --id;
       return *this;
   }
   iterator  operator -- (int postfix)
   {
       auto temp = id;
       --id;
       return temp;
   }

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   // Member variables
   int id;             // deque index
   deque<T> *pDeque;
};


/****************************************************
 * DEQUE : CONSTRUCTOR - non-default
 ***************************************************/
template <class T>
deque <T> :: deque(int newCapacity)
{
}

/****************************************************
 * DEQUE : CONSTRUCTOR - copy
 ***************************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs) : data(rhs.data)
{
    numElements = rhs.numElements;
    numCapacity = rhs.numCapacity;
    iaFront = rhs.iaFront;
}


/****************************************************
 * DEQUE : ASSIGNMENT OPERATOR
 ***************************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs)
{
    clear();
    this->iaFront = 0;

    if (numCapacity < rhs.numElements)
        resize(rhs.numElements);

    for (int id = 0; id < rhs.numElements; id++)
        data[id] = rhs.data[rhs.iaFromID(id)];

    numElements = rhs.numElements;

   return *this;
}


/**************************************************
 * DEQUE :: FRONT
 * Fetch the item that is at the beginning of the deque
 *************************************************/
template <class T>
const T & deque <T> :: front() const 
{
    assert(numElements != 0);
    return data[iaFromID(iaFront)];
}
template <class T>
T& deque <T> ::front()
{
    assert(numElements != 0);
    return data[iaFromID(iaFront)];
}

/**************************************************
 * DEQUE :: BACK
 * Fetch the item that is at the end of the deque
 *************************************************/
template <class T>
const T & deque <T> :: back() const 
{
    assert(numElements != 0);
    return data[iaFromID(numElements - 1)];
}
template <class T>
T& deque <T> ::back()
{
    assert(numElements != 0);
    return data[iaFromID(numElements - 1)];
}

/**************************************************
 * DEQUE :: SUBSCRIPT
 * Fetch the item in the deque
 *************************************************/
template <class T>
const T& deque <T> ::operator[](size_t index) const
{
    assert(0 <= index < numElements);
    return data[iaFromID(index)];
}
template <class T>
T& deque <T> ::operator[](size_t index)
{
    assert(0 <= index < numElements);
    return data[iaFromID(index)];
}

/*****************************************************
 * DEQUE : POP_BACK
 *****************************************************/
template <class T>
void deque <T> ::pop_back()
{
    numElements--;
    data[iaFromID(numElements)] = NULL;
}

/*****************************************************
 * DEQUE : POP_FRONT
 *****************************************************/
template <class T>
void deque <T> :: pop_front()
{
    numElements--;
    data[iaFromID(0)] = NULL;
    iaFront++;
    if (iaFront == numCapacity)
        iaFront = 0;
}

/******************************************************
 * DEQUE : PUSH_BACK
 ******************************************************/
template <class T>
void deque <T> :: push_back(const T & t) 
{
    if (numElements == numCapacity)
        if (numCapacity == 0)
            resize(1);
        else
            resize(numCapacity * 2);

    data[iaFromID(numElements++)] = t;
}

/******************************************************
 * DEQUE : PUSH_FRONT
 ******************************************************/
template <class T>
void deque <T> :: push_front(const T & t) 
{
    if (numElements == numCapacity)
        if (numCapacity == 0)
            resize(1);
        else
            resize(numCapacity * 2);

    int temp = iaFront--;
    if (temp < 0)
        temp = numCapacity - 1;
    data[iaFromID(temp)] = t;
    numElements++;
}

/****************************************************
 * DEQUE :: GROW
 * If the deque is currently empty, allocate to size 2.
 * Otherwise, double the size
 ***************************************************/
template <class T>
void deque <T> :: resize(int newCapacity) 
{
    assert(newCapacity > 0 && newCapacity > numElements);
    T* dataNew = new T[newCapacity];

    for (int id = 0; id < numElements; id++)
        dataNew[id] = data[id];

    numCapacity = newCapacity;
    iaFront = 0;

    delete[] data;
    data = dataNew;
}

} // namespace custom
