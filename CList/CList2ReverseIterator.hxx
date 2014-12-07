#pragma once

#include "CList2.h"

template<typename T>
class nsSdD::CList<T>::CReverseIterator
{
  private:
    CIterator it;

  public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef int difference_type;
    typedef T *pointer;
    typedef T &reference;

    explicit CReverseIterator (CIterator i) : it (i)
    {
    }

    CReverseIterator () : it (nullptr)
    {
    }

    CIterator base () const
    {
        CIterator itCopy = it;
        return --itCopy;
    }

    CReverseIterator operator++ ()
    {
        --it;
        return *this;
    }

    CReverseIterator operator-- ()
    {
        ++it;
        return *this;
    }

    CReverseIterator operator++ (int)
    {
        CReverseIterator before = *this;
        --it;
        return before;
    }

    CReverseIterator operator-- (int)
    {
        CReverseIterator before = *this;
        ++it;
        return before;
    }

    bool operator== (const CReverseIterator &other)
    {
        return it == other.it;
    }

    bool operator!= (const CReverseIterator &other)
    {
        return it != other.it;
    }

    T &operator* () const
    {
        return *it;
    }

    CReverseIterator &operator= (const T &info)
    {
        it->setInfo (info);
        return *this;
    }


};