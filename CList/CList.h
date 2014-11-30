#include <memory>

namespace nsSdD
{
    template <class T>
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
        explicit CList() noexcept : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
                                    m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
        {
            m_head->setNext(m_tail);
        }

        explicit CList(size_t n) noexcept
                : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
                  m_tail(std::make_shared<CNode>(T(), nullptr, m_head)) {
            m_head->setNext(m_tail);

            for(size_t i = 0; i < n; i++) {
                CNodePtr ptr = std::make_shared<CNode>(T(), nullptr, nullptr);

                ptr->setNext(m_tail);
                ptr->setPrevious(m_tail->getPrevious());

                m_tail->getPrevious()->setNext(ptr);
                m_tail->setPrevious(ptr);

                ++m_size;
            }
        }

        explicit CList(size_t n, const T& val) noexcept
                : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
                  m_tail(std::make_shared<CNode>(T(), nullptr, m_head)) {
            m_head->setNext(m_tail);

            for(size_t i = 0; i < n; i++) {
                CNodePtr ptr = std::make_shared<CNode>(val, nullptr, nullptr);
                CNodePtr LastCreated = m_tail->getPrevious();

                ptr->setNext(m_tail);
                ptr->setPrevious(LastCreated);

                LastCreated->setNext(ptr);
                m_tail->setPrevious(ptr);

                ++m_size;
            }
        }

        CList(const CList<T>& x)
        {
            this->m_head = x.getHead();
            this->m_tail = x.getTail();
            this->m_size = x.size();

            for(CNodePtr p = x.getHead(); p; p = p->getNext())
            {
                CNodePtr temp = std::make_shared<CNode>(p->getInfo(),p->getNext(),p->getPrevious());
            }
        }

        CNodePtr getHead() const noexcept { return m_head; }
        CNodePtr getTail() const noexcept { return m_tail; }

        size_t size() const noexcept { return m_size; }
        bool empty() const noexcept { return m_size; }
        T front() { return m_size ? m_head->getNext()->getInfo() : NULL; }
        T back() { return m_size ? m_tail->getNext()->getInfo() : NULL; }


        class CNode {
        private:
            T m_info;
            CNodePtr m_next;
            CNodePtr m_previous;

            CNode(const CNode &) noexcept {}
            CNode& operator=(const CNode &) noexcept {}

        public:
            CNode(T info = T(), CNodePtr next = nullptr, CNodePtr previous = nullptr) noexcept
                    : m_info(info), m_next(next),
                      m_previous(previous) {}

            ~CNode() noexcept {}

            inline T getInfo() const noexcept { return m_info; }
            inline void setInfo(T info) noexcept { m_info = info; }
            inline CNodePtr & getNext()  noexcept { return m_next; }
            inline void setNext(CNodePtr &next) noexcept { m_next = next; }
            inline CNodePtr & getPrevious()  noexcept { return m_previous; }
            inline void setPrevious(CNodePtr &previous) noexcept { m_previous = previous; }
        };
    };
}
