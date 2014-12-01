#include "CList.h"

using namespace std;
using namespace nsSdD;

template<typename T>
CList<T>::CList() noexcept : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
                             m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
{
    m_head->setNext(m_tail);
}

template<typename T>
CList<T>::CList(size_t n) noexcept
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
CList<T>::CList(size_t n, const T &val) noexcept
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
CList<T>::CList(const CList<T> &x) noexcept
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
void CList<T>::assign(unsigned n, const T &val)
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