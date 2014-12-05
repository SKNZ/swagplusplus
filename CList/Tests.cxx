#include "Tests.h"
#include "IziAssert.h"
#include "CList2.h"

#include <memory>
#include <ctime>
#include <limits>
#include <vector>
#include <algorithm>

using namespace nsTests;
using namespace std;
using namespace nsSdD;

namespace
{
    // C++11 c'est bon, mangez en.
    template<typename T> using CCollection = vector<T>;
    //template<typename T> using CTestedList = list<T>;
    template<typename T> using CTestedList = CList<T>;

    int rand(int min, int max)
    {
        return min + (std::rand() % (max - min + 1));
    }

    class TestClass
    {
    public:
        TestClass(int a = 0, const string &name = "ALAIN CASALOL") noexcept : m_a(a), m_name(name)
        {
        }

        bool operator==(const TestClass &c) const noexcept
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
    class CValueProvider
    {
    public:
        CCollection<T> operator()(const int /*valueCount*/ = 0)
        {
            // typeid(T).name() only gives mangled class name, not very clear but still a good indication.
            throw runtime_error(string("Value provider for type ") + typeid(T).name() + " does not exist.");
        }
    };

    template<typename T>
    class CValueProvider<T *>
    {
    public:
        CCollection<T *> operator()(const int valueCount = 0)
        {
            CCollection<T> array = CValueProvider<T>()(valueCount);
            CCollection<T *> ptrArray;
            ptrArray.reserve(array.size());

            for (T x : array)
                ptrArray.push_back(new T(x));

            return ptrArray;
        }
    };

    template<typename T>
    class CValueProvider<shared_ptr<T>>
    {
    public:
        CCollection<shared_ptr<T>> operator()(const int valueCount = 0)
        {
            CCollection<T> array = CValueProvider<T>()(valueCount);
            CCollection<shared_ptr<T>> ptrArray;
            ptrArray.reserve(array.size());

            for (T x : array)
                ptrArray.push_back(make_shared<T>(x));

            return ptrArray;
        }
    };

    template<>
    class CValueProvider<int>
    {
    public:
        CCollection<int> operator()(const int valueCount = 0) noexcept
        {
            int arraySize = valueCount ? valueCount : rand(10, 100);

            CCollection<int> array(arraySize);

            array[0] = 0;
            array[1] = std::numeric_limits<int>::max();
            array[2] = std::numeric_limits<int>::min();

            for (int i = 3; i < arraySize; ++i)
                array[i] = std::rand();

            return array;
        }
    };

