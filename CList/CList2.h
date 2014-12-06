#ifndef __CLIST2_H__
#define __CLIST2_H__

#include <iterator>
#include <memory>

namespace nsSdD
{
    template<typename T>
    class CList
    {

    private:
        class CNode;
        typedef std::shared_ptr<CNode> CNodePtr;
        size_t m_size = 0;
        CNodePtr m_head = nullptr;
        CNodePtr m_tail = nullptr;

    public:
        typedef size_t size_type;

        class iterator;

        explicit CList() noexcept;

        explicit CList(size_t n) noexcept;

        explicit CList(size_t n, const T &val) noexcept;

        CList(const CList<T> &x) noexcept;

        inline CNodePtr getHead() const noexcept
        {
            return m_head;
        }

        inline CNodePtr getTail() const noexcept
        {
            return m_tail;
        }

        class iterator
        {

        private:
            CNodePtr node;

        public:
            typedef std::forward_iterator_tag iterator_category;
            typedef T value_type;
            typedef int difference_type;
            typedef T* pointer;
            typedef T& reference;

            iterator(CNodePtr p = nullptr) : node(p){}
            ~iterator(){}

            iterator& operator=(const iterator& other)
            {
                node = other.node;
                return (*this);
            }

            iterator& operator=(const T& other)
            {
                node->setInfo(other);
                return (*this);
            }

            bool operator==(const iterator& other)
            {
                return(node == other.node);
            }

            bool operator!=(const iterator& other)
            {
                return(node != other.node);
            }

            iterator& operator++()
            {
                if (node->getNext() != nullptr)
                {
                    node = node->getNext();
                }
                return(*this);
            }

            iterator& operator--()
            {
                if (node->getPrevious() != nullptr)
                {
                    node = node->getPrevious();
                }
                return(*this);
            }

            iterator& operator++(int)
            {
                iterator temp(*this);
                ++(*this);
                return(temp);
            }

            iterator& operator--(int)
            {
                iterator temp(*this);
                --(*this);
                return(temp);
            }

            T& operator*() const
            {
                return  node->m_info;
            }

            const CNodePtr operator->()
            {
                return (node);
            }

            CNodePtr getNode()
            {
                return node;
            }

        };

        class const_iterator
        {

        private:
            CNodePtr node;

        public:

            typedef std::forward_iterator_tag iterator_category;
            typedef T value_type;
            typedef int difference_type;
            typedef T* pointer;
            typedef T& reference;

            const_iterator(CNodePtr p = nullptr) : node(p){}
            ~const_iterator(){}

            const_iterator& operator=(const const_iterator& other)
            {
                node = other.node;
                return (*this);
            }

            bool operator==(const const_iterator& other)
            {
                return node == other.node;
            }

            bool operator!=(const const_iterator& other)
            {
                return(node != other.node);
            }

            const_iterator& operator++()
            {
               // if (node->getNext() != nullptr)
                {
                    node = node->getNext();
                }
                return(*this);
            }

            const_iterator& operator--()
            {
                if (node->getPrevious() != nullptr)
                {
                    node = node->getPrevious();
                }
                return(*this);
            }

            const_iterator& operator++(int)
            {
                const_iterator temp(*this);
                ++(*this);
                return(temp);
            }

            const_iterator& operator--(int)
            {
                const_iterator temp(*this);
                --(*this);
                return(temp);
            }

            const T operator*() const
            {
                return node->getInfo();
            }

            const CNodePtr operator->()
            {
                return node;
            }

        };

        class reverse_iterator
        {

        private:
            iterator it;

        public:

            typedef std::forward_iterator_tag iterator_category;
            typedef T value_type;
            typedef int difference_type;
            typedef T* pointer;
            typedef T& reference;

            reverse_iterator(iterator i ) : it(i){}
            reverse_iterator():it(NULL){}
            ~reverse_iterator(){}

            iterator base() const
            {
                iterator ittmp = it;
                return --ittmp;
            }

            reverse_iterator operator++()
            {
                return reverse_iterator(--it);
            }

            reverse_iterator operator--()
            {
                return reverse_iterator(++it);
            }

            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                ++*this;
                return tmp;
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                --*this;
                return tmp;
            }

            bool operator==(const reverse_iterator & other)
            {
                return it == other.it;
            }

