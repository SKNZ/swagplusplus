/*!
@file CTests.h
@author Anthony L., Loïck M., Thomas M., Floran N., Loïc P.
@date 08/12/2014
@version  1.0
@brief CList tests runner
*/
#pragma once

#include <list>

namespace nsTests
{
    class CTests
    {
    public:
        static void RunTests () noexcept;

    private:
        CTests () = delete;
    };
}