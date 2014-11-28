#include "Tests.h"
#include "IziAssert.h"

#include <memory>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include <string.h>

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
            return m_a == c.m_a && !strcmp(m_name, c.m_name);
        }

        int getA()
        {
            return m_a;
        }

        const char* getName()
        {
            return m_name;
        }

    private:
        int m_a;
        const char* m_name;
    };

    template<typename T>
    class ValueProvider
    {
    public:
        vector<T> operator ()(int /*valueCount*/ = 0)
        {
            // typeid(T).name() only gives mangled class name, not very clear but still a good indication.
            throw runtime_error(string("Value provider for type ") + typeid(T).name() + " does not exist.");
        }
    };

    template<typename T>
    class ValueProvider<T*>
    {
    public:
        vector<T*> operator ()(int /*valueCount*/ = 0)
        {
            vector<T> array = ValueProvider<T>()();
            vector<T*> ptrArray;
            ptrArray.reserve(array.size());

            for (T x : array)
                ptrArray.push_back(new T(x));

            return ptrArray;
        }
    };

    template<typename T>
    class ValueProvider<shared_ptr<T>>
    {
    public:
        vector<shared_ptr<T>> operator ()(int/* valueCount*/ = 0)
        {
            vector<T> array = ValueProvider<T>()();
            vector<shared_ptr<T>> ptrArray;
            ptrArray.reserve(array.size());

            for (T x : array)
                ptrArray.push_back(make_shared<T>(x));

            return ptrArray;
        }
    };

    template<>
    class ValueProvider<int>
    {
    public:
        vector<int> operator ()(int valueCount = 0) noexcept
        {
            int arraySize = valueCount ? valueCount : rand(10, 100);
            vector<int> array(arraySize);

            array[0] = 0;
            array[1] = std::numeric_limits<int>::max();
            array[2] = std::numeric_limits<int>::min();

            for (int i = 3; i < arraySize; ++i)
                array[i] = std::rand();

            return array;
        }
    };

    template<>
    class ValueProvider<TestClass>
    {
    public:
        vector<TestClass> operator()(int valueCount = 0) noexcept
        {
            int arraySize = valueCount ? valueCount : rand(10, 100);
            vector<TestClass> array(arraySize);

            array[0] = TestClass(4654, "MARQUE LA PORTE");

            for (int i = 1; i < arraySize; ++i)
            {
                int nameSize = rand(10, 20);
                char* name = new char[nameSize];
                for (int j = 0; j < nameSize; ++j)
                    name[j] = rand(65, 90);

                array[i] = TestClass(std::rand(), name);

                cout << array[i].getName() << endl;
            }

            return array;
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
        int listSize = rand(1, 10);

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
        int listSize = rand(1, 10);

        CTestedList<T> list(listSize, value);

        IZI_ASSERT(list.size() == listSize);
        IZI_ASSERT(!list.empty());
        IZI_ASSERT(list.begin() != list.end());

        for (T x : list)
            IZI_ASSERT(x == value)
    }

    template<typename T>
    void CreateListByCopy() noexcept
    {
        int listSize = rand(1, 10000);

        CTestedList<T> referenceList;
        for (T x : ValueProvider<T>()(listSize))
            referenceList.push_back(x);

        CTestedList<T> copiedList(referenceList);

        IZI_ASSERT(referenceList.size() == copiedList.size());

        while (!referenceList.empty())
        {
            IZI_ASSERT(referenceList.front() == copiedList.front());
            referenceList.pop_front();
            copiedList.pop_front();
        }
    }

    template <typename T>
    void RunTemplatedTests() noexcept
    {
        CreateEmptyList<T>();
        CreateSizedList<T>();
        
        for (T x : ValueProvider<T>()(5))
            CreateSizeListWithValue<T>(x);

        CreateListByCopy<T>();
    }
}

void CTests::RunTests() noexcept
{
    cout << "Starting tests..." << endl << endl;

    srand(time(NULL));
    IZI_CALLTEST(RunTemplatedTests<int>());
    IZI_CALLTEST(RunTemplatedTests<int*>());
    IZI_CALLTEST(RunTemplatedTests<shared_ptr<int>>());

    IZI_CALLTEST(RunTemplatedTests<TestClass>());
    IZI_CALLTEST(RunTemplatedTests<TestClass*>());
    IZI_CALLTEST(RunTemplatedTests<shared_ptr<TestClass>>());

    cout << "Tests done..." << endl << endl;
}
