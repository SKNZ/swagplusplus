/*!
@file CList2.h
@author Anthony L., Loïck M., Thomas M., Floran N., Loïc P.
@date 08/12/2014
@version  1.0
@brief Header to the CList class.

@mainpage Documention for the class "CList"
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
        struct CIterator;

        struct CConstIterator;

        class CNode;

        /*!
            @typedef CNodePtr
            @brief This define a @p std::shared_ptr<CNode> like a CNodePtr. We use
                    it to declare the content of the list
        */
        typedef std::shared_ptr<CNode> CNodePtr;

    public:

        /*!
            @typedef size_type
            @brief This define a @p size_t. We use it because it's a std::list standard
         */
        typedef size_t size_type;

        /*!
            @typedef iterator
            @brief This define a @p CIterator. We use it to declare a CList iterator
         */
        typedef CIterator iterator;

        /*!
            @typedef const_iterator
            @brief This define a @p CConstIterator. We use it to declare a CList const iterator
         */
        typedef CConstIterator const_iterator;

        /*!
            @typedef reverse_iterator
            @brief This define a @p CReverseIterator. We use it to declare a CList reverse_iterator
         */
        typedef std::reverse_iterator<iterator> reverse_iterator;

        /*!
            @typedef const_reverse_iterator
            @brief This define a @p CConstReverseIterator. We use it to declare a CList const reverse iterator
         */
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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
        iterator begin () noexcept;

        iterator end () noexcept;

        const_iterator cbegin () const noexcept;

        const_iterator cend () const noexcept;

        std::reverse_iterator<iterator> rbegin () noexcept;

        std::reverse_iterator<iterator> rend () noexcept;

        std::reverse_iterator<const_iterator> crbegin () noexcept;

        std::reverse_iterator<const_iterator> crend () noexcept;


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
#include "CList2Node.hxx"
