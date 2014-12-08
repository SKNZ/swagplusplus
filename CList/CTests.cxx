#include "CTests.h"
#include "IziAssert.h"
#include "CList.h"
#include "CTestClass.h"
#include "CValueProvider.h"

#include <ctime>
#include <algorithm>

using namespace nsTests;
using namespace std;
using namespace nsSdD;

namespace
{
    //template<typename T> using CTestedList = list<T>;
    template<typename T> using CTestedList = CList<T>;

    template<typename T>
    void CreateEmptyList () noexcept
    {
        CTestedList<T> list;

        IZI_ASSERT(list.size () == 0);
        IZI_ASSERT(list.empty ());
        IZI_ASSERT(list.begin () == list.end ());
        IZI_ASSERT(list.cbegin () == list.cend ());
    }

    template<typename T>
    void CreateSizedList () noexcept
    {
        typename CTestedList<T>::size_type listSize = rand (1, 10);

        CTestedList<T> list (listSize);

        IZI_ASSERT(list.size () == listSize);
        IZI_ASSERT(!list.empty ());
        IZI_ASSERT(list.begin () != list.end ());

        for (T x : list)
            IZI_ASSERT(x == T ());
    }

    template<typename T>
    void CreateSizeListWithValue (const T &value) noexcept
    {
        typename CTestedList<T>::size_type listSize = rand (1, 10);

        CTestedList<T> list (listSize, value);

        IZI_ASSERT(list.size () == listSize);
        IZI_ASSERT(!list.empty ());
        IZI_ASSERT(list.begin () != list.end ());

        for (T x : list)
            IZI_ASSERT(x == value)
    }

    template<typename T>
    void CreateListByExplicitCopy () noexcept
    {
        typename CTestedList<T>::size_type listSize = rand (1, 10000);

        CTestedList<T> referenceList;
        for (T x : CValueProvider<T> () (listSize))
            referenceList.push_back (x);

        CTestedList<T> copiedList (referenceList);

        IZI_ASSERT(referenceList.size () == copiedList.size ());

        while (!referenceList.empty ())
        {
            IZI_ASSERT(referenceList.front () == copiedList.front ());
            referenceList.pop_front ();
            copiedList.pop_front ();
        }
    }

    template<typename T>
    void CreateListByImplicitCopy () noexcept
    {
        typename CTestedList<T>::size_type listSize = rand (1, 10000);

        CTestedList<T> referenceList;
        for (T x : CValueProvider<T> () (listSize))
            referenceList.push_back (x);

        CTestedList<T> copiedList = referenceList;

        IZI_ASSERT(referenceList.size () == copiedList.size ());

        while (!referenceList.empty ())
        {
            IZI_ASSERT(referenceList.front () == copiedList.front ());
            referenceList.pop_front ();
            copiedList.pop_front ();
        }
    }

    template<typename T>
    void Iterate () noexcept
    {
        const typename CTestedList<T>::size_type listSize = 20;

        CTestedList<T> list;
        CCollection<T> t = CValueProvider<T> () (listSize);
        CCollection<T> originalData (t.begin (), t.begin () + listSize / 2);
        CCollection<T> newData (t.begin () + listSize / 2, t.end ());

        for (T x : originalData)
            list.push_back (x);

        typename CTestedList<T>::iterator begin = list.begin ();
        typename CTestedList<T>::iterator end = list.end ();

        for (; begin != end; ++begin)
        {
            int i = distance (list.begin (), begin);
            IZI_ASSERT(originalData[i] == *begin);
            *begin = newData[i];
            IZI_ASSERT(newData[i] == *begin);
        }

        IZI_ASSERT(begin == end);
    }

    template<typename T>
    void ConstIterate () noexcept
    {
        const typename CTestedList<T>::size_type listSize = 20;

        CTestedList<T> list;
        CCollection<T> t = CValueProvider<T> () (listSize);
        for (T x : t)
            list.push_back (x);

        typename CTestedList<T>::const_iterator cbegin = list.cbegin ();
        typename CTestedList<T>::const_iterator cend = list.cend ();

        for (; cbegin != cend; ++cbegin)
            IZI_ASSERT(t[distance (list.cbegin (), cbegin)] == *cbegin);

        IZI_ASSERT(cbegin == cend);
    }

