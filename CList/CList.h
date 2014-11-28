#include <memory>

namespace nsSdD {
    template <class T>
    class CList {

    typedef int size_type;
    typedef std::unique_ptr<CNode> CNodePtr;

    private:
        CNodePtr head;
        CNodePtr tail;

    public:
        explicit CList();
        explicit CList(size_type n);
        explicit CList(size_type n, const T& val);

        CNodePtr getHead() const noexcept;
        CNodePtr getTail() const noexcept;

        template <class T>
        class CNode {

        private:
            T info;
            CNodePtr m_next;
            CNodePtr previous;

            CNode(const CNode &);
            CNode& operator=(const CNode &);

        public:
            CNode(T info = T(), CNodePtr next = nullptr, CNodePtr previous = nullptr);

            inline T getInfo() const { return m_info; }
            inline void setInfo(T info) { m_info = info; }
            inline CNodePtr &getNext() const { return m_next; }
            inline void setNext(CNodePtr &next) { m_next = next; }
            inline CNodePtr &getPrevious() const { return m_previous; }
            inline void setPrevious(CNodePtr &previous) { m_previous = previous; }
        };
    };
}