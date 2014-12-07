#pragma once

#include "CList2.h"

template<typename T>
class nsSdD::CList<T>::CConstIterator
{

private:
    CNodePtr node;

public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef int difference_type;
    typedef T *pointer;
    typedef T &reference;

    CConstIterator (CNodePtr p = nullptr) : node (p)
    {
    }

    ~CConstIterator ()
    {
    }

    CConstIterator &operator= (const CConstIterator &other)
    {
        node = other.node;
        return *this;
    }

    bool operator== (const CConstIterator &other)
    {
        return node == other.node;
    }

    bool operator!= (const CConstIterator &other)
    {
        return node != other.node;
    }

    CConstIterator &operator++ ()
    {
        node = node->getNext ();
        return *this;
    }

    CConstIterator &operator-- ()
    {
        node = node->getPrevious ();
        return *this;
    }

    CConstIterator &operator++ (int)
    {
        node = node->getNext ();
        return *this;
    }

    CConstIterator &operator-- (int)
    {
        node = node->getPrevious ();
        return *--this;
    }

    const T operator* () const
    {
        return node->getInfo ();
    }

    const CNodePtr operator-> ()
    {
        return node;
    }

};
