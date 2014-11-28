#include <memory>

namespace nsSdD {
    template <class T>
    class CList {

    typedef std::shared_ptr<CNode> CNode_ptr;
    typedef int size_type;

    private:
        CNode_ptr next;
        CNode_ptr previous;

    public:
        explicit CList();
        explicit CList(size_type n);
        explicit CList(size_type n, const T& val);

        CNode_ptr getNext() const noexcept;
        CNode_ptr getPrevious() const noexcept;
    };
}