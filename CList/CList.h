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
            return m_size;
        }

        T &front() noexcept
        {
            return m_head->getNext()->getInfo();
        }

        T &back() noexcept
        {
            return m_tail->getNext()->getInfo();
        }

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

            inline void setNext(CNodePtr &next) noexcept
            {
                m_next = next;
            }

            inline CNodePtr &getPrevious()  noexcept
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