    template<typename T>
    void ReverseIterate () noexcept
    {
        const typename CTestedList<T>::size_type listSize = 20;

        CTestedList<T> list;
        CCollection<T> t = CValueProvider<T> () (listSize);
        CCollection<T> originalData (t.begin (), t.begin () + listSize / 2);
        CCollection<T> newData (t.begin () + listSize / 2, t.end ());

        for (T x : originalData)
            list.push_back (x);

        reverse (originalData.begin (), originalData.end ());
        reverse (newData.begin (), newData.end ());

        typename CTestedList<T>::reverse_iterator rbegin = list.rbegin ();
        typename CTestedList<T>::reverse_iterator rend = list.rend ();

        for (; rbegin != rend; ++rbegin)
        {
            int i = distance (list.rbegin (), rbegin);
            IZI_ASSERT(originalData[i] == *rbegin);
            *rbegin = newData[i];
            IZI_ASSERT(newData[i] == *rbegin);
        }

        IZI_ASSERT(rbegin == rend);
    }

    template<typename T>
    void ReverseConstIterate () noexcept
    {
        const typename CTestedList<T>::size_type listSize = 20;

        CTestedList<T> list;
        CCollection<T> t = CValueProvider<T> () (listSize);
        for (T x : t)
            list.push_back (x);

        reverse (t.begin (), t.end ());

        typename CTestedList<T>::const_reverse_iterator crbegin = list.crbegin ();
        typename CTestedList<T>::const_reverse_iterator crend = list.crend ();

        for (; crbegin != crend; ++crbegin)
            IZI_ASSERT(t[distance (list.crbegin (), crbegin)] == *crbegin);

        IZI_ASSERT(crbegin == crend);
    }

    template<typename T>
    void IsEmpty () noexcept
    {
        CTestedList<T> list;

        IZI_ASSERT(list.empty ());
        list.push_back (T ());
        IZI_ASSERT(!list.empty ());
        list.pop_front ();
        IZI_ASSERT(list.empty ());
    }

    template<typename T>
    void Size () noexcept
    {
        CTestedList<T> list;

        IZI_ASSERT(0 == list.size ());

        list.push_front (T ());
        IZI_ASSERT(1 == list.size ());

        list.pop_back ();
        IZI_ASSERT(0 == list.size ());
    }

    template<typename T>
    void Front () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.push_back (x);

