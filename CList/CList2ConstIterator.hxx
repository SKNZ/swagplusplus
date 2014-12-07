#pragma once

#include "CList2.h"

template<typename T> using CConstIterBase = std::iterator<std::bidirectional_iterator_tag, const T, std::ptrdiff_t, const T *, const T &>;

template<typename T>
struct nsSdD::CList<T>::CConstIterator : public CConstIterBase<T>
{
private:
    CNodePtr node;

public:
    CConstIterator (CNodePtr p = nullptr) noexcept : node (p)
    {
    }

    CConstIterator (const CConstIterator &) noexcept = default;

    CConstIterator &operator= (const CConstIterator &) noexcept = default;

    bool operator== (const CConstIterator &other) const noexcept
    {
        return node == other.node;
    }

    bool operator!= (const CConstIterator &other) const noexcept
    {
        return node != other.node;
    }

    CConstIterator &operator++ () noexcept
    {
        node = node->getNext ();
        return *this;
    }

    CConstIterator &operator-- () noexcept
    {
        node = node->getPrevious ();
        return *this;
    }

    CConstIterator operator++ (int) noexcept
    {
        CConstIterator temp = *this;
        node = node->getNext ();
        return temp;
    }

    CConstIterator operator-- (int) noexcept
    {
        CConstIterator temp = *this;
        node = node->getPrevious ();
        return temp;
    }

    typename CConstIterBase<T>::pointer operator-> () const noexcept
    {
        return &node->getInfo ();
    }

    typename CConstIterBase<T>::reference operator* () const noexcept
    {
        return node->getInfo ();
    }

    CNodePtr getNode () const noexcept
    {
        return node;
    }
};
