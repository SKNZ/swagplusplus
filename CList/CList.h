#include <memory>

namespace nsSdD {
    template <class T>
    class CList {

    typedef int size_type;
    typedef std::unique_ptr<CNode> CNodePtr;

    private:
        CNodePtr m_head;
        CNodePtr m_tail;

    public:
        explicit CList() noexcept : m_head(new CNode()), m_tail(new CNode()) {}

        explicit CList(size_type n) noexcept
                : m_head(new CNode(T(), nullptr, nullptr)),
                  m_tail(new CNode(T(), nullptr, m_head)) {
            m_head->setNext(m_tail);

            for(size_type i = 0; i < n; i++) {
                CNodePtr ptr = new CNode();
                ptr->setNext(m_head->getNext());
                ptr->setPrevious(m_head->getNext()->getPrevious());
                m_head->setNext(ptr);
                m_tail->setPrevious(ptr);
            }
        }

        explicit CList(size_type n, const T& val) noexcept {
            
        }

        CNodePtr getHead() const noexcept { return m_head; }
        CNodePtr getTail() const noexcept { return m_tail; }

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