#pragma once

#include "CList2.h"

template<typename T>
class nsSdD::CList<T>::CConstReverseIterator
{

  private:
    CConstIterator it;

  public:

    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef int difference_type;
    typedef T *pointer;
    typedef T &reference;

    CConstReverseIterator (CConstIterator i) : it (i)
    {
    }

    CConstReverseIterator () : it (NULL)
    {
    }

    ~CConstReverseIterator ()
    {
    }

    CConstReverseIterator base () const
    {
        CConstReverseIterator ittmp = it;
        return --ittmp;
    }

    CConstReverseIterator operator++ ()
    {
        return CConstReverseIterator (--it);
    }

    CConstReverseIterator operator-- ()
    {
        return CConstReverseIterator (++it);
    }

    CConstReverseIterator operator++ (int)
    {
        return *++this;
    }

    CConstReverseIterator operator-- (int)
    {
        return *--this;
    }

    bool operator== (const CConstReverseIterator &other)
    {
        return it == other.it;
    }

    bool operator!= (const CConstReverseIterator &other)
    {
        return it != other.it;
    }

    const T operator* () const
    {
        return *it;
    }

};