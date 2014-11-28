#pragma once

#include <list>

#define CTestedList std::list
//#define CTestedList nsSdD::CList

namespace nsTests
{
    class CTests
    {
    public:
        static void RunTests() noexcept;

    private:
        CTests() = delete;
    };
}