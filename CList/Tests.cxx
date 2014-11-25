#include "Tests.h"
#include "IziAssert.h"

#include <memory>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

using namespace nsTests;
using namespace std;

namespace
{
    int rand(int min, int max)
    {
        return min + (std::rand() % (max - min + 1));
    }

    class TestClass
    {
    public:
        TestClass(int a = 0, const char* name = "ALAIN CASALOL") noexcept : m_a(a), m_name(name) { }

        bool operator ==(const TestClass& c)
        {
            return m_a == c.m_a && m_name == c.m_name; // TODO USE STRCMP
        }

    private:
        int m_a;
        const char* m_name;
    };

    template<typename T>
    class ValueProvider
    {
    public:
        vector<T> operator ()()
        {
            throw runtime_error("Value provider for this type has not been provided.");
        }
    };

    template<>
    class ValueProvider<int>
    {
    public:
        vector<int> operator ()() noexcept
        {
            int arraySize = rand(0,100);
            int* array = new int[arraySize];
            array[0] = 0;
            array[1] = std::numeric_limits<int>::max();
            array[2] = std::numeric_limits<int>::min();

            for (int i = 3; i < arraySize; ++i)
                array[i] = std::rand();
        }
    };

    template<typename T>
    void CreateEmptyList() noexcept
    {
        CTestedList<T> list;
        IZI_ASSERT(list.size() == 0);
        IZI_ASSERT(list.empty());
        IZI_ASSERT(list.begin() == list.end());
    }

    template<typename T>
    void CreateSizedList() noexcept
    {
        int listSize = rand(1, 10000);

        CTestedList<T> list(listSize);

        IZI_ASSERT(list.size() == listSize);
        IZI_ASSERT(!list.empty());
        IZI_ASSERT(list.begin() != list.end());

        for (T x : list)
            IZI_ASSERT(x == T());
    }

    template<typename T>
    void CreateSizeListWithValue(T value)
    {
        int listSize = rand(1, 10000);

        CTestedList<T> list(listSize, value);

        IZI_ASSERT(list.size() == listSize);
        IZI_ASSERT(!list.empty());
        IZI_ASSERT(list.begin() != list.end());

        for (T x : list)
            IZI_ASSERT(x == value)
    }

    template<typename T>
    void AddItemsToList()
    {
        CTestedList<T> list;
//        list.push_back();
    }

    template <typename T>
    void RunTemplatedTests() noexcept
    {
        CreateEmptyList<T>();
        CreateSizedList<T>();
        
        for (T x : ValueProvider<T>()())
            CreateSizeListWithValue<T>(x);
    }
}

void CTests::RunTests() noexcept
{
    srand(time(NULL));
    RunTemplatedTests<int>();
    RunTemplatedTests<int*>();
    RunTemplatedTests<shared_ptr<int>>();

    RunTemplatedTests<TestClass>();
    RunTemplatedTests<TestClass*>();
    RunTemplatedTests<shared_ptr<TestClass>>();
}
