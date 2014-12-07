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
    m_head->setNext(m_tail);
}

template<typename T>
nsSdD::CList<T>::CList (size_t n) noexcept
        : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
          m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
{
    m_head->setNext(m_tail);

    for (size_t i = 0; i < n; i++)
    {
        CNodePtr ptr = std::make_shared<CNode>(T(), nullptr, nullptr);

        ptr->setNext(m_tail);
        ptr->setPrevious(m_tail->getPrevious());

        m_tail->getPrevious()->setNext(ptr);
        m_tail->setPrevious(ptr);

        ++m_size;
    }
}

template<typename T>
nsSdD::CList<T>::CList (size_t n, const T &val) noexcept
        : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
          m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
{
    m_head->setNext(m_tail);

    for (size_t i = 0; i < n; i++)
    {
        CNodePtr ptr = std::make_shared<CNode>(val, nullptr, nullptr);
        CNodePtr lastCreated = m_tail->getPrevious ();

        ptr->setNext(m_tail);
        ptr->setPrevious (lastCreated);

        lastCreated->setNext (ptr);
        m_tail->setPrevious(ptr);

        ++m_size;
    }
}

template<typename T>
nsSdD::CList<T>::CList (const nsSdD::CList<T> &x) noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);

    for (auto itr = x.cbegin (); itr != x.cend (); ++itr)
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
typename nsSdD::CList<T>::reverse_iterator nsSdD::CList<T>::rbegin () noexcept
{
    return reverse_iterator (m_head);
}

template<typename T>
typename nsSdD::CList<T>::reverse_iterator nsSdD::CList<T>::rend () noexcept
{
    return reverse_iterator (m_tail->getPrevious ());
}

template<typename T>
typename nsSdD::CList<T>::const_reverse_iterator nsSdD::CList<T>::crbegin () const noexcept
{
    return const_reverse_iterator (m_head);
}

template<typename T>
typename nsSdD::CList<T>::const_reverse_iterator nsSdD::CList<T>::crend () const noexcept
{
    return const_reverse_iterator (m_tail->getPrevious ());
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
    if (this->size() == 0)
    {
        for (size_t i = 0; i < n; i++)
        {
            CNodePtr ptr = std::make_shared<CNode>(val, nullptr, nullptr);
            CNodePtr LastCreated = m_tail->getPrevious();

            ptr->setNext(m_tail);
            ptr->setPrevious(LastCreated);

            LastCreated->setNext(ptr);
            m_tail->setPrevious(ptr);

            ++m_size;
        }
    }
}

template<typename T>
void nsSdD::CList<T>::pop_front () noexcept
{
    CNodePtr del = m_head->getNext();
    if (del != m_tail)
    {
        CNodePtr a = del->getNext();
        m_head->setNext(a);

        a->setPrevious(m_head);

        del->setPrevious(nullptr);
        del->setNext(nullptr);

        --m_size;
    }
    else
    {
        m_size = 0;
    }

}

template<typename T>
void nsSdD::CList<T>::push_front (const T &x) noexcept
{
    CNodePtr add = std::make_shared<CNode>(x, nullptr, nullptr);

    add->setNext(m_head->getNext());
    add->setPrevious(m_head);
    add->getNext()->setPrevious(add);
    m_head->setNext(add);

    ++m_size;
}

template<typename T>
void nsSdD::CList<T>::push_back (const T &x) noexcept
{
    CNodePtr add = std::make_shared<CNode>(x, nullptr, nullptr);
    CNodePtr LastCreated = m_tail->getPrevious();

    add->setNext(m_tail);
    add->setPrevious(LastCreated);

    LastCreated->setNext(add);
    m_tail->setPrevious(add);

    ++m_size;
}

