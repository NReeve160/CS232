/***********************************************************************
 * Header:
 *    VECTOR
 * Summary:
 *    Our custom implementation of std::vector
 *
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        vector                 : A class that represents a Vector
 *        vector::iterator       : An interator through Vector
 * Author
 *    Group G
 ************************************************************************/

#pragma once

#include <cassert>  // because I am paranoid
#include <new>      // std::bad_alloc
#include <memory>   // for std::allocator


namespace custom
{

/*****************************************
 * VECTOR
 * Just like the std :: vector <T> class
 ****************************************/
template <typename T>
class vector
{
public:
   
   // 
   // Construct
   //

   vector();
   vector(size_t numElements                );
   vector(size_t numElements, const T & t   );
   vector(const std::initializer_list<T>& l );
   vector(const vector &  rhs);
   vector(      vector && rhs);
   ~vector();

   //
   // Assign
   //

   void swap(vector& rhs)
   {
       T* tempData = rhs.data;
       rhs.data = data;
       data = tempData;

       T tempElements = rhs.numElements;
       rhs.numElements = numElements;
       numElements = tempElements;

       T tempCapacity = rhs.numCapacity;
       rhs.numCapacity = numCapacity;
       numCapacity = tempCapacity;
   }
   vector & operator = (const vector & rhs);
   vector& operator = (vector&& rhs);

   //
   // Iterator
   //

   class iterator;
   iterator       begin() { return iterator(&data[0]); }
   iterator       end() { return iterator(&data[numElements]); }

   //
   // Access
   //

         T& operator [] (size_t index);
   const T& operator [] (size_t index) const;
         T& front();
   const T& front() const;
         T& back();
   const T& back() const;

   //
   // Insert
   //

   void push_back(const T& t);
   void push_back(T&& t);
   void reserve(size_t newCapacity);
   void resize(size_t newElements);
   void resize(size_t newElements, const T& t);

   //
   // Remove
   //

   void clear()
   {
       for (int i = 0; i < numElements; ++i)
           data[i] = NULL;
       numElements = 0;
   }
   void pop_back()
   {
       if (numElements != 0) 
       {
           data[size() - 1] = NULL;
           numElements--;
       }
   }
   void shrink_to_fit();

   //
   // Status
   //

   size_t  size()          const { return numElements;}
   size_t  capacity()      const { return numCapacity;}
   bool empty()            const { return numElements == 0;}
   
   // adjust the size of the buffer
   
