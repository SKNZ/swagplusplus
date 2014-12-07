/*!
@file CList2.h
@author Anthony L., Loïck M., Thomas M., Floran N., Loïc P.
@date 8 décembre 2014
@version  1.0
@brief Header to the CList class V2.

@mainpage Documention for the class "CList V2"
*/

#pragma once

#include <iterator>
#include <memory>

namespace nsSdD
{
    template<typename T>
    class CList
    {
        // Types
    private:
        class CIterator;

        class CConstIterator;

        class CReverseIterator;

        class CConstReverseIterator;

        class CNode;

        /*!
            @typedef CNodePtr
            @brief This define a @p std::shared_ptr<CNode> like a CNodePtr. We use
                    it to declare the content of the list
        */
        typedef std::shared_ptr<CNode> CNodePtr;

    public:
        typedef size_t size_type;
        typedef CIterator iterator;
        typedef CConstIterator const_iterator;
        typedef CReverseIterator reverse_iterator;
        typedef CConstReverseIterator const_reverse_iterator;

        /*!
            @fn CList (const CList<T> &x) noexcept
            @brief This is the copy-constructor of the class CList
            @param[in] @p CList<T> this is the list who want to copy.
        */
        CList (const CList<T> &x) noexcept;

        /*!
            @fn explicit CList () noexcept
            @brief This is the default of the class CList
            @param[in] No parameters.
        */
        explicit CList () noexcept;

        /*!
            @fn explicit CList (size_t n) noexcept
            @brief This is the default of the class CList
            @param[in] No parameters.
        */
        explicit CList (size_t n) noexcept;

        explicit CList (size_t n, const T &val) noexcept;

        template<class InputIterator>
        explicit CList (InputIterator begin, InputIterator end) noexcept;

        // V1
        inline CNodePtr getHead () const noexcept;

        inline CNodePtr getTail () const noexcept;

        // Iterators
        CIterator begin () noexcept;

        CIterator end () noexcept;

        CConstIterator cbegin () const noexcept;

        CConstIterator cend () const noexcept;

        CReverseIterator rbegin () noexcept;

        CReverseIterator rend () noexcept;

        CConstReverseIterator crbegin () const noexcept;

        CConstReverseIterator crend () const noexcept;

        // Capacity
        inline bool empty () const noexcept;

        inline size_type size () const noexcept;

        // Element access
        inline T front () const noexcept;

        inline T back () const noexcept;

        // Modifiers
        // Assign
        void assign (unsigned n, const T &val) noexcept;

        template<class InputIterator>
        void assign (InputIterator begin, InputIterator last);

        // Push/pop
        void push_back (const T &x) noexcept;

        void pop_back () noexcept;

        void push_front (const T &x) noexcept;

        void pop_front () noexcept;

        // Sort
        void sort() noexcept;

        template <class Compare>
        void sort(Compare comp) noexcept;

        // Emplace
        template<typename... Args>
        CIterator emplace (CIterator position, Args &&... args);

        template<typename... Args>
        CIterator emplace_front (Args &&... args);

        template<typename... Args>
        CIterator emplace_back (Args &&... args);

        // Insert
        CIterator insert (CIterator position, const T &val) noexcept;

        CIterator insert (CIterator position, size_type n, const T &val) noexcept;

        template<class InputIterator>
        CIterator insert (CIterator position, InputIterator begin, InputIterator end) noexcept;

        // Erase
        CIterator erase (CIterator del) noexcept;

        iterator erase (iterator first, iterator last) noexcept;

        // Swap
        void swap (CList &x) noexcept;

        // Resize
        void resize (unsigned n, const T &val = T ()) noexcept;

        // Clear
        void clear () noexcept;

        // Operations
        // Remove
        void remove (const T &val) noexcept;

        template<class Predicate>
        void remove_if (Predicate pred) noexcept;

        // Unique
        void unique () noexcept;

        template<class Predicate>
        void unique (Predicate pred) noexcept;

        //Splice
        void splice (iterator position, CList& x) noexcept;

        void splice (iterator position, CList& x, iterator i) noexcept;

        void splice (iterator position, CList& x, iterator first, iterator last) noexcept;

        //Merge
        void merge (CList<T>& x) noexcept;

        // Reverse
        void reverse () noexcept;

    private:
        size_type m_size = 0;
        CNodePtr m_head = nullptr;
        CNodePtr m_tail = nullptr;
    };
}

#include "CList2.hxx"
#include "CList2Iterator.hxx"
#include "CList2ConstIterator.hxx"
#include "CList2ReverseIterator.hxx"
#include "CList2ConstReverseIterator.hxx"
#include "CList2Node.hxx"
