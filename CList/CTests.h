/*!
@file CTests.h
@author Anthony L., Loïck M., Thomas M., Floran N., Loïc P.
@date 08/12/2014
@version  1.0
@brief CList tests runner
*/
#pragma once

#include <list>

/*!
    @brief Regroups everything related to tests.
 */
namespace nsTests
{
    /*!
        @brief Test caller runnable
     */
    class CTests
    {
    public:
        /*!
            @brief Run all the tests....
         */
        static void RunTests () noexcept;

    private:
        // Remove the default construcot (C++11 :))
        CTests () = delete;
    };
}