   // vector-specific interfaces
   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   
   T *  data;                 // user data, a dynamically-allocated array
   size_t  numCapacity;       // the capacity of the array
   size_t  numElements;       // the number of items currently used
};

/*****************************************
 * VECTOR :: DEFAULT constructors
 * Default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector()
{
   data = nullptr;
   numCapacity = 0;
   numElements = 0;
}

/*****************************************
 * VECTOR :: NON-DEFAULT constructors
 * non-default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector(size_t num, const T & t) 
{
   data = new T[num];
   numCapacity = num;
   numElements = num;
   for (int i = 0; i < num; ++i) {
       data[i] = t;
   }
}

/*****************************************
 * VECTOR :: INITIALIZATION LIST constructors
 * Create a vector with an initialization list.
 ****************************************/
template <typename T>
vector <T> :: vector(const std::initializer_list<T> & l) 
{
   data = new T[l.size()];
   numCapacity = l.size();
   numElements = l.size();
   int n = 0;
   for (int i : l) {
       data[n] = i;
       n++;
   }
}
/*****************************************
 * VECTOR :: NON-DEFAULT constructors
 * non-default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector(size_t num) 
{
    (num == 0 ? data = nullptr : data = new T[num]);
   numCapacity = num;
   numElements = num;
   for (int i = 0; i < num; ++i) {
       data[i] = 0;
   }
}

/*****************************************
 * VECTOR :: COPY CONSTRUCTOR
 * Allocate the space for numElements and
 * call the copy constructor on each element
 ****************************************/
template <typename T>
vector <T> :: vector (const vector & rhs) 
{
    (rhs.data != nullptr ? data = new T[rhs.size()] : data = nullptr);
   numCapacity = rhs.numElements;
   numElements = rhs.numElements;
   for (int i = 0; i < rhs.size(); ++i) {
       data[i] = rhs.data[i];
   }
}

/*****************************************
 * VECTOR :: MOVE CONSTRUCTOR
 * Steal the values from the RHS and set it to zero.
 ****************************************/
template <typename T>
vector <T> :: vector (vector && rhs)
{
   data = rhs.data;
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;
   rhs.data = nullptr;
   rhs.numCapacity = 0;
   rhs.numElements = 0;
}

/*****************************************
 * VECTOR :: DESTRUCTOR
 * Call the destructor for each element from 0..numElements
 * and then free the memory
 ****************************************/
template <typename T>
vector <T> :: ~vector()
{
    for (int i = 0; i < numElements; ++i) {
        data[i] = NULL;
    }
    delete[] data;
}

/***************************************
 * VECTOR :: RESIZE
 * This method will adjust the size to newElements.
 * This will either grow or shrink newElements.
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: resize(size_t newElements)
{
    if (newElements < numElements) {
        for (int i = newElements; i < numElements; ++i) {
            data[i] = NULL;
        }
    }
    else if (newElements > numElements) {
        if (newElements > numCapacity)
            reserve(newElements);
        for (int i = numElements; i < newElements; ++i) {
            data[i] = 0;
        }
    }
    numElements = newElements;
}

template <typename T>
void vector <T> :: resize(size_t newElements, const T & t)
{
    if (newElements < numElements) {
        for (int i = newElements; i < numElements; ++i) {
            data[i] = NULL;
        }
    }
    else if (newElements > numElements) {
        if (newElements > numCapacity)
            reserve(newElements);
        for (int i = numElements; i < newElements; ++i) {
            data[i] = t;
        }
    }
    numElements = newElements;
}

/***************************************
 * VECTOR :: RESERVE
 * This method will grow the current buffer
 * to newCapacity.  It will also copy all
 * the data from the old buffer into the new
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: reserve(size_t newCapacity)
{
    if (newCapacity <= numCapacity)
        return;
    T* dataNew = new T[newCapacity];
    for (int i = 0; i < numElements; ++i)
        dataNew[i] = data[i];
    delete[] data;
    data = dataNew;
    numCapacity = newCapacity;
}

/***************************************
 * VECTOR :: SHRINK TO FIT
 * Get rid of any extra capacity
 *     INPUT  :
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: shrink_to_fit()
{
    if (numElements == numCapacity)
        return;

    T* dataNew = new T[numElements];
    for (int i = 0; i < numElements; ++i)
        dataNew[i] = data[i];

    delete[] data;
    data = dataNew;
    numCapacity = numElements;

    if (numElements == 0)
        data = nullptr;
}



/*****************************************
 * VECTOR :: SUBSCRIPT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: operator [] (size_t index)
{
   return data[index];
   
}

/******************************************
 * VECTOR :: SUBSCRIPT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: operator [] (size_t index) const
{
   return data[index];
}

/*****************************************
 * VECTOR :: FRONT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: front ()
{
   
   return data[0];
}

/******************************************
 * VECTOR :: FRONT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: front () const
{
   return data[0];
}

/*****************************************
 * VECTOR :: FRONT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: back()
{
   return data[numElements - 1];
}

/******************************************
 * VECTOR :: FRONT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: back() const
{
   return data[numElements - 1];
}

/***************************************
 * VECTOR :: PUSH BACK
 * This method will add the element 't' to the
 * end of the current buffer.  It will also grow
 * the buffer as needed to accomodate the new element
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this
 **************************************/
template <typename T>
void vector <T> ::push_back(const T& t)
{
    if (capacity() == 0)
        reserve(1);
    if (size() == capacity())
        reserve(capacity() * 2);
    data[numElements++] = t;
}

template <typename T>
void vector <T> ::push_back(T && t)
{
    if (capacity() == 0)
        reserve(1);
    if (size() == capacity())
        reserve(capacity() * 2);
    data[numElements++] = t;
}

/***************************************
 * VECTOR :: ASSIGNMENT
 * This operator will copy the contents of the
 * rhs onto *this, growing the buffer as needed
 *     INPUT  : rhs the vector to copy from
 *     OUTPUT : *this
 **************************************/
template <typename T>
vector <T> & vector <T> :: operator = (const vector & rhs)
{
    if (numCapacity < rhs.size())
        reserve(rhs.size());
    for (int i = 0; i < numCapacity; ++i)
        data[i] = rhs.data[i];
    if (numCapacity > rhs.size())
        for (int i = numElements; i < numCapacity; ++i)
            data[i] = NULL;
    numElements = rhs.numElements;

   return *this;
}
template <typename T>
vector <T>& vector <T> :: operator = (vector&& rhs)
{
    if (numCapacity < rhs.size())
        reserve(rhs.size());
    for (int i = 0; i < numCapacity; ++i)
        data[i] = rhs.data[i];
    if (numCapacity > rhs.size())
        for (int i = numElements; i < rhs.size(); ++i)
            data[i] = NULL;
    numElements = rhs.numElements;
    rhs.data = nullptr;
    rhs.numElements = 0;

   return *this;
}

/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector.  You only need to
 * support the following:
 *   1. Constructors (default and copy)
 *   2. Not equals operator
 *   3. Increment (prefix and postfix)
 *   4. Dereference
 * This particular iterator is a bi-directional meaning
 * that ++ and -- both work.  Not all iterators are that way.
 *************************************************/
template <typename T>
class vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      { this->p = nullptr; }
   iterator(T * p)        { this->p = p; }
   iterator(const iterator & rhs) { this->p = rhs.p; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return p;
   }
   
   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return p != rhs.p; }
   bool operator == (const iterator & rhs) const { return p == rhs.p; }
   
   // dereference operator
   T & operator * ()
   {
      return *p;
   }
   
   // prefix increment
   iterator & operator ++ ()
   {
       p++;
       return *this;
   }
   
   // postfix increment
   iterator operator ++ (int postfix)
   {
       iterator i = p;
       p++;
       return i;
   }

   // prefix decrement
   iterator & operator -- ()
   {
       p--;
       return *this;
   }
   
   // postfix decrement
   iterator operator -- (int postfix)
   {
       iterator i = p;
       p--;
       return i;
   }
   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   T * p;
};


} // namespace custom

