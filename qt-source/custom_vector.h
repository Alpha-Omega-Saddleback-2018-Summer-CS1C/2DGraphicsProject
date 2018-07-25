/*
 *  2D Graphics Modeler
 *  July 2018
 *
 *  David Epstein <DavidE92@live.com>
 *  Greg Graffius <ggraffius0@saddleback.edu>
 *  Justis Ketcham Justis <justis.ketcham@gmail.com>
 *  Brett Saiki <bsaiki0@saddleback.edu>
 *
 *  Descr:   Final project for CS1C at Saddleback College (Summer 2018)
 *  Teacher: John Kath
 *
 *  Draws shapes using QPainter. Shapes can be loaded from a file, added
 *  to a vector, manipulated and later saved. A login is required to access
 *  the program.
 *
 **/
/*
    File: custom_vector.h

    Defines UI features
 */

#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <assert.h>

template<typename T>
class Vector
{
    static const int DEFAULT_SIZE = 8;

public:

    /* Type aliasing */
    using iterator = T*;
    using const_iterator = const T*;

    /* Default constructor */
    Vector() : mArray(new T[DEFAULT_SIZE]), mSize(0), mReservedSize(DEFAULT_SIZE)
    {
        for(int i = 0; i < mReservedSize; ++i)
            mArray[i] = T();
    }

    /* Alternate constructor */
    explicit Vector(int size)  : mArray(new T[size]), mSize(0), mReservedSize(size)
    {
        for(int i = 0; i < mReservedSize; ++i)
            mArray[i] = T();
    }

    /* Copy constructor */
    Vector(const Vector& vec) : mSize(vec.mSize), mReservedSize(vec.mReservedSize)
    {
        mArray = new T[mReservedSize];
        for(int i = 0; i < mReservedSize; ++i)
            mArray[i] = vec.mArray[i];
    }

    /* Move constructor */
    Vector(Vector&& vec) : mArray(vec.mArray), mSize(vec.mSize), mReservedSize(vec.mReservedSize)
    {
        vec.mArray = nullptr;
        vec.mSize = 0;
        vec.mReservedSize = 0;
    }

    /* Destructor */
    ~Vector()
    {
        if(mArray != nullptr)
        {
            delete[] mArray;
            mArray = nullptr;
        }
    }

    /* Copy assignment */
    Vector& operator=(const Vector& vec)
    {
        if(mArray != nullptr)
            delete[] mArray;

        mArray = new T[mReservedSize];
        mSize = vec.mSize;
        mReservedSize = vec.mReservedSize;
        for(int i = 0; i < mReservedSize; ++i)
            mArray[i] = vec.mArray[i];

        return *this;
    }

    /* Move assignment */
    Vector& operator=(Vector&& vec)
    {
        if(mArray != nullptr)
            delete[] mArray;

        mArray = vec.mArray;
        mSize = vec.mSize;
        mReservedSize = vec.mReservedSize;
        vec.mArray = nullptr;
        vec.mSize = 0;
        vec.mReservedSize = 0;

        return *this;
    }

    /* Access operator */
    T& operator[](int n)
    {
        assert(n < mSize);
        return mArray[n];
    }

    /* Access operator */
    const T& operator[](int n) const
    {
        assert(n < mSize);
        return mArray[n];
    }

    /* Returns an iterator to the first element */
    iterator begin()
    {
        return mArray;
    }

    /* Returns an iterator to the first element */
    const_iterator begin() const
    {
        return mArray;
    }

    /* Returns the number of elements allocated in the vector */
    int capacity() const
    {
        return mReservedSize;
    }

    /* Sets the number of elements to 0, effectively clearing the vector */
    void clear()
    {
        mSize = 0;
    }

    /* Returns an iterator to the element beyond the last element */
    iterator end()
    {
        return &mArray[mSize];
    }

    /* Returns an iterator to the element beyond the last element */
    const_iterator end() const
    {
        return &mArray[mSize];
    }

    /* Removes an element pointed to by a given iterator */
    iterator erase(iterator it)
    {
        for(iterator i = it; i != &mArray[mSize - 1]; ++i)
            *i = *(i + 1);

        --mSize;
        return it;
    }

    /* Inserts a new element before a given iterator */
    iterator insert(iterator it, const T& value)
    {
        if(mSize + 1 > mReservedSize)
        {
            T* tmp = mArray;
            mArray = new T[mReservedSize * 2];
            for(int i = 0; i < mReservedSize; ++i)
                mArray[i] = tmp[i];
            delete[] tmp;
            mReservedSize *= 2;
        }

        for(iterator i = &mArray[mSize - 1]; i >= it; --i)
            *(i + 1) = *i;
        *it = value;
        ++mSize;

        return it;
    }

    /* Deletes the last element */
    void pop_back()
    {
        --mSize;
    }

    /* Adds an element and the end */
    void push_back(const T& value)
    {
        if(mSize + 1 > mReservedSize)
        {
            T* tmp = mArray;
            mArray = new T[mReservedSize * 2];
            for(int i = 0; i < mReservedSize; ++i)
                mArray[i] = tmp[i];
            delete[] tmp;
            mReservedSize *= 2;
        }

        mArray[mSize] = value;
        ++mSize;
    }

    /* Resizes the vector if the requested size is large than the current reserved size */
    void reserve(int size)
    {
        if(size > mReservedSize)
        {
            T* tmp = mArray;
            mArray = new T[size];
            mReservedSize = size;

            for(int i = 0; i < mReservedSize; ++i)
                mArray[i] = tmp[i];
            delete[] tmp;
        }
    }

    /* Resizes the vector */
    void resize(int size)
    {
        T* tmp = mArray;
        mArray = new T[size];
        mReservedSize = size;
        if(mSize > size)  mSize = size;

        for(int i = 0; i < mReservedSize; ++i)
            mArray[i] = tmp[i];
        delete[] tmp;
    }

    /* Returns the number of elements stored in the vector */
    int size() const
    {
        return mSize;
    }

private:
    T*  mArray;
    int mSize;
    int mReservedSize;
};

template<typename T>
void custom_swap(T& a, T& b)
{
    T c = a;
    a = b;
    b = c;
}

template<typename It, typename T, typename Cmp>
It custom_find(It first, It last, const T& value, Cmp func)
{
    while(first != last)
    {
        if(func(*first, value))
            return first;
        ++first;
    }

    return last;
}

template<typename It, typename Cmp>
void selection_sort(It first, It last, Cmp func)
{
    for(It it1 = first ; it1 != last; ++it1)
    {
        It it2 = it1;

        for(It it3 = it1; it3 != last; ++it3)
        {
            if(func(*it2, *it3))
                it2 = it3;
        }

        custom_swap(*it1, *it2);
    }
}

#endif // CUSTOM_VECTOR_H
