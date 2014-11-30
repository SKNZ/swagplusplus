#include "Tests.h"
#include "IziAssert.h"

#include <memory>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include <algorithm>
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
        TestClass(int a = 0, const string& name = "ALAIN CASALOL") noexcept : m_a(a), m_name(name) { }

        bool operator ==(const TestClass& c) const noexcept
        {
            return m_a == c.m_a && m_name == c.m_name;
        }

        int getA() const noexcept
        {
            return m_a;
        }

        string getName() const noexcept
        {
            return m_name;
        }

    private:
        int m_a;
        string m_name;
    };

    std::ostream &operator<<(std::ostream &os, TestClass const &p) {
        return os << "PERS. " << p.getName() << ". " << p.getA();
    }

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
            cout << "TProv " << valueCount << " " << arraySize << endl;
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
                string name;
                for (int j = 0; j < rand(10, 20); ++j)
                    name += static_cast<char>(rand(66, 89));

                array[i] = TestClass(rand(0, 30), name);
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
    void CreateSizeListWithValue(T value) noexcept
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
    void CreateListByExplicitCopy() noexcept
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

    template<typename T>
    void CreateListByImplicitCopy() noexcept
    {
        int listSize = rand(1, 10000);

        CTestedList<T> referenceList;
        for (T x : ValueProvider<T>()(listSize))
            referenceList.push_back(x);

        CTestedList<T> copiedList = referenceList;

        IZI_ASSERT(referenceList.size() == copiedList.size());

        while (!referenceList.empty())
        {
            IZI_ASSERT(referenceList.front() == copiedList.front());
            referenceList.pop_front();
            copiedList.pop_front();
        }
    }

    template<typename T>
    void Iterate() noexcept
    {
        const int listSize = 20;

        CTestedList<T> list;
        vector<T> t = ValueProvider<T>()(listSize);
        vector<T> originalData(t.begin(), t.begin() + listSize / 2);
        vector<T> newData(t.begin() + listSize / 2, t.end());

        for (T x : originalData)
            list.push_back(x);

        typename CTestedList<T>::iterator begin = list.begin();
        typename CTestedList<T>::iterator end = list.end();

        for (; begin != end; ++begin)
        {
            int i = distance(list.begin(), begin);
            IZI_ASSERT(originalData[i] == *begin);
            *begin = newData[i];
            IZI_ASSERT(newData[i] == *begin);
        }

        IZI_ASSERT(begin == end);
    }

    template<typename T>
    void ConstIterate() noexcept
    {
        const int listSize = 20;

        CTestedList<T> list;
        vector<T> t = ValueProvider<T>()(listSize);
        for (T x : t)
            list.push_back(x);

        typename CTestedList<T>::const_iterator cbegin = list.cbegin();
        typename CTestedList<T>::const_iterator cend = list.cend();

        for (; cbegin != cend; ++cbegin)
            IZI_ASSERT(t[distance(list.cbegin(), cbegin)] == *cbegin);

        IZI_ASSERT(cbegin == cend);
    }

    template<typename T>
    void ReverseIterate() noexcept
    {
        const int listSize = 20;

        CTestedList<T> list;
        vector<T> t = ValueProvider<T>()(listSize);
        vector<T> originalData(t.begin(), t.begin() + listSize / 2);
        vector<T> newData(t.begin() + listSize / 2, t.end());

        cout << listSize << " " << t.size() << " " << originalData.size() << " " << newData.size() << endl;

        for (T x : originalData)
            list.push_back(x);

        reverse(originalData.begin(), originalData.end());
        reverse(newData.begin(), newData.end());

        typename CTestedList<T>::reverse_iterator rbegin = list.rbegin();
        typename CTestedList<T>::reverse_iterator rend = list.rend();

        for (; rbegin != rend; ++rbegin)
        {
            int i = distance(list.rbegin(), rbegin);
            IZI_ASSERT(originalData[i] == *rbegin);
            *rbegin = newData[i];
            IZI_ASSERT(newData[i] == *rbegin);
        }

        IZI_ASSERT(rbegin == rend);
    }

    template<typename T>
    void ReverseConstIterate() noexcept
    {const int listSize = 20;

        CTestedList<T> list;
        vector<T> t = ValueProvider<T>()(listSize);
        for (T x : t)
            list.push_back(x);

        reverse(t.begin(), t.end());

        typename CTestedList<T>::const_reverse_iterator crbegin = list.crbegin();
        typename CTestedList<T>::const_reverse_iterator crend = list.crend();

        for (; crbegin != crend; ++crbegin)
            IZI_ASSERT(t[distance(list.crbegin(), crbegin)] == *crbegin);

        IZI_ASSERT(crbegin == crend);
    }

    template <typename T>
    void RunTemplatedTests() noexcept
    {
        CreateEmptyList<T>();
        CreateSizedList<T>();

        for (T x : ValueProvider<T>()(5))
            CreateSizeListWithValue<T>(x);

        CreateListByExplicitCopy<T>();
        CreateListByImplicitCopy<T>();

        Iterate<T>();
        ConstIterate<T>();
        ReverseIterate<T>();
        ReverseConstIterate<T>();
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