    template<>
    class CValueProvider<TestClass>
    {
    public:
        CCollection<TestClass> operator()(const int valueCount = 0) noexcept
        {
            int arraySize = valueCount ? valueCount : rand(10, 100);
            CCollection<TestClass> array;
            array.reserve(arraySize);

            array.push_back(TestClass(4654, "MARQUE LA PORTE"));

            for (int i = array.size(); i < arraySize; ++i)
            {
                string name;
                for (int j = 0; j < rand(10, 20); ++j)
                    name += static_cast<char>(rand(66, 89));

                array.push_back(TestClass(rand(0, 30), name));
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
        typename CTestedList<T>::size_type listSize = rand(1, 10);

        CTestedList<T> list(listSize);

        IZI_ASSERT(list.size() == listSize);
        IZI_ASSERT(!list.empty());
        IZI_ASSERT(list.begin() != list.end());

        for (T x : list)
            IZI_ASSERT(x == T());
    }

    template<typename T>
    void CreateSizeListWithValue(const T& value) noexcept
    {
        typename CTestedList<T>::size_type listSize = rand(1, 10);

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
        typename CTestedList<T>::size_type listSize = rand(1, 10000);

        CTestedList<T> referenceList;
        for (T x : CValueProvider<T>()(listSize))
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
        typename CTestedList<T>::size_type listSize = rand(1, 10000);

        CTestedList<T> referenceList;
        for (T x : CValueProvider<T>()(listSize))
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
        const typename CTestedList<T>::size_type listSize = 20;

        CTestedList<T> list;
        CCollection<T> t = CValueProvider<T>()(listSize);
        CCollection<T> originalData(t.begin(), t.begin() + listSize / 2);
        CCollection<T> newData(t.begin() + listSize / 2, t.end());

        for (T x : originalData)
            list.push_back(x);

        typename CTestedList<T>::iterator begin = list.begin();
        typename CTestedList<T>::iterator end = list.end();

        for (; begin != end; ++begin)
        {
            int i = distance(list.begin(), begin);
            IZI_ASSERT(originalData[i] == *begin);
            begin = newData[i];
            IZI_ASSERT(newData[i] == *begin);
        }

        IZI_ASSERT(begin == end);
    }

    template<typename T>
    void ConstIterate() noexcept
    {
        const typename CTestedList<T>::size_type listSize = 20;

        CTestedList<T> list;
        CCollection<T> t = CValueProvider<T>()(listSize);
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
        const typename CTestedList<T>::size_type listSize = 20;

        CTestedList<T> list;
        CCollection<T> t = CValueProvider<T>()(listSize);
        CCollection<T> originalData(t.begin(), t.begin() + listSize / 2);
        CCollection<T> newData(t.begin() + listSize / 2, t.end());

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
    {
        const typename CTestedList<T>::size_type listSize = 20;

        CTestedList<T> list;
        CCollection<T> t = CValueProvider<T>()(listSize);
        for (T x : t)
            list.push_back(x);

        reverse(t.begin(), t.end());

        typename CTestedList<T>::const_reverse_iterator crbegin = list.crbegin();
        typename CTestedList<T>::const_reverse_iterator crend = list.crend();

        for (; crbegin != crend; ++crbegin)
            IZI_ASSERT(t[distance(list.crbegin(), crbegin)] == *crbegin);

        IZI_ASSERT(crbegin == crend);
    }

    template<typename T>
    void IsEmpty() noexcept
    {
        CTestedList<T> list;

        IZI_ASSERT(list.empty());
        list.push_back(T());
        IZI_ASSERT(!list.empty());
        list.pop_front();
        IZI_ASSERT(list.empty());
    }

    template<typename T>
    void Size() noexcept
    {
        CTestedList<T> list;

        IZI_ASSERT(0 == list.size());

        list.push_front(T());
        IZI_ASSERT(1 == list.size());

        list.pop_back();
        IZI_ASSERT(0 == list.size());
    }

    template<typename T>
    void Front() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.push_back(x);

        IZI_ASSERT(list.front() == *data.begin());
    }

    template<typename T>
    void Back() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.push_back(x);

        IZI_ASSERT(list.back() == *--data.end());
    }

    template<typename T>
    void AssignByIterator() noexcept
    {
        const int listSize = 10;

        CTestedList<T> list(2 * listSize, T());
        CCollection<T> data = CValueProvider<T>()(listSize);

        list.assign(data.cbegin(), data.cend());

        IZI_ASSERT(data.size() == list.size());

        for (auto itr = list.cbegin(); itr != list.cend(); ++itr)
            IZI_ASSERT(*itr == data[distance(list.cbegin(), itr)]);
    }

    template<typename T>
    void AssignByValue(const T& x) noexcept
    {
        const int listSize = 10;

        CTestedList<T> list;
        list.assign(listSize, x);

        IZI_ASSERT(listSize == list.size());
        for (T val : list)
            IZI_ASSERT(val == x);
    }

    template<typename T>
    void EmplaceFront() noexcept
    {
        CTestedList<pair<T, T>> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.emplace_front(x, x);

        reverse(list.begin(), list.end());

        for (auto itr = list.cbegin(); itr != list.cend(); ++itr)
        {
            int i = distance(list.cbegin(), itr);
            IZI_ASSERT(make_pair(data[i], data[i]) == *itr)
        }

        IZI_ASSERT(list.size() == data.size());
    }

    template<typename T>
    void EmplaceBack() noexcept
    {
        CTestedList<pair<T, T>> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.emplace_back(x, x);

        for (auto itr = list.cbegin(); itr != list.cend(); ++itr)
        {
            int i = distance(list.cbegin(), itr);
            IZI_ASSERT(make_pair(data[i], data[i]) == *itr)
        }

        IZI_ASSERT(list.size() == data.size());
    }

    template<typename T>
    void Emplace() noexcept
    {
        CTestedList<pair<T, T>> list;
        CCollection<T> data = CValueProvider<T>()(5);

        list.push_back(make_pair(data[0], data[0]));
        list.push_back(make_pair(data[1], data[1]));
        list.push_back(make_pair(data[3], data[3]));
        list.push_back(make_pair(data[4], data[4]));

        auto itr = list.begin();
        advance(itr, 2);
        itr = list.emplace(itr, data[2], data[2]);

        IZI_ASSERT(*itr == make_pair(data[2], data[2]));

        for (auto itr = list.cbegin(); itr != list.cend(); ++itr)
        {
            int i = distance(list.cbegin(), itr);
            IZI_ASSERT(*itr == make_pair(data[i], data[i]));
        }
    }

    template<typename T>
    void PushFront() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.push_front(x);

        reverse(data.begin(), data.end());

        for (auto itr = list.cbegin(); itr != list.cend(); ++itr)
        {
            int i = distance(list.cbegin(), itr);
            IZI_ASSERT(*itr == data[i]);
        }

        IZI_ASSERT(data.size() == list.size());
    }

    template<typename T>
    void PushBack() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.push_back(x);

        for (auto itr = list.cbegin(); itr != list.cend(); ++itr)
        {
            int i = distance(list.cbegin(), itr);
            IZI_ASSERT(*itr == data[i]);
        }

        IZI_ASSERT(data.size() == list.size());
    }

    template<typename T>
    void PopFront() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.push_back(x);

        for (int i = 0; i < data.size(); ++i)
        {
            IZI_ASSERT(list.front() == data[i]);
            list.pop_front();
        }

        IZI_ASSERT(list.empty());
    }

    template<typename T>
    void PopBack() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.push_back(x);

        reverse(data.begin(), data.end());

        for (int i = 0; i < data.size(); ++i)
        {
            IZI_ASSERT(list.back() == data[i]);
            list.pop_back();
        }

        IZI_ASSERT(list.empty());
    }

    template<typename T>
    void Insert() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()(5);

        list.push_back(data[1]);
        list.push_back(data[2]);
        list.push_back(data[4]);

        auto itr = list.begin();
        itr = list.insert(itr, data[0]);

        IZI_ASSERT(*itr == data[0]);
        IZI_ASSERT(itr == list.begin());

        advance(itr, 3);
        itr = list.insert(itr, data[3]);
        IZI_ASSERT(*itr == data[3]);

        for (itr = list.begin(); itr != list.end(); ++itr)
            IZI_ASSERT(*itr == data[distance(list.begin(), itr)]);

        IZI_ASSERT(list.size() == data.size());
    }

    template<typename T>
    void InsertByValue(const T& x) noexcept
    {
        const int listSize = rand(0, 20);
        CTestedList<T> list;

        list.assign(listSize, x);

        for (T val : list)
            IZI_ASSERT(val == x);

        IZI_ASSERT(list.size() == listSize);
    }

    template<typename T>
    void InsertByIterator() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()();

        list.assign(data.cbegin(), data.cend());

        for (auto itr = list.cbegin(); itr != list.cend(); ++itr)
            IZI_ASSERT(*itr == data[distance(list.cbegin(), itr)]);

        IZI_ASSERT(list.size() == data.size());
    }

    template<typename T>
    void Erase() noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T>()();

        for (T x : data)
            list.push_back(x);

        auto itr = list.erase(list.begin());
        IZI_ASSERT(*itr == data[1]);
        IZI_ASSERT(itr == list.begin());

        itr = list.erase(--list.end());
        IZI_ASSERT(itr == list.end());

        IZI_ASSERT(list.size() == data.size() - 2);
    }

    template<typename T>
    void RunTemplatedTests() noexcept
    {
        CreateEmptyList<T>();
        CreateSizedList<T>();

        for (T x : CValueProvider<T>()(5))
            CreateSizeListWithValue<T>(x);
//
        CreateListByExplicitCopy<T>();
        CreateListByImplicitCopy<T>();
//
        Iterate<T>();
//        ConstIterate<T>();
//        ReverseIterate<T>();
//        ReverseConstIterate<T>();
//
//        IsEmpty<T>();
//        Size<T>();
//
//        Front<T>();
//        Back<T>();
//
//        AssignByIterator<T>();
//        for (T x : CValueProvider<T>()(5))
//            AssignByValue(x);
//
//        EmplaceFront<T>();
//        EmplaceBack<T>();
//        Emplace<T>();
//
//        PushFront<T>();
//        PushBack<T>();
//
//        PopFront<T>();
//        PopBack<T>();
//
//        Insert<T>();
//        InsertByIterator<T>();
//        for (T x : CValueProvider<T>()(5))
//            InsertByValue<T>(x);
//
//        Erase<T>();
    }
}

void CTests::RunTests() noexcept
{
    cout << "Starting tests..." << endl;

    srand(time(NULL));
    IZI_CALLTEST(RunTemplatedTests<int>());
    IZI_CALLTEST(RunTemplatedTests<int *>());
    IZI_CALLTEST(RunTemplatedTests<shared_ptr<int>>());

    IZI_CALLTEST(RunTemplatedTests<TestClass>());
    IZI_CALLTEST(RunTemplatedTests<TestClass *>());
    IZI_CALLTEST(RunTemplatedTests<shared_ptr<TestClass>>());

    cout << "Tests done..." << endl;
}
