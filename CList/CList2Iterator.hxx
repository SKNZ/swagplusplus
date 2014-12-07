#pragma once

#include "CList2.h"

template<typename T>
class nsSdD::CList<T>::CIterator
{
  private:
    CNodePtr node;

  public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef int difference_type;
    typedef T *pointer;
    typedef T &reference;

    CIterator (CNodePtr p = nullptr) noexcept : node (p)
    {
    }

    CIterator &operator= (const CIterator &other) noexcept
    {
        node = other.node;
        return (*this);
    }

    CIterator &operator= (const T &info) noexcept
    {
        node->setInfo (info);
        return *this;
    }

    bool operator== (const CIterator &other) noexcept
    {
        return node == other.node;
    }

    bool operator!= (const CIterator &other) noexcept
    {
        return node != other.node;
    }

    CIterator &operator++ () noexcept
    {
        node = node->getNext ();
        return *this;
    }

    CIterator &operator-- () noexcept
    {
        node = node->getPrevious ();
        return *this;
    }

    CIterator &operator++ (int) noexcept
    {
        CIterator temp = *this;
        node = node->getNext ();
        return temp;
    }

    CIterator &operator-- (int) noexcept
    {
        CIterator temp = *this;
        node = node->getPrevious ();
        return temp;
    }

    pointer operator-> () noexcept
    {
        return &node->getInfo ();
    }

    reference operator* () const noexcept
    {
        return node->m_info;
    }

    CNodePtr getNode () noexcept
    {
        return node;
    }

};
