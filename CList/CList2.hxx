#pragma once

#include <memory>
#include <iterator>
#include "CList2.h"
#include "CList2Node.hxx"

template<typename T>
nsSdD::CList<T>::CList () noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);
}

template<typename T>
nsSdD::CList<T>::CList (size_type n) noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);

    for (size_type i = 0; i < n; i++)
        push_back (T ());
}

template<typename T>
nsSdD::CList<T>::CList (size_type n, const T &val) noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);

    for (size_type i = 0; i < n; i++)
        push_back (val);
}

template<typename T>
nsSdD::CList<T>::CList (const nsSdD::CList<T> &list) noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);

    for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
        push_back (*itr);
}

template<typename T>
template<class InputIterator>
nsSdD::CList<T>::CList (InputIterator begin, InputIterator end) noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);

    assign (begin, end);
}

template<typename T>
typename nsSdD::CList<T>::CNodePtr nsSdD::CList<T>::getHead () const noexcept
{
    return m_head;
}

template<typename T>
typename nsSdD::CList<T>::CNodePtr nsSdD::CList<T>::getTail () const noexcept
{
    return m_tail;
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::begin () noexcept
{
    return iterator (m_head->getNext ());
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::end () noexcept
{
    return iterator (m_tail);
}

template<typename T>
typename nsSdD::CList<T>::const_iterator nsSdD::CList<T>::cbegin () const noexcept
{
    return const_iterator (m_head->getNext ());
}

template<typename T>
typename nsSdD::CList<T>::const_iterator nsSdD::CList<T>::cend () const noexcept
{
    return const_iterator (m_tail);
}

template<typename T>
typename std::reverse_iterator<typename nsSdD::CList<T>::iterator> nsSdD::CList<T>::rbegin () noexcept
{
    return std::reverse_iterator<iterator> (end ());
}

template<typename T>
typename std::reverse_iterator<typename nsSdD::CList<T>::iterator> nsSdD::CList<T>::rend () noexcept
{
    return std::reverse_iterator<iterator> (begin ());
}

template<typename T>
typename std::reverse_iterator<typename nsSdD::CList<T>::const_iterator> nsSdD::CList<T>::crbegin () noexcept
{
    return std::reverse_iterator<const_iterator> (cend ());
}

template<typename T>
typename std::reverse_iterator<typename nsSdD::CList<T>::const_iterator> nsSdD::CList<T>::crend () noexcept
{
    return std::reverse_iterator<const_iterator> (cbegin ());
}

template<typename T>
bool nsSdD::CList<T>::empty () const noexcept
{
    return m_size == 0;
}

template<typename T>
typename nsSdD::CList<T>::size_type nsSdD::CList<T>::size () const noexcept
{
    return m_size;
}

template<typename T>
T nsSdD::CList<T>::front () const noexcept
{
    return m_head->getNext ()->getInfo ();
}

template<typename T>
T nsSdD::CList<T>::back () const noexcept
{
    return m_tail->getPrevious ()->getInfo ();
}

template<typename T>
template<class InputIterator>
void nsSdD::CList<T>::assign (InputIterator begin, InputIterator last)
{
    clear ();
    for (; begin != last; ++begin)
        push_back (*begin);
}

template<typename T>
void nsSdD::CList<T>::assign (unsigned n, const T &val) noexcept
{
    clear ();
    for (int i = 0; i < n; ++i)
        push_back (val);
}

template<typename T>
void nsSdD::CList<T>::pop_front () noexcept
{
    if (m_size != 0)
    {
        m_head->getNext ()->remove ();
        --m_size;
    }
}

template<typename T>
void nsSdD::CList<T>::push_front (const T &x) noexcept
{
    m_head->addAfter (x);
    ++m_size;
}

template<typename T>
void nsSdD::CList<T>::push_back (const T &x) noexcept
{
    m_tail->addBefore (x);
    ++m_size;
}

template<typename T>
void nsSdD::CList<T>::pop_back () noexcept
{
    if (m_size != 0)
    {
        m_tail->getPrevious ()->remove ();
        --m_size;
    }
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::erase (nsSdD::CList<T>::iterator del) noexcept
{
    del.getNode ()->remove ();
    --m_size;

    return iterator (del.getNode ()->getNext ());
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::erase (iterator first, iterator last) noexcept
{
    for(auto i = first ; i != last ; ++i)
        erase (i);

    return iterator (last.getNode ());
}

template<typename T>
void nsSdD::CList<T>::resize (unsigned n, const T &val /*= T()*/) noexcept
{
    if (m_size == n)
        return;

    if (m_size > n) // Reducing
    {
        iterator itr = begin ();
        std::advance (itr, n - 1);

        itr.getNode ()->setNext (m_tail);
        m_tail->setPrevious (itr.getNode ());

        m_size = n;
    }
    else // Expanding
    {
        for (; n != 0; --n)
            push_back (val);
    }
}

template<typename T>
void nsSdD::CList<T>::swap (nsSdD::CList<T> &x) noexcept
{
    // Is this even legit ?
    std::swap (x.m_head, m_head);
    std::swap (x.m_tail, m_tail);
    std::swap (x.m_size, m_size);
}

template<typename T>
void nsSdD::CList<T>::clear () noexcept
{
    m_head->setNext (m_tail);
    m_tail->setPrevious (m_head);

    m_size = 0;
}

template<typename T>
void nsSdD::CList<T>::remove (const T &val) noexcept
{
    remove_if ([val] (const T &x)
    {
        return x == val;
    });
}

template<typename T>
template<class Predicate>
void nsSdD::CList<T>::remove_if (Predicate pred) noexcept
{
    for (CNodePtr a = m_head->getNext (); a != m_tail; a = a->getNext ())
    {
        if (pred (a->getInfo ()))
        {
            a->remove ();
            --m_size;
        }
    }
}

template<typename T>
void nsSdD::CList<T>::unique () noexcept
{
    unique ([] (const T &a, const T &b)
    {
        return a == b;
    });
}

template<typename T>
template<class Compare>
void nsSdD::CList<T>::unique (Compare comp) noexcept
{
    for (CNodePtr currNode = m_head->getNext (); currNode != m_tail; currNode = currNode->getNext ())
        while (comp (currNode->getInfo (), currNode->getNext ()->getInfo ()))
        {
            currNode->getNext ()->remove ();
            --m_size;
        }
}

template<typename T>
void nsSdD::CList<T>::reverse () noexcept
{
    for (CNodePtr currentNode = m_head; currentNode != m_tail; currentNode = currentNode->getPrevious ())
        std::swap (currentNode->getNext (), currentNode->getPrevious ());

    std::swap (m_tail->getNext (), m_tail->getPrevious ());
    std::swap (m_tail, m_head);
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::insert (iterator position, T const &val) noexcept
{
    ++m_size;
    return iterator (position.getNode ()->addBefore (val));
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::insert (iterator position, size_type n, T const &val) noexcept
{
    CNodePtr nextNode = position.getNode (),
            prevNode = nextNode->getPrevious (),
            currNode = prevNode;

    for (int i = 0; i < n; ++i)
    {
        currNode = nextNode->addBefore (val);
        ++m_size;
    }

    return iterator (prevNode->getNext ());
}

template<typename T>
template<class InputIterator>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::insert (iterator position, InputIterator begin, InputIterator end) noexcept
{
    CNodePtr nextNode = position.getNode ();
    CNodePtr prevNode = nextNode->getPrevious ();

    for (; begin != end; ++begin)
    {
        nextNode->addBefore (*begin);
        ++m_size;
    }

    return iterator (prevNode->getNext ());
}

template<typename T>
template<typename... Args>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::emplace (iterator position, Args &&... args)
{
    return insert (position, T (std::forward<Args> (args)...));
}

template<typename T>
template<typename... Args>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::emplace_front (Args &&... args)
{
    return emplace (begin (), std::forward<Args> (args)...);
}

template<typename T>
template<typename... Args>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::emplace_back (Args &&... args)
{
    return emplace (end (), std::forward<Args> (args)...);
}

template<typename T>
void nsSdD::CList<T>::splice (iterator position, typename nsSdD::CList<T>& x) noexcept
{
    insert (position, x.begin (), x.end ());
    x.clear ();
}

template<typename T>
void nsSdD::CList<T>::splice (iterator position, nsSdD::CList<T> &x, iterator i) noexcept
{
    insert (position, *i);
    x.erase (i);
}

template<typename T>
void nsSdD::CList<T>::splice(iterator position, CList& x, iterator first, iterator last) noexcept
{
    insert (position, first, last);
    x.erase (first,last);
}

template <typename T>
void nsSdD::CList<T>::sort() noexcept
{
    sort ([] (const T &a, const T &b)
    {
        return a < b;
    });
}

template <typename T>
template<class Compare>
void nsSdD::CList<T>::sort(Compare comp) noexcept
{
    for (iterator i = begin (); i != end (); ++i)
        for (iterator j = i; j != end (); ++j)
            if(comp(*j, *i))
                std::iter_swap(i, j);
}

template<typename T>
void  nsSdD::CList<T>::merge (nsSdD::CList<T>& x) noexcept
{
    splice (end(), x);
    sort();
}
