#pragma once

#include "CList2.h"

template<typename T> using CIterBase = std::iterator<std::bidirectional_iterator_tag, T>;

template<typename T>
struct nsSdD::CList<T>::CIterator : public CIterBase<T>
{
private:
    CNodePtr node;

public:
    CIterator (CNodePtr p = nullptr) noexcept : node (p)
    {
    }

    CIterator (const CIterator &) = default;

    CIterator &operator= (const CIterator &) noexcept = default;
    CIterator &operator= (const T &info) noexcept
    {
        node->setInfo (info);
        return *this;
    }

    bool operator== (const CIterator &other) const noexcept
    {
        return node == other.node;
    }

    bool operator!= (const CIterator &other) const noexcept
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

    CIterator operator++ (int) noexcept
    {
        CIterator temp = *this;
        node = node->getNext ();
        return temp;
    }

    CIterator operator-- (int) noexcept
    {
        CIterator temp = *this;
        node = node->getPrevious ();
        return temp;
    }

    typename CIterBase<T>::pointer operator-> () noexcept
    {
        return &node->getInfo ();
    }

    typename CIterBase<T>::reference operator* () noexcept
    {
        return node->getInfo ();
    }

    typename CIterBase<T>::reference operator* () const noexcept
    {
        return node->getInfo ();
    }

    CNodePtr getNode () noexcept
    {
        return node;
    }
};
