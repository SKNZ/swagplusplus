#pragma once

#include <string>

namespace nsTests
{
    /*!
        @brief Dummy class for CList object testing
     */
    class TestClass
    {
    public:
        TestClass (int a = 0, const std::string &name = "ALAIN CASALOL") noexcept : m_a (a), m_name (name)
        {
        }

        bool operator== (const TestClass &c) const noexcept
        {
            return m_a == c.m_a && m_name == c.m_name;
        }

        bool operator< (const TestClass &c) const noexcept
        {
            if (m_a == c.m_a)
                return m_name < c.m_name;
            return m_a < c.m_a;
        }

        bool operator> (const TestClass &c) const noexcept
        {
            if (m_a == c.m_a)
                return m_name > c.m_name;
            return m_a > c.m_a;
        }

        bool operator<= (const TestClass &c) const noexcept
        {
            return *this < c || *this == c;
        }

        bool operator>= (const TestClass &c) const noexcept
        {
            return *this > c || *this == c;
        }

        int getA () const noexcept
        {
            return m_a;
        }

        std::string getName () const noexcept
        {
            return m_name;
        }

    private:
        int m_a;
        std::string m_name;
    };

    std::ostream &operator<< (std::ostream &os, TestClass const &p)
    {
        return os << "PERS. " << p.getName () << ". " << p.getA ();
    }
}