template<typename T>
void nsSdD::CList<T>::pop_back () noexcept
{
    CNodePtr del = m_tail->getPrevious();
    m_tail->setPrevious(del->getPrevious());

    del->getPrevious()->setNext(m_tail);

    del->setPrevious(nullptr);
    del->setNext(nullptr);

    --m_size;
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::erase (nsSdD::CList<T>::iterator del) noexcept
{
    del.getNode ()->getNext ()->setPrevious (del.getNode ()->getPrevious ());
    del.getNode ()->getPrevious ()->setNext (del.getNode ()->getNext ());

    --m_size;

    return nsSdD::CList<T>::iterator (del.getNode ()->getNext ());
}

template<typename T>
void nsSdD::CList<T>::resize (unsigned n, const T &val /*= T()*/) noexcept
{
    if (m_size == n)
        return;

    if (m_size > n) // Reducing
    {
        CNodePtr currentNode = m_head;
        for (size_t i = 0; i < n; ++i)
            currentNode = currentNode->getNext ();

        currentNode->setNext (m_tail);
        m_tail->setPrevious (currentNode);
        if (n == 0)
            IZI_ASSERT(m_head->getNext () == m_tail);

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

//    CNodePtr ptr = m_head->getNext();
//    m_head->setNext(x.getHead()->getNext());
//    x.getHead()->setNext(ptr);
//
//    ptr = m_tail->getPrevious();
//    m_tail->setPrevious(x.getTail()->getPrevious());
//    x.getTail()->setPrevious(ptr);
//
//    size_t tmp = m_size;
//    m_size = x.size();
//
//    x.m_size = tmp;
}

template<typename T>
void nsSdD::CList<T>::clear () noexcept
{
    m_head->setNext(m_tail);
    m_tail->setPrevious(m_head);

    m_size = 0;
}

template<typename T>
void nsSdD::CList<T>::remove (const T &val) noexcept
{
    for (CNodePtr a = m_head->getNext (); a != m_tail; a = a->getNext ())
    {
        if (a->getInfo() == val)
        {
            a->getPrevious ()->setNext (a->getNext ());
            a->getNext ()->setPrevious (a->getPrevious ());
            --m_size;
        }
    }
}

template<typename T>
template<class Predicate>
void nsSdD::CList<T>::remove_if (Predicate pred) noexcept
{
    for (CNodePtr a = m_head->getNext (); a != m_tail; a = a->getNext ())
    {
        if (pred (a->getInfo ()))
        {
            a->getPrevious ()->setNext (a->getNext ());
            a->getNext ()->setPrevious (a->getPrevious ());
            --m_size;
        }
    }
}

template<typename T>
void nsSdD::CList<T>::reverse () noexcept
{
    CNodePtr tmp = m_head;
    m_head->setNext(m_tail->getPrevious());
    m_tail->setPrevious(tmp->getNext());

    for (size_t i = 0; i < m_size; ++i)
    {
        CNodePtr ptr = tmp->getNext()->getPrevious();
        tmp->getNext()->setPrevious(tmp->getNext()->getNext());
        tmp->getNext()->setNext(ptr);

        tmp = tmp->getNext();
    }
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::insert (typename nsSdD::CList<T>::iterator position, T const &val) noexcept
{
    CNodePtr tmp = std::make_shared<CNode>(val);
    tmp->setNext(position.getNode());
    tmp->setPrevious (position.getNode ()->getPrevious ());
    position.getNode ()->getPrevious ()->setNext (tmp);
    position.getNode ()->setPrevious (tmp);

    ++m_size;

    return nsSdD::CList<T>::iterator (tmp);
}

template<typename T>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::insert (typename nsSdD::CList<T>::iterator position, size_type n, T const &val) noexcept
{

    CNodePtr nextNode = position.getNode ();
    CNodePtr prevNode = nextNode->getPrevious ();

    for (int i = 0; i < n; ++i)
    {
        CNodePtr newNode = std::make_shared<CNode> (val, nextNode, prevNode);
        prevNode->setNext (newNode);
        nextNode->setPrevious (newNode);
        ++m_size;
        prevNode = newNode;
    }

    return iterator (prevNode->getNext ());
}

template<typename T>
template<class InputIterator>
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::insert (typename nsSdD::CList<T>::iterator position, InputIterator begin, InputIterator end) noexcept
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
typename nsSdD::CList<T>::iterator nsSdD::CList<T>::emplace (typename nsSdD::CList<T>::iterator position, Args &&... args)
{
    T newValue (std::forward<Args> (args)...);
    CNodePtr newNode = position.getNode ()->addBefore (newValue);
    return iterator (newNode);
}
