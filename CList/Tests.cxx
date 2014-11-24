#include "Tests.h"
#include "IziAssert.h"

#include <memory>

using namespace nsTests;
using namespace std;

namespace
{
    template<typename T>
    void CreateEmptyList() noexcept
    {
        CTestedList<T> list;
        IZI_ASSERT(list.size() == 0);
        IZI_ASSERT(list.empty());
        IZI_ASSERT(list.begin() == list.end());
    }

    template <typename T>
    void RunTemplatedTests() noexcept
    {
        CreateEmptyList<T>();
    }

    class TestClass
    {
    public:
        TestClass(int a = 0) noexcept : m_a(a) { }

    private:
        int m_a;
    };
}

void CTests::RunTests() noexcept
{
    RunTemplatedTests<int>();
    RunTemplatedTests<int*>();
    RunTemplatedTests<shared_ptr<int>>();
    RunTemplatedTests<TestClass>();
    RunTemplatedTests<TestClass*>();
    RunTemplatedTests<shared_ptr<TestClass>>();
}
