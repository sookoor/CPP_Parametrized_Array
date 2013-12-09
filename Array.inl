// Returns the current size of the array.

template <class T> INLINE size_t 
Array<T>::size (void) const
{
    return this->cur_size_;
}

// Returns true if <index> is within range, i.e., 0 <= <index> <
// <cur_size_>, else returns false.

template <class T> INLINE bool
Array<T>::in_range (size_t index) const
{
    return index < this->cur_size_;
}

// Set an item in the array at location index without 
// checking for range errors

template <class T> INLINE T &
Array<T>::operator[] (size_t index)
{
    return this->array_[index];
}

// Returns a reference to the <index> element in the <Array> without
// checking for range errors.

template <class T> INLINE const T &
Array<T>::operator[] (size_t index) const
{
    return this->array_[index];
} 

// Get an iterator to the begniing of the array
template <typename T> INLINE typename Array<T>::iterator
Array<T>::begin (void)
{
    Array_Iterator<T> iter (*this);
    return iter;
}

// Get an iterator pointing past the end of the array
template <typename T> INLINE typename Array<T>::iterator
Array<T>::end (void)
{
    return typename Array<T>::iterator (*this, this->size ());
}

/// Dereference operator returns a reference to the item contained
/// at the current position

template <typename T> INLINE T &
Array_Iterator<T>::operator* (void)
{
    return this->array_[this->pos_];
}

/// Returns a const reference to the item contained at the current position

template <typename T> INLINE const T &
Array_Iterator<T>::operator* (void) const
{
    return this->array_[this->pos_];
}

/// Preincrement operator

template <typename T> INLINE Array_Iterator<T> &
Array_Iterator<T>::operator++ (void) 
{
    ++this->pos_;
    return *this;
}

/// Postincrement operator

template <typename T> INLINE Array_Iterator<T> 
Array_Iterator<T>::operator++ (int) 
{
    Array_Iterator<T> old (*this);
    ++(*this);
    return old;
}

/// Predecrement operator

template <typename T> INLINE Array_Iterator<T> &
Array_Iterator<T>::operator-- (void)
{
    --this->pos_;
    return *this;
}

/// Posdecrement operator

template <typename T> INLINE Array_Iterator<T>
Array_Iterator<T>::operator-- (int) 
{
    Array_Iterator<T> old (*this);
    --(*this);
    return old;
}

/// Equality operator

template <typename T> INLINE bool
Array_Iterator<T>::operator== (const Array_Iterator<T> &rhs) const
{
    return &this->array_ == &rhs.array_ && this->pos_ == rhs.pos_;
}

/// Nonequality operator

template <typename T> INLINE bool
Array_Iterator<T>::operator!= (const Array_Iterator<T> &rhs) const
{
    return !(*this == rhs);
}

