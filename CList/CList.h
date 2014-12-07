#pragma once

#include <memory>

namespace nsSdD
{
    template<typename T>
    class CList
    {
      public:
        class CNode;

      private:
        typedef std::shared_ptr<CNode> CNodePtr;
        size_t m_size = 0;
        CNodePtr m_head = nullptr;
        CNodePtr m_tail = nullptr;

      public:
        explicit CList() noexcept;

        explicit CList(size_t n) noexcept;

        explicit CList(size_t n, const T &val) noexcept;

        CList(const CList<T> &x) noexcept;

        CNodePtr getHead() const noexcept
        {
            return m_head;
        }

        CNodePtr getTail() const noexcept
        {
            return m_tail;
        }

        size_t size() const noexcept
        {
            return m_size;
        }

        bool empty() const noexcept
        {
          return (bool) m_size;
        }

        T &front() noexcept
        {
            return m_head->getNext()->getInfo();
        }

        T &back() noexcept
        {
            return m_tail->getNext()->getInfo();
        }

      void assign (unsigned n, const T &val) noexcept;

        void emplace_front(T val) noexcept;

      void push_back (const T &x) noexcept;

        void pop_back() noexcept;

      void push_front (const T &x) noexcept;

        void pop_front() noexcept;

      void emplace (CNodePtr Prec, T val) noexcept;

        void erase(CNodePtr del) noexcept;

      void swap (CList &x) noexcept;

      void resize (unsigned n, const T &val = T ()) noexcept;

        void clear() noexcept;

      void remove (const T &val) noexcept;

        void reverse() noexcept;

        template<class Predicate>
        void remove_if(Predicate pred) noexcept;

        class CNode
        {
          private:
            T m_info;
            CNodePtr m_next;
            CNodePtr m_previous;

            CNode(const CNode &) noexcept
            {
            }

            CNode &operator=(const CNode &) noexcept
            {
              // @todo Should this really be empty ?
            }

          public:
            CNode(T info = T(), CNodePtr next = nullptr, CNodePtr previous = nullptr) noexcept
                    : m_info(info), m_next(next),
                      m_previous(previous)
            {
            }

            ~CNode() noexcept
            {
            }

            inline T getInfo() const noexcept
            {
                return m_info;
            }

            inline void setInfo(T info) noexcept
            {
                m_info = info;
            }

            inline CNodePtr getNext()  noexcept
            {
              return m_next;
            }

            inline void setNext(CNodePtr &next) noexcept
            {
                m_next = next;
            }

            inline CNodePtr getPrevious()  noexcept
            {
              return m_previous;
            }

            inline void setPrevious(CNodePtr &previous) noexcept
            {
                m_previous = previous;
            }


        };
    };
}
