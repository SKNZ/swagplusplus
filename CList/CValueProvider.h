/*!
@file CValueProvider.h
@author Anthony L., Loïck M., Thomas M., Floran N., Loïc P.
@date 08/12/2014
@version  1.0
@brief Provides semi-random values for tested classes...
*/
#pragma once

#include "CTestClass.h"
#include <vector>
#include <limits>

namespace nsTests
{
    int rand (int min, int max)
    {
        return min + (std::rand () % (max - min + 1));
    }

    // C++11 c'est bon, mangez-en.
    template<typename T> using CCollection = std::vector<T>;

    template<typename T>
    class CValueProvider
    {
    public:
        CCollection<T> operator() (const int /*valueCount*/ = 0)
        {
            // typeid(T).name() only gives mangled class name, not very clear but still a good indication.
            throw std::runtime_error (std::string ("Value provider for type ") + typeid (T).name () + " does not exist.");
        }
    };

    template<typename T>
    class CValueProvider<T *>
    {
    public:
        CCollection<T *> operator() (const int valueCount = 0)
        {
            CCollection<T> array = CValueProvider<T> () (valueCount);
            CCollection<T *> ptrArray;
            ptrArray.reserve (array.size ());

            for (T x : array)
                ptrArray.push_back (new T (x));

            return ptrArray;
        }
    };

    template<typename T>
    class CValueProvider<std::shared_ptr<T>>
    {
    public:
        CCollection<std::shared_ptr<T>> operator() (const int valueCount = 0)
        {
            CCollection<T> array = CValueProvider<T> () (valueCount);
            CCollection<std::shared_ptr<T>> ptrArray;
            ptrArray.reserve (array.size ());

            for (T x : array)
                ptrArray.push_back (std::make_shared<T> (x));

            return ptrArray;
        }
    };

    template<>
    class CValueProvider<int>
    {
    public:
        CCollection<int> operator() (const int valueCount = 0) noexcept
        {
            int arraySize = valueCount ? valueCount : rand (10, 100);

            CCollection<int> array (arraySize);

            array[0] = 0;
            array[1] = std::numeric_limits<int>::max ();
            array[2] = std::numeric_limits<int>::min ();

            for (int i = 3; i < arraySize; ++i)
                array[i] = std::rand ();

            return array;
        }
    };

    template<>
    class CValueProvider<TestClass>
    {
    public:
        CCollection<TestClass> operator() (const int valueCount = 0) noexcept
        {
            int arraySize = valueCount ? valueCount : rand (10, 100);
            CCollection<TestClass> array;
            array.reserve (arraySize);

            array.push_back (TestClass (4654, "MARQUE LA PORTE"));

            for (int i = array.size (); i < arraySize; ++i)
            {
                std::string name;
                for (int j = 0; j < rand (10, 20); ++j)
                    name += static_cast<char>(rand (66, 89));

                array.push_back (TestClass (rand (0, 30), name));
            }

            return array;
        }
    };
}
