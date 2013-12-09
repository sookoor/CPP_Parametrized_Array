/* -*- C++ -*- */

#ifndef ARRAY_H
#define ARRAY_H

// This header defines "size_t"
#include <stdlib.h>

#include <stdexcept>

// Solve circular include problem
template <typename T>
class Array_Iterator;

/**
 * @class Array
 * @brief Implements a vector that resizes.
 */
template <class T>
class Array
{
public:
  // Define a "trait"
  typedef T TYPE;

  // = Initialization and termination methods.

  // Dynamically create an uninitialized array.  Throws <std::bad_alloc>
  // if allocation fails.
  Array (size_t size) throw (std::bad_alloc);

  // Dynamically initialize the entire array to the <default_value>.
  // Throws <std::bad_alloc> if allocation fails.
  Array (size_t size, const T &default_value) throw (std::bad_alloc);

  // The copy constructor performs initialization by making an exact
  // copy of the contents of parameter <s>, i.e., *this == s will
  // return true.  Throws <std::bad_alloc> if allocation fails.
  Array (const Array<T> &s) throw (std::bad_alloc);

  // Assignment operator performs an assignment by making a copy of
  // the contents of parameter <s>, i.e., *this == s will return true.
  // Note that if the <max_size_> of <array_> is >= than <s.cur_size_>
  // we can copy it without reallocating.  However, if <max_size_> is
  // < <s.cur_size_> we must delete the <array_>, reallocate a new
  // <array_>, and then copy the contents of <s>.  Throws
  // <std::bad_alloc> if allocation fails.
  void operator= (const Array<T> &s) throw (std::bad_alloc);

  // Clean up the array (e.g., delete dynamically allocated memory).
  ~Array (void);

  // = Forward iterator definitions
  typedef Array_Iterator<T> iterator;

  // Get an iterator that points to the beginning of the list
  iterator begin (void);

  // Get an iterator that points to the end
  iterator end (void);

  // = Set/get methods.

  // Set an item in the array at location index.  If <index> >
  // <s.cur_size_> then <resize()> the array so it's big enough.
  // Throws <std::bad_alloc> if resizing the array fails.
  void set (const T &new_item, size_t index) throw (std::bad_alloc);

  // Get an item in the array at location index.  Throws <std::out_of_range>
  // of index is not <in_range>.
  void get (T &item, size_t index) const throw (std::out_of_range);

  // Returns the <cur_size_> of the array.
  size_t size (void) const;

  // Returns a reference to the <index> element in the <Array> without
  // checking for range errors.
  const T &operator[] (size_t index) const;

  // Set an item in the array at location index without 
  // checking for range errors.
  T &operator[] (size_t index);

  // Compare this array with <s> for equality.  Returns true if the
  // size()'s of the two arrays are equal and all the elements from 0
  // .. size() are equal, else false.
  bool operator== (const Array<T> &s) const;

  // Compare this array with <s> for inequality such that <*this> !=
  // <s> is always the complement of the boolean return value of
  // <*this> == <s>.
  bool operator!= (const Array<T> &s) const;

  // Change the size of the array to be at least <new_size> elements.
  // Throws <std::bad_alloc> if allocation fails.
  void resize (size_t new_size) throw (std::bad_alloc);

private:
  // Returns true if <index> is within range, i.e., 0 <= <index> <
  // <cur_size_>, else returns false.
  bool in_range (size_t index) const;

  // Perform the initializations that can throw exceptions to
  // Isolate this all in one place.
  // void init (void) throw (std::bad_alloc);

  // Maximum size of the array, i.e., the total number of <T> elements
  // in <array_>.
  size_t max_size_;
        
  // Current size of the array.  This starts out being == to
  // <max_size_>.  However, if we are assigned a smaller array, then
  // <cur_size_> will become less than <max_size_>.  The purpose of
  // keeping track of both sizes is to avoid reallocating memory if we
  // don't have to.
  size_t cur_size_;

  // Pointer to the array's storage buffer.
  T *array_;
};

/**
 * @class Array_Iterator
 * @brief Implements a bidirectional iterator for array type classes.
 *
 * Note:  Having a const Iterator does not guarantee that the current
 * *position* that it points to will not change, it only guarantees that
 * you cannot change the underlying array!
 */
template <typename T>
class Array_Iterator 
{
public:
  /// Construct an Array_Iterator at position pos.  
  Array_Iterator (Array<T> &array, size_t pos = 0);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  T& operator* (void);

  /// Returns a const reference to the item contained at the current position
  const T& operator* (void) const;

  /// Preincrement operator
  Array_Iterator<T> &operator++ (void);

  /// Postincrement operator
  Array_Iterator<T> operator++ (int);

  /// Predecrement operator
  Array_Iterator<T> &operator-- (void);

  /// Posdecrement operator
  Array_Iterator<T> operator-- (int);

  /// Equality operator
  bool operator== (const Array_Iterator<T> &rhs) const;

  /// Nonequality operator
  bool operator!= (const Array_Iterator<T> &lhs) const;

  // = Necessary traits
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// the array we are dealing with
  Array<T> &array_;

  /// Our current position
  mutable size_t pos_;
};

#if defined (__INLINE__)
#define INLINE inline
#include "Array.inl"
#endif /* __INLINE__ */

#include "Array.cpp"

#endif /* ARRAY_H */