            bool operator!=(const reverse_iterator & other)
            {
                return it != other.it;
            }

            T& operator*() const
            {
                return *it;
            }

            reverse_iterator& operator=(const T& other)
            {
                it->setInfo(other);
                return (*this);
            }


        };

        class const_reverse_iterator
        {

            private:
            const_iterator it;

            public:

            typedef std::forward_iterator_tag iterator_category;
            typedef T value_type;
            typedef int difference_type;
            typedef T* pointer;
            typedef T& reference;

            const_reverse_iterator(const_iterator i ) : it(i){}
            const_reverse_iterator():it(NULL){}
            ~const_reverse_iterator(){}

            const_reverse_iterator base() const
            {
                const_reverse_iterator ittmp = it;
                return --ittmp;
            }

            const_reverse_iterator operator++()
            {
                return const_reverse_iterator(--it);
            }

            const_reverse_iterator operator--()
            {
                return const_reverse_iterator(++it);
            }

            const_reverse_iterator operator++(int)
            {
                const_reverse_iterator tmp = *this;
                ++*this;
                return tmp;
            }

            const_reverse_iterator operator--(int)
            {
                const_reverse_iterator tmp = *this;
                --*this;
                return tmp;
            }

            bool operator==(const const_reverse_iterator & other)
            {
                return it == other.it;
            }

            bool operator!=(const const_reverse_iterator & other)
            {
                return it != other.it;
            }

            const T operator*() const
            {
                return *it;
            }

        };

        // Iterators

        iterator begin()
        {
            return iterator(m_head->getNext());
        }

        iterator end()
        {
            return iterator(m_tail);
        }

        reverse_iterator rbegin()
        {
            return CList::reverse_iterator(m_tail->getPrevious());
        }

        reverse_iterator rend()
        {
            return CList::reverse_iterator(m_head);
        }

        const_iterator cbegin() const
        {
            return const_iterator(m_head->getNext());
        }

        const_iterator cend() const
        {
            return const_iterator(m_tail->getPrevious());
        }

        const_reverse_iterator crbegin()
        {
            return const_reverse_iterator(m_tail->getPrevious());
        }

        const_reverse_iterator crend()
        {
            return const_reverse_iterator(m_head);
        }

        // Capacity

        inline bool empty() const noexcept
        {
            return m_size == 0;
        }

        inline size_t size() const noexcept
        {
            return m_size;
        }

        // Element access

        inline T front() noexcept
        {
            return m_head->getNext()->getInfo();
        }

        inline T back() noexcept
        {
            return m_tail->getPrevious()->getInfo();
        }

        // Modifiers

        void assign(unsigned n, const T& val) noexcept;

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last);

        void emplace_back(T val) noexcept;

        void push_back(const T& x) noexcept;

        void pop_back() noexcept;

        template <class... Args>
        void emplace_front(Args&&... val) noexcept;

        void push_front(const T& x) noexcept;

        void pop_front() noexcept;

        void emplace(CNodePtr Prec , T val) noexcept;

        iterator insert (iterator position, const T& val) noexcept;

        iterator erase(iterator del) noexcept;

        void swap(CList& x) noexcept;

        void resize(unsigned n, const T& val = T()) noexcept;

        void clear() noexcept;

        // Operations

        void remove(const T& val) noexcept;

        template<class Predicate>
        void remove_if(Predicate pred) noexcept;

        void reverse() noexcept;

    private:

        class CNode
        {
        public:
            T m_info;
        private:

            CNodePtr m_next;
            CNodePtr m_previous;

            CNode(const CNode &) noexcept
            {
            }

            CNode &operator=(const CNode &) noexcept
            {
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

            inline T getInfo() noexcept
            {
                return m_info;
            }

            inline void setInfo(T info) noexcept
            {
                m_info = info;
            }

            inline CNodePtr &getNext()  noexcept
            {
                return m_next;
            }

            inline void setNext(CNodePtr next) noexcept
            {
                m_next = next;
            }

            inline CNodePtr &getPrevious()  noexcept
            {
                return m_previous;
            }

            inline void setPrevious(CNodePtr previous) noexcept
            {
                m_previous = previous;
            }
        };
    };
}

#include "CList2.hxx"

#endif