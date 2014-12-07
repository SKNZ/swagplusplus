#pragma once

#include "CList2.h"

template<typename T>
class nsSdD::CList<T>::CNode
{
private:
    /*!
        @var m_info
        @brief This is the info value of the CNode
     */
    T m_info;

    /*!
        @var m_next
        @brief This is the next CNode of the current
     */
    CNodePtr m_next;

    /*!
        @var m_previous
        @brief This is the previous CNode of the current
     */
    CNodePtr m_previous;

    /*!
        @fn CNode (const CNode &) noexcept
        @brief This is the This is the copy-constructor
     */
    CNode (const CNode &) noexcept
    {
    }

    /*!
        @fn CNode &operator= (const CNode &c) noexcept = delete;
        @brief This is the operator= of the CNode
     */
    CNode &operator= (const CNode &c) noexcept = delete;

public:
    /*!
        @fn CNode (T info = T (), CNodePtr next = nullptr, CNodePtr previous = nullptr) noexcept
        @brief This is the constructor of the class CNode
        @params[in] info This is the info of the CNode
        @params[in] @p next This is the next CNode
        @params[in] @p next This is the previous CNode
     */
    explicit CNode (T info = T (), CNodePtr next = nullptr, CNodePtr previous = nullptr) noexcept
            : m_info (info), m_next (next),
              m_previous (previous)
    {
    }

    /*!
        @fn ~CNode () noexcept
        @brief This is the destructor of the class CNode
     */
    ~CNode () noexcept
    {
    }

    /*!
        @fn inline T &getInfo () noexcept
        @brief This is the getter of info
     */
    inline T &getInfo () noexcept
    {
        return m_info;
    }

    /*!
        @fn inline void setInfo (T info) noexcept
        @brief This is the setter of info
        @param[in] info This is the info that you liked to define
     */
    inline void setInfo (T info) noexcept
    {
        m_info = info;
    }

    /*!
        @fn inline CNodePtr &getNext ()  noexcept
        @brief This is the getter of the next CNode
     */
    inline CNodePtr &getNext ()  noexcept
    {
        return m_next;
    }

    /*!
        @fn inline void setNext (CNodePtr next) noexcept
        @brief This is the setter of the next CNode
        @param[in] next This is the next CNode that you liked to define
     */
    inline void setNext (CNodePtr next) noexcept
    {
        m_next = next;
    }

    /*!
        @fn inline CNodePtr &getPrevious ()  noexcept
        @brief This is the getter of the previous CNode
     */
    inline CNodePtr &getPrevious ()  noexcept
    {
        return m_previous;
    }

    /*!
        @fn inline void setPrevious (CNodePtr previous) noexcept
        @brief This is the setter of the previous CNode
        @param[in] previous This is the previous CNode that you liked to define
     */
    inline void setPrevious (CNodePtr previous) noexcept
    {
        m_previous = previous;
    }

    /*!
        @fn inline void remove () noexcept
        @brief This function deletes the CNode
     */
    inline void remove () noexcept
    {
        m_next->setPrevious (m_previous);
        m_previous->setNext (m_next);
    }

    /*!
        @fn inline CNodePtr addBefore (const T &val) noexcept
        @brief This function adds a CNode before
        @param[in] val This is the value of the CNode that you want to add
     */
    inline CNodePtr addBefore (const T &val) noexcept
    {
        CNodePtr newNode = std::make_shared<CNode> (val, m_previous->m_next, m_previous);
        m_previous->m_next = newNode;
        m_previous = newNode;
        return newNode;
    }

    /*!
        @fn inline CNodePtr addAfter (const T &val) noexcept
        @brief This function adds a CNode after
        @param[in] val This is the value of the CNode that you want to add
     */
    inline CNodePtr addAfter (const T &val) noexcept
    {
        CNodePtr newNode = std::make_shared<CNode> (val, m_next, m_next->m_previous);
        m_next->m_previous = newNode;
        m_next = newNode;
        return newNode;
    }
};
