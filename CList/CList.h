#include <memory>

namespace nsSdD {
    template <class T>
    class CList {
        
    typedef std::unique_ptr<CNode> CNodePtr;

    private:
        size_t m_size = 0;
        CNodePtr m_head = NULL;
        CNodePtr m_tail = NULL;

    public:
        explicit CList() noexcept: m_head(new CNode(T(), nullptr, nullptr)),
                                   m_tail(new CNode(T(), nullptr, m_head)) {
            m_head->setNext(m_tail);
        }

        explicit CList(size_t n) noexcept
                : m_head(new CNode(T(), nullptr, nullptr)),
                  m_tail(new CNode(T(), nullptr, m_head)) {
            m_head->setNext(m_tail);

            CNodePtr tmp_head = m_head;
            for(size_t i = 0; i < n; i++) {
                CNodePtr ptr = new CNode(T(), nullptr, nullptr);

                ptr->setNext(tmp_head->getNext());
                ptr->setPrevious(tmp_head->getNext()->getPrevious());

                tmp_head->setNext(ptr);
                m_tail->setPrevious(ptr);

                tmp_head = ptr;
                ++m_size;
            }
        }

        explicit CList(size_t n, const T& val) noexcept
                : m_head(new CNode(T(), nullptr, nullptr)),
                  m_tail(new CNode(T(), nullptr, m_head)) {
            m_head->setNext(m_tail);

            CNodePtr tmp_head = m_head;
            for(size_t i = 0; i < n; i++) {
                CNodePtr ptr = new CNode(T(val), nullptr, nullptr);

                ptr->setNext(tmp_head->getNext());
                ptr->setPrevious(tmp_head->getNext()->getPrevious());

                tmp_head->setNext(ptr);
                m_tail->setPrevious(ptr);

                tmp_head = ptr;
                ++m_size;
            }
        }

        CNodePtr getHead() const noexcept { return m_head; }
        CNodePtr getTail() const noexcept { return m_tail; }

        size_t size() const noexcept { return m_size; }
        bool empty() const noexcept { return m_size; }
        T front() { return m_size ? m_head->getNext()->getInfo() : NULL; }
        T back() { return m_size ? m_tail->getNext()->getInfo() : NULL; }



        template <class T>
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
            inline CNodePtr &getNext() const noexcept { return m_next; }
            inline void setNext(CNodePtr &next) noexcept { m_next = next; }
            inline CNodePtr &getPrevious() const noexcept { return m_previous; }
            inline void setPrevious(CNodePtr &previous) noexcept { m_previous = previous; }
        };
    };
}