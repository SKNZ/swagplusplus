#include <memory>

namespace nsSdD {
    template <class T>
    class CList {

        typedef std::shared_ptr<CNode> CNode_ptr;

    private:
        CNode_ptr next;
        CNode_ptr previous;

    public:
        explicit CList();
        explicit CList(T n);
        explicit CList(T n, const T& val);

        CNode_ptr getNext() const noexcept;
        CNode_ptr getPrevious() const noexcept;
    };
}