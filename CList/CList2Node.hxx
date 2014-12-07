#pragma once

#include "CList2.h"

template<typename T>
class nsSdD::CList<T>::CNode : public std::enable_shared_from_this<nsSdD::CList<T>::CNode>
{
  public:
    T m_info;

  private:
    CNodePtr m_next;
    CNodePtr m_previous;

    CNode (const CNode &) noexcept
    {
    }

    CNode &operator= (const CNode &c) noexcept
    {
        // @todo Should this really be empty ?
    }

  public:
    CNode (T info = T (), CNodePtr next = nullptr, CNodePtr previous = nullptr) noexcept
            : m_info (info), m_next (next),
              m_previous (previous)
    {
    }

    ~CNode () noexcept
    {
    }

    inline T getInfo () noexcept
    {
        return m_info;
    }

    inline void setInfo (T info) noexcept
    {
        m_info = info;
    }

    inline CNodePtr &getNext ()  noexcept
    {
        return m_next;
    }

    inline void setNext (CNodePtr next) noexcept
    {
        m_next = next;
    }

    inline CNodePtr &getPrevious ()  noexcept
    {
        return m_previous;
    }

    inline void setPrevious (CNodePtr previous) noexcept
    {
        m_previous = previous;
    }

    inline void remove () noexcept
    {
        m_next->setPrevious (m_previous);
        m_previous->setNext (m_next);
    }

    inline CNodePtr addBefore (const T &val) noexcept
    {
        CNodePtr newNode = std::make_shared<CNode> (val, m_previous, this->shared_from_this ());
        m_previous->m_next = newNode;
        m_previous = newNode;
        return newNode;
    }
};