        IZI_ASSERT(list.front () == *data.begin ());
    }

    template<typename T>
    void Back () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.push_back (x);

        IZI_ASSERT(list.back () == *--data.end ());
    }

    template<typename T>
    void AssignByIterator () noexcept
    {
        const int listSize = 10;

        CTestedList<T> list (2 * listSize);
        CCollection<T> data = CValueProvider<T> () (listSize);

        list.assign (data.cbegin (), data.cend ());

        IZI_ASSERT(data.size () == list.size ());

        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
        {
            IZI_ASSERT(*itr == data[distance (list.cbegin (), itr)]);
        }

    }

    template<typename T>
    void AssignByValue (const T &x) noexcept
    {
        const unsigned listSize = 10;

        CTestedList<T> list;
        list.assign (listSize, x);

        IZI_ASSERT(listSize == list.size ());
        for (T val : list)
            IZI_ASSERT(val == x);
    }

    template<typename T>
    void EmplaceFront () noexcept
    {
        CTestedList<pair<T, T>> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.emplace_front (x, x);

        reverse (list.begin (), list.end ());

        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
        {
            int i = distance (list.cbegin (), itr);
            IZI_ASSERT(make_pair (data[i], data[i]) == *itr)
        }

        IZI_ASSERT(list.size () == data.size ());
    }

    template<typename T>
    void EmplaceBack () noexcept
    {
        CTestedList<pair<T, T>> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.emplace_back (x, x);

        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
        {
            int i = distance (list.cbegin (), itr);
            IZI_ASSERT(make_pair (data[i], data[i]) == *itr)
        }

        IZI_ASSERT(list.size () == data.size ());
    }

    template<typename T>
    void Emplace () noexcept
    {
        CTestedList<pair<T, T>> list;
        CCollection<T> data = CValueProvider<T> () (5);

        list.push_back (make_pair (data[0], data[0]));
        list.push_back (make_pair (data[1], data[1]));
        list.push_back (make_pair (data[3], data[3]));
        list.push_back (make_pair (data[4], data[4]));

        auto itr = list.begin ();
        advance (itr, 2);
        itr = list.emplace (itr, data[2], data[2]);

        IZI_ASSERT(*itr == make_pair (data[2], data[2]));

        for (itr = list.begin (); itr != list.end (); ++itr)
        {
            int i = distance (list.begin (), itr);
            IZI_ASSERT(*itr == make_pair (data[i], data[i]));
        }
    }

    template<typename T>
    void PushFront () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.push_front (x);

        reverse (data.begin (), data.end ());

        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
        {
            int i = distance (list.cbegin (), itr);
            IZI_ASSERT(*itr == data[i]);
        }

        IZI_ASSERT(data.size () == list.size ());
    }

    template<typename T>
    void PushBack () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.push_back (x);

        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
        {
            int i = distance (list.cbegin (), itr);
            IZI_ASSERT(*itr == data[i]);
        }

        IZI_ASSERT(data.size () == list.size ());
    }

    template<typename T>
    void PopFront () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.push_back (x);

        for (typename CTestedList<T>::size_type i = 0; i < data.size (); ++i)
        {
            IZI_ASSERT(list.front () == data[i]);
            list.pop_front ();
        }

        IZI_ASSERT(list.empty ());
    }

    template<typename T>
    void PopBack () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.push_back (x);

        reverse (data.begin (), data.end ());

        for (typename CTestedList<T>::size_type i = 0; i < data.size (); ++i)
        {
            IZI_ASSERT(list.back () == data[i]);
            list.pop_back ();
        }

        IZI_ASSERT(list.empty ());
    }

    template<typename T>
    void Insert () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () (5);

        list.push_back (data[1]);
        list.push_back (data[2]);
        list.push_back (data[4]);

        auto itr = list.begin ();
        itr = list.insert (itr, data[0]);

        IZI_ASSERT(*itr == data[0]);
        IZI_ASSERT(itr == list.begin ());

        advance (itr, 3);
        itr = list.insert (itr, data[3]);
        IZI_ASSERT(*itr == data[3]);

        for (itr = list.begin (); itr != list.end (); ++itr)
            IZI_ASSERT(*itr == data[distance (list.begin (), itr)]);

        IZI_ASSERT(list.size () == data.size ());
    }

    template<typename T>
    void InsertByValue (const T &x) noexcept
    {
        const typename CTestedList<T>::size_type listSize = rand (0, 20);
        CTestedList<T> list;

        list.insert (list.begin (), listSize, x);

        for (T val : list)
            IZI_ASSERT(val == x);

        IZI_ASSERT(list.size () == listSize);
    }

    template<typename T>
    void InsertByIterator () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        list.insert (list.begin (), data.cbegin (), data.cend ());

        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
            IZI_ASSERT(*itr == data[distance (list.cbegin (), itr)]);

        IZI_ASSERT(list.size () == data.size ());
    }

    template<typename T>
    void Erase () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        for (T x : data)
            list.push_back (x);

        auto itr = list.erase (list.begin ());
        IZI_ASSERT(*itr == data[1]);
        IZI_ASSERT(itr == list.begin ());

        itr = list.erase (--list.end ());
        IZI_ASSERT(itr == list.end ());

        IZI_ASSERT(list.size () == data.size () - 2);
    }

    template<typename T>
    void Swap () noexcept
    {
        const int listSize = 20;

        CTestedList<T> list1 (listSize / 2), list2 (listSize / 2);
        CCollection<T> data = CValueProvider<T> () (listSize);

        copy (data.cbegin (), data.cbegin () + listSize / 2, list1.begin ());
        copy (data.cbegin () + listSize / 2, data.cend (), list2.begin ());

        list1.swap (list2);

        for (auto itr = list1.cbegin (); itr != list1.cend (); ++itr)
            IZI_ASSERT(*itr == data[listSize / 2 + distance (list1.cbegin (), itr)]);

        for (auto itr = list2.cbegin (); itr != list2.cend (); ++itr)
            IZI_ASSERT(*itr == data[distance (list2.cbegin (), itr)]);
    }

    template<typename T>
    void Resize () noexcept
    {
        const int listSize = 20;

        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () (listSize);

        list.insert (list.begin (), data.cbegin (), data.cend ());
        list.resize (listSize / 2);

        IZI_ASSERT(list.size () == listSize / 2);

        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
            IZI_ASSERT(*itr == data[distance (list.cbegin (), itr)]);

        list.resize (0);

        IZI_ASSERT(0 == list.size ());
        IZI_ASSERT(list.cbegin () == list.cend ());

        list.resize (listSize);

        for (T x : list)
            IZI_ASSERT(x == T ());
        IZI_ASSERT(list.size () == listSize);

        list.resize (0);
        IZI_ASSERT(0 == list.size ());
        IZI_ASSERT(list.cbegin () == list.cend ());

        list.resize (listSize, data[0]);
        for (T x : list)
            IZI_ASSERT(x == data[0]);
        IZI_ASSERT(list.size () == listSize);
    }

    template<typename T>
    void Clear () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        list.clear ();
        IZI_ASSERT(0 == list.size ());

        list.insert (list.begin (), data.cbegin (), data.cend ());
        IZI_ASSERT(list.size () == data.size ());

        list.clear ();
        IZI_ASSERT(0 == list.size ());

        list.clear ();
        IZI_ASSERT(0 == list.size ());

        list.insert (list.begin (), data.cbegin (), data.cend ());
        IZI_ASSERT(list.size () == data.size ());

        list.clear ();
        IZI_ASSERT(0 == list.size ());
    }

    template<typename T>
    void SpliceList () noexcept
    {
        const int listSize = 20;
        CTestedList<T> list1, list2;
        CCollection<T> data = CValueProvider<T> () (listSize);

        list1.insert (list1.begin (), data.cbegin (), data.cbegin () + listSize / 4);
        list1.insert (list1.end (), data.cbegin () + listSize / 2, data.cend ());
        list2.insert (list2.begin (), data.cbegin () + listSize / 4, data.cbegin () + listSize / 2);

        IZI_ASSERT(list1.size () == 3 * data.size () / 4);
        IZI_ASSERT(list2.size () == data.size () / 4);

        auto itr = list1.begin ();
        advance (itr, listSize / 4);
        list1.splice (itr, list2);

        IZI_ASSERT(list2.empty ());
        IZI_ASSERT(list1.size () == data.size ());
        for (itr = list1.begin (); itr != list1.end (); ++itr)
            IZI_ASSERT(*itr == data[distance (list1.begin (), itr)]);
    }

    template<typename T>
    void SpliceOne () noexcept
    {
        const int listSize = 20;
        CTestedList<T> list1, list2;
        CCollection<T> data = CValueProvider<T> () (listSize);

        list2.insert (list2.begin (), data.cbegin (), data.cend ());

        for (auto itr = list2.begin (); itr != list2.end ();)
            list1.splice (list1.end (), list2, itr++);

        for (auto itr = list1.begin (); itr != list1.end (); ++itr)
            IZI_ASSERT(*itr == data[distance (list1.begin (), itr)]);

        IZI_ASSERT(list1.size () == data.size ());
    }

    template<typename T>
    void SpliceRange () noexcept
    {
        const int listSize = 20;
        CTestedList<T> list1, list2;
        CCollection<T> data = CValueProvider<T> () (listSize);

        list1.insert (list1.begin (), data.cbegin (), data.cbegin () + listSize / 4);
        list1.insert (list1.end (), data.cbegin () + listSize / 2, data.cend ());
        list2.insert (list2.begin (), data.cbegin () + listSize / 4, data.cbegin () + listSize / 2);

        IZI_ASSERT(list1.size () == 3 * data.size () / 4);
        IZI_ASSERT(list2.size () == data.size () / 4);

        auto itr = list1.begin ();
        advance (itr, listSize / 4);
        list1.splice (itr, list2, list2.begin (), list2.end ());

        IZI_ASSERT(list2.empty ());
        IZI_ASSERT(list1.size () == data.size ());
        for (itr = list1.begin (); itr != list1.end (); ++itr)
            IZI_ASSERT(*itr == data[distance (list1.begin (), itr)]);
    }

    template<typename T>
    void Remove () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () ();

        list.insert (list.begin (), data.cbegin (), data.cend ());

        IZI_ASSERT(list.size ());
        for (T x : data)
            list.remove (x);

        IZI_ASSERT(!list.size ());
    }

    template<typename T>
    void RemoveIf () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () (20);

        list.insert (list.begin (), data.cbegin (), data.cend ());

        static int i = 0;
        list.remove_if ([data] (const T &x)
        {
            return !(i++ % 2) || data[3] == x;
        });

        IZI_ASSERT(9 == list.size ());
    }

    template<typename T>
    void Unique () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () (20);

        unique (data.begin (), data.end ()); // Since some of the data might contain duplicates due to pseudo-random
        for (T x : data)
            for (int i = 0; i < 3; ++i)
                list.push_back (x);

        list.unique ();

        IZI_ASSERT(list.size () == data.size ());
        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
            IZI_ASSERT(*itr == data[distance (list.cbegin (), itr)]);
    }

    template<typename T>
    void UniqueWithPredicate () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () (20);

        unique (data.begin (), data.end ()); // Since some of the data might contain duplicates due to pseudo-random

        for (T x : data)
            for (int i = 0; i < 3; ++i)
                list.push_back (x);

        list.unique ([] (const T &a, const T &b)
        {
            return a == b;
        }); // Better way to test this ?

        IZI_ASSERT(list.size () == data.size ());
        for (auto itr = list.cbegin (); itr != list.cend (); ++itr)
            IZI_ASSERT(*itr == data[distance (list.cbegin (), itr)]);
    }

    template<typename T>
    void Merge () noexcept
    {
        CTestedList<T> list1, list2;
        CCollection<T> data = CValueProvider<T> () (20);

        sort (data.begin (), data.end ());

        for (typename CTestedList<T>::size_type i = 0; i < data.size (); i += 2)
            list1.push_back (data[i]);

        for (typename CTestedList<T>::size_type i = 1; i < data.size (); i += 2)
            list2.push_back (data[i]);

        IZI_ASSERT(list2.size () == list1.size () && list1.size () == data.size () / 2);

        list1.merge (list2);

        IZI_ASSERT(list1.size () == data.size ());
        IZI_ASSERT(list2.empty ());

        for (auto itr = list1.cbegin (); itr != --list1.cend ();)
            IZI_ASSERT(*itr <= *++itr)
    }

    template<typename T>
    void Sort () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () (20);

        list.insert (list.begin (), data.cbegin (), data.cend ());
        list.sort ();

        for (auto itr = list.cbegin (); itr != --list.cend ();)
            IZI_ASSERT(*itr <= *++itr)
    }

    template<typename T>
    void SortWithPredicate () noexcept
    {
        CTestedList<T> list;
        CCollection<T> data = CValueProvider<T> () (20);

        list.insert (list.begin (), data.cbegin (), data.cend ());
        list.sort ([] (const T &a, const T &b)
        {
            return b < a;
        });

        for (auto itr = list.cbegin (); itr != --list.cend ();)
            IZI_ASSERT(*itr >= *++itr)
    }

    template<typename T>
    void Reverse () noexcept
    {
        CCollection<T> data = CValueProvider<T> () ();
        CTestedList<T> list (data.cbegin (), data.cend ());

        list.reverse ();
        for (auto itrList = list.cbegin (), itrData = data.crbegin (); itrList != list.cend () && itrData != data.crend (); ++itrList, ++itrData)
            IZI_ASSERT(*itrList == *itrData);
    }

    template <class T>
    void TestCNode () noexcept
    {
        CCollection<T> data = CValueProvider<T> () ();
        CTestedList<T> list (data.cbegin (), data.cend ());

        IZI_ASSERT(list.getHead ()->getInfo () == T ());
        IZI_ASSERT(list.getTail ()->getInfo () == T ());

        auto ptr = list.getHead ();
        for(T x : data)
        {
            ptr = ptr->getNext ();
            IZI_ASSERT(x == ptr->getInfo ());
        }

        ptr = list.getTail ();
        reverse (data.begin (), data.end ());
        for (T x : data)
        {
            ptr = ptr->getPrevious ();
            IZI_ASSERT(x == ptr->getInfo ());
        }

        ptr->addAfter (data[0]);
        IZI_ASSERT(ptr->getNext ()->getInfo () == data[0]);

        ptr->addBefore (data[0]);
        IZI_ASSERT(ptr->getPrevious ()->getInfo () == data[0]);
    }

    template<typename T>
    void RunTemplatedTests () noexcept
    {
        IZI_SUBTEST(CreateEmptyList<T> ());
        IZI_SUBTEST(CreateSizedList<T> ());

        for (T x : CValueProvider<T> () (5))
        IZI_SUBTEST(CreateSizeListWithValue<T> (x));

        IZI_SUBTEST(CreateListByExplicitCopy<T> ());
        IZI_SUBTEST(CreateListByImplicitCopy<T> ());

        IZI_SUBTEST(Iterate<T> ());
        IZI_SUBTEST(ConstIterate<T> ());
        IZI_SUBTEST(ReverseIterate<T> ());
        IZI_SUBTEST(ReverseConstIterate<T> ());

        IZI_SUBTEST(IsEmpty<T> ());
        IZI_SUBTEST(Size<T> ());

        IZI_SUBTEST(Front<T> ());
        IZI_SUBTEST(Back<T> ());

        IZI_SUBTEST(AssignByIterator<T> ());
        for (T x : CValueProvider<T> () (5))
        IZI_SUBTEST(AssignByValue (x));

        IZI_SUBTEST(EmplaceFront<T> ());
        IZI_SUBTEST(EmplaceBack<T> ());
        IZI_SUBTEST(Emplace<T> ());

        IZI_SUBTEST(PushFront<T> ());
        IZI_SUBTEST(PushBack<T> ());

        IZI_SUBTEST(PopFront<T> ());
        IZI_SUBTEST(PopBack<T> ());

        IZI_SUBTEST(Insert<T> ());
        IZI_SUBTEST(InsertByIterator<T> ());

        for (T x : CValueProvider<T> () (5))
        IZI_SUBTEST(InsertByValue<T> (x));

        IZI_SUBTEST(Erase<T> ());

        IZI_SUBTEST(Swap<T> ());

        IZI_SUBTEST(Resize<T> ());

        IZI_SUBTEST(Clear<T> ());

        IZI_SUBTEST(SpliceList<T>());
        IZI_SUBTEST(SpliceOne<T>());
        IZI_SUBTEST(SpliceRange<T>());

        IZI_SUBTEST(Remove<T> ());
        IZI_SUBTEST(RemoveIf<T> ());

        IZI_SUBTEST(Unique<T> ());
        IZI_SUBTEST(UniqueWithPredicate<T> ());

        IZI_SUBTEST(Merge<T> ());

        IZI_SUBTEST(Sort<T> ());
        IZI_SUBTEST(SortWithPredicate<T> ());

        IZI_SUBTEST(Reverse<T> ());

        IZI_SUBTEST(TestCNode<T> ());

        cout << endl;
    }
}

void CTests::RunTests () noexcept
{
    cout << "Starting tests..." << endl << endl;

    srand (time (NULL));

    IZI_CALLTEST(RunTemplatedTests<int> ());
    IZI_CALLTEST(RunTemplatedTests<int *> ());
    IZI_CALLTEST(RunTemplatedTests<shared_ptr<int>> ());

    IZI_CALLTEST(RunTemplatedTests<TestClass> ());
    IZI_CALLTEST(RunTemplatedTests<TestClass *> ());
    IZI_CALLTEST(RunTemplatedTests<shared_ptr<TestClass>> ());

    cout << "Tests done..." << endl;
}
