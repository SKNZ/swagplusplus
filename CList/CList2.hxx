
#include <memory>
#include "CList2.h"

#define NSCLIST nsSdD::CList<T>

template<typename T>
NSCLIST::CList() noexcept : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
                             m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
{
    m_head->setNext(m_tail);
}

template<typename T>
NSCLIST::CList(size_t n) noexcept
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
NSCLIST::CList(size_t n, const T &val) noexcept
        : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
          m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
{
    m_head->setNext(m_tail);

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

template<typename T>
NSCLIST::CList(const NSCLIST &x) noexcept
{
    m_head = x.getHead();
    m_tail = x.getTail();
    m_size = x.size();

    for (CNodePtr p = x.getHead(); p; p = p->getNext())
    {
        CNodePtr temp = std::make_shared<CNode>(p->getInfo(), p->getNext(), p->getPrevious());
    }
}


template<typename T>
template<class InputIterator>
void NSCLIST::assign(InputIterator first, InputIterator last)
{
    CNodePtr prec = m_head;
    m_size = 0;
    for (auto tmp = first; tmp < last; tmp++)
    {
        CNodePtr add = std::make_shared<CNode>(*tmp);

        prec->setNext(add);

        add->setPrevious(prec);
        add->setNext(prec->getNext());

        m_tail->setPrevious(add);

        ++m_size;
        prec = add;

    }
    m_tail->setPrevious(prec);
}

template<typename T>
void NSCLIST::assign(unsigned n, const T &val) noexcept
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
template <class... Args>
void NSCLIST::emplace_front(Args&&... val) noexcept
{
    CNodePtr ptr = std::make_shared<CNode>(val..., nullptr, nullptr);

    ptr->setPrevious(m_head);
    ptr->setNext(m_head->getNext());

    (m_head->getNext())->setPrevious(ptr);

    m_head->setNext(ptr);

    ++m_size;
}

template<typename T>
void NSCLIST::pop_front() noexcept
{
    CNodePtr del = m_head->getNext();
    if(del != m_tail)
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
void NSCLIST::push_front(const T &x) noexcept
{
    CNodePtr add = std::make_shared<CNode>(x, nullptr, nullptr);

    add->setNext(m_head->getNext());
    add->setPrevious(m_head);
    add->getNext()->setPrevious(add);
    m_head->setNext(add);

    ++m_size;
}

template<typename T>
void NSCLIST::push_back(const T &x) noexcept
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
void NSCLIST::pop_back() noexcept
{
    CNodePtr del = m_tail->getPrevious();
    m_tail->setPrevious(del->getPrevious());

    del->getPrevious()->setNext(m_tail);

    del->setPrevious(nullptr);
    del->setNext(nullptr);

    --m_size;
}

template<typename T>
void NSCLIST::emplace(CNodePtr Prec, T val) noexcept
{
    CNodePtr add = std::make_shared<CNode>(val, Prec, Prec->getNext());

    Prec->getNext()->setPrevious(add);
    Prec->setNext(add);

    ++m_size;
}

template<typename T>
typename NSCLIST::iterator NSCLIST::erase(NSCLIST::iterator del) noexcept
{
    del->getNext()->setPrevious(del->getPrevious());
    del->getPrevious()->setNext(del->getNext());

    --m_size;

    return NSCLIST::iterator(del->getNext());
}

template<typename T>
void NSCLIST::resize(unsigned n, const T &val /*= T()*/) noexcept
{
    if (m_size == n)
        return;

    if (m_size > n)
    {
        CNodePtr ptr = m_head;
        for (size_t i = 0; i < n; ++i)
            ptr = ptr->getNext();

        ptr->setNext(m_tail);
        m_tail->setPrevious(ptr);

        m_size = n;

        return;
    }

    CNodePtr ptr = m_head;
    for (size_t i = 0; i < m_size; ++i)
        ptr = ptr->getNext();

    for (size_t i = 0; i < n - m_size; ++i)
    {
        CNodePtr add = std::make_shared<CNode>(val, ptr, ptr->getNext());
        ptr->setNext(add);
        m_tail->setPrevious(add);
        ptr = add;
    }

    m_size = n;
}

template<typename T>
void NSCLIST::swap(NSCLIST &x) noexcept
{
    CNodePtr ptr = m_head;
    m_head->setNext(x.getHead()->getNext());
    x.getHead()->setNext(ptr->getNext());

    ptr = m_tail;
    m_tail->setPrevious(x.getTail()->getPrevious());
    x.getTail()->setPrevious(ptr->getPrevious());

    size_t tmp = m_size;
    m_size = x.size();

    x.m_size = tmp;
}

template<typename T>
void NSCLIST::clear() noexcept
{
    m_head->setNext(m_tail);
    m_tail->setPrevious(m_head);

    m_size = 0;
}

template<typename T>
void NSCLIST::remove(const T &val) noexcept
{
    for (CNodePtr a = m_head; a; a = a->getNext())
    {
        if (a->getInfo() == val)
        {
            (a->getPrevious())->setNext(a->getNext());
            (a->getNext())->setPrevious(a->getPrevious());
            a->setNext(nullptr);
            a->setPrevious(nullptr);
            return;
        }
    }
}

template<typename T>
template<class Predicate>
void NSCLIST::remove_if(Predicate pred) noexcept
{
    for (CNodePtr a = m_head; a; a = a->getNext())
    {
        if (!pred(a))
        {
            (a->getPrevious())->setNext(a->getNext());
            (a->getNext())->setPrevious(a->getPrevious());
            a->setNext(nullptr);
            a->setPrevious(nullptr);
        }
    }
}

template<typename T>
void NSCLIST::reverse() noexcept
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
void NSCLIST::emplace_back(T val) noexcept
{
    CNodePtr a = std::make_shared<CNode>(val, m_tail->getPrevious(), m_tail);
    (m_tail->getPrevious())->setNext(a);
    m_tail->setPrevious(a);

    ++m_size;
}

template<typename T>
typename NSCLIST::iterator NSCLIST::insert(typename NSCLIST::iterator position, T const &val) noexcept
{
    CNodePtr tmp = std::make_shared<CNode>(val);
    tmp->setNext(position.getNode());
    tmp->setPrevious(position->getPrevious());
    (position->getPrevious())->setNext(tmp);
    position->setPrevious(tmp);

    ++m_size;

    return NSCLIST::iterator(tmp);
}
