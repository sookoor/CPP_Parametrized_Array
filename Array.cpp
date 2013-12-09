#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <sys/types.h>
#include "Array.h"
#include "scoped_array.h"

#if !defined (__INLINE__)
#define INLINE 
#include "Array.inl"
#endif /* __INLINE__ */

#include <algorithm>
#include <strstream>

//
//Method name: Array
//Purpose: Dynamically create an uninitialized array.
//Parameters: <size> is of type size_t. 
//            <size> is the size of the array to be created.
//            <size> is passed by value.
//Return value: None
//

template <class T> 
Array<T>::Array (size_t size) throw (std::bad_alloc)
  : max_size_(size),
    cur_size_(size),
    array_(new T[this->cur_size_]) 
{
}

//
//Method name: Array
//Purpose: Dynamically initialize the entire array to the <default_value>.
//Parameters: <size> is of type size_t and default_value is of type T.
//            <size> is the size of the array to be created.
//            <default_value> is the value to be used to initialize the array.
//            <size> is passed by value. <default_value> is passed by reference.//Return value: None
//

template <class T> 
Array<T>::Array (size_t size, 
		 const T &default_value) throw (std::bad_alloc)
    : max_size_(size),
      cur_size_(size),
      array_(0)
{
    scoped_array<T> temp_array (new T[size]);
    
    // Initialize all array locations to the <default_value>.
    std::fill (temp_array.get (), temp_array.get () + size, default_value);

    temp_array.swap (this->array_);
}

//
//Method name: Array
//Purpose: The copy constructor (performs initialization).
//Parameters: <s> is of type Array<T>.
//            <s> is the parameter whos contents are to be copied.
//            <s> is passed by reference.
//Return value: None
//

template <class T> 
Array<T>::Array (const Array<T> &s) throw (std::bad_alloc)
    : max_size_(s.cur_size_),
      cur_size_(s.cur_size_),
      array_(0)
{
    scoped_array<T> temp_array (new T[s.cur_size_]);
    
    // Copy each array element from s's array to the newly created array.
    std::copy (s.array_, s.array_ + this->cur_size_, temp_array.get ());

    temp_array.swap(this->array_);
}

//
//Method name: resize
//Purpose: Change the size of the array to be at least <new_size> elements.
//Parameters: <new_size> is of type size_t.
//            <new_size> is the size to which the array needs to be resized.
//            <new_size> is passed by value.
//Return value: void
//

template <class T> void
Array<T>::resize (size_t new_size) throw (std::bad_alloc)
{
    // If <new_size> is less than the physical size of the array, just change
    // the logical size to <new_size>.
    if (new_size <= this->max_size_)
        this->cur_size_ = new_size;
    // If <new_size> is greater than the physical size of the array, a new array    // should be allocated.
    else
        {
            // Check if the new_size is greater than twice the physical size.
            // If it is create the new array to be of size <new_size>, otherwise            // create the array to be twice its current physical size. This will            // reduce the number of times the array has to be reallocated if it             // continues to grow.
            size_t physical_size = std::max(new_size, this->max_size_*2);

            scoped_array<T> temp_array (new T[physical_size]); // Temporary array.
                
            // Copy all array elements to the temporary
            // array before deleting it.
            std::copy(this->array_, this->array_ + this->cur_size_, temp_array.get ());
            temp_array.swap (this->array_);
            this->max_size_ = physical_size;
            this->cur_size_ = new_size;
        } 
}

//
//Method name: operator=
//Purpose: Assignment operator (performs assignment).
//Parameters: <s> is of type Array<T>.
//            <s> is the parameter whos contents are to be copied.
//            <s> is passed by reference.
//Return value: void
//

template <class T> void 
Array<T>::operator= (const Array<T> &s) throw (std::bad_alloc)
{
    if (this != &s) // Check for self-allocation.
        {
            scoped_array<T> temp_array (new T[s.cur_size_]);
            std::copy(s.array_, s.array_ + s.cur_size_, temp_array.get ());
            temp_array.swap (this->array_);
            this->max_size_ = s.cur_size_;
            this->cur_size_ = s.cur_size_;
            
        }
}

//
//Method name: ~Array
//Purpose: Clean up the array (e.g., delete dynamically allocated memory).
//Parameters: void
//Return value: none
//

template <class T> 
Array<T>::~Array (void)
{
    delete [] array_;
}

// = Set/get methods.

//
//Method name: set
//Purpose: Set an item in the array at location index.
//Parameters: <new_item> is of type T and <index> is of type size_t.
//            <new_item> is the item to be set in the array.
//            <index> is the location where the item should be set.
//            <new_item> is passed by reference and <index> is passed by value.
//Return value: void
//

template <class T> void
Array<T>::set (const T &new_item, size_t index) throw (std::bad_alloc)
{
    // If index is out of range, resize the array.
    if (!this->in_range (index))
        this->resize (index + 1);

    (*this)[index] = new_item;
}

//
//Method name: get
//Purpose: Get an item in the array at location index.
//Parameters: <item> is of type T and <index> is of type size_t.
//            The item at location <index> is assigned to <item>.
//            <item> is passed by reference and <index> is passed by value.
//Return value: void
//

template <class T> void
Array<T>::get (T &item, size_t index) const throw (std::out_of_range)
{
    if (in_range(index))
        item = array_[index];
    else
        throw std::out_of_range("index out of range");
}

//
//Method name: operator==
//Purpose: Compare this array with <s> for equality.
//Parameters: <s> is of type Array<T>.
//            <s> is the item with which the array must be compared.
//            <s> is passed by reference.
//Return value: bool. true if the size()'s of the two arrays are equal and all
//              the elements from 0 .. size() are equal, else false.
//

template <class T> bool
Array<T>::operator== (const Array<T> &s) const
{
    // Check if size()'s of the two arrays are equal.
    if (size () != s.size ())
	// If size()'s are not equal return false.
	return false;
    // If size()'s are equal compare all elements from 0 to size().
    else {
	for (size_t i = 0; i < s.size (); i++)
	    {
		if (array_[i] != s.array_[i])
		    return false;
	    }
	return true;
    }
}

//
//Method name: operator!=
//Purpose: Compare this array with <s> for inequality.
//Parameters: <s> is of type Array<T>.
//            <s> is the item with which the array must be compared.
//            <s> is passed by reference.
//Return value: bool. false if the size()'s of the two arrays are equal and all
//              the elements from 0 .. size() are equal, else true.
//

template <class T> bool
Array<T>::operator!= (const Array<T> &s) const
{
    return !(*this == s);
}

//
//Method name: Array_Iterator
//Purpose: Construct an Array_Iterator at position pos.
//Parameters: <array> is of type Array<T> and <pos> is of type size_t.
//            The iterator points at position <pos> of array <array>.
//            <array> is passed by reference and <pos> is passed by value.
//Return value: None
//

template <typename T>
Array_Iterator<T>::Array_Iterator (Array<T> &array, size_t pos)
    : array_(array),
      pos_(pos)
{
}

#endif /* ARRAY_CPP */
