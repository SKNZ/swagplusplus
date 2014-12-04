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

        inline size_t size() const noexcept
        {
            return m_size;
        }

        inline bool empty() const noexcept
        {
            return m_size;
        }

        inline T front() noexcept
        {
            return m_head->getNext()->getInfo();
        }

        inline T back() noexcept
        {
            return m_tail->getNext()->getInfo();
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
                return node->getInfo();
            }

            T* operator->()
            {
                return *this;
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
                return(node == other.node);
            }

            bool operator!=(const const_iterator& other)
            {
                return(node != other.node);
            }

            const_iterator& operator++()
            {
                if (node->getNext() != nullptr)
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

            const T* operator->()
            {
                return *this;
            }

        };

        iterator begin()
        {
            return iterator(m_head);
        }

        iterator end()
        {
            return iterator(m_tail);
        }


        const_iterator cbegin() const
        {
            return const_iterator(m_head);
        }

        const_iterator cend() const
        {
            return const_iterator(m_tail);
        }

        iterator rbegin()
        {
            return iterator(m_tail);
        }

        iterator rend()
        {
            return iterator(m_head);
        }

        void push_back(const T& x)
        {
            CNodePtr add = std::make_shared<CNode>(x, nullptr, nullptr);
            CNodePtr LastCreated = m_tail->getPrevious();

            add->setNext(m_tail);
            add->setPrevious(LastCreated);

            LastCreated->setNext(add);
            m_tail->setPrevious(add);

            ++m_size;
        }

        void pop_front()
        {
            CNodePtr del = m_head->getNext();
            m_head->setNext(del->getNext());

            (del->getNext())->setPrevious(m_head);

            del->setPrevious(nullptr);
            del->setNext(nullptr);
        }

    private:

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



#endif