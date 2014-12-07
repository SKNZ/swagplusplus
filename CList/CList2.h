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
            @fn     explicit CList (size_t n) noexcept
            @brief  This is the constructor by the size (@p size_t n) CList we want.
                    The constructor create a CList of n elements.
            @param[in] n The size of the CList we want.
        */
        explicit CList (size_t n) noexcept;

        /*!
            @fn     explicit CList (size_t n, const T &val) noexcept
            @brief  This is the constructor by the size (@p size_t n) CList we want.
                    The constructor create a CList of n elements with @p T val in each element.
            @param[in] n The size of the CList we want.
            @param[in] val The value we want to insert in the element of CList.
         */
        explicit CList (size_t n, const T &val) noexcept;

        /*!
            @fn     explicit CList (InputIterator begin, InputIterator end) noexcept
            @brief  This is the constructor who construct a new CList from two CIterator of another CList.
            @param[in] begin This point to the first element who want to copy.
            @param[in] end This point to the last element who want to copy.
         */
        template<class InputIterator>
        explicit CList (InputIterator begin, InputIterator end) noexcept;

        // V1
        /*!
            @fn     getHead() noexcept
            @brief  This function return the head of the CList.
            @return CNodePtr A pointer to the head of the Clist.
         */
        inline CNodePtr getHead () const noexcept;

        /*!
            @fn     getTail() noexcept
            @brief  This function return the tail of the CList.
            @return CNodePtr A pointer to the tail of the Clist.
         */
        inline CNodePtr getTail () const noexcept;

        // CIterators
        /*!
            @fn     begin() noexcept
            @brief  This function construct and return an CIterator to the begin of the CList.
            @return CIterator A CIterator who point to the begin of the CList.
         */
        CIterator begin () noexcept;

        /*!
            @fn     end() noexcept
            @brief  This function construct and return an CIterator to the end of the CList.
            @return CIterator A CIterator who point to the end of the CList.
         */
        CIterator end () noexcept;

        /*!
            @fn     cbegin() noexcept
            @brief  This function construct and return a CConstIterator to the begin of the CList.
            @return CConstIterator A CIterator who point to the begin of the CList.
         */
        CConstIterator cbegin () const noexcept;

        /*!
            @fn     cend() noexcept
            @brief  This function construct and return a CIterator to the end of the CList.
            @return CConstIterator A CIterator who point to the end of the CList.
         */
        CConstIterator cend () const noexcept;

        /*!
            @fn     rbegin() noexcept
            @brief  This function construct and return an reverse_iterator to the end of the CList.
            @return reverse_iterator<CIterator> A reverse_iterator who point to the end of the CList.
         */
        std::reverse_iterator<CIterator> rbegin () noexcept;

        /*!
            @fn     rend() noexcept
            @brief  This function construct and return an reverse_iterator to the begin of the CList.
            @return reverse_iterator<CIterator> A reverse_iterator who point to the begin of the CList.
         */
        std::reverse_iterator<CIterator> rend () noexcept;

        /*!
            @fn     crbegin() noexcept
            @brief  This function construct and return an const_reverse_iterator to the end of the CList.
            @return reverse_iterator<CConstIterator> A const_reverse_iterator who point to the end of the CList.
         */
        std::reverse_iterator<CConstIterator> crbegin () noexcept;

        /*!
            @fn     crend() noexcept
            @brief  This function construct and return an const_reverse_iterator to the begin of the CList.
            @return reverse_iterator<CConstIterator> A const_reverse_iterator who point to the begin of the CList.
         */
        std::reverse_iterator<CConstIterator> crend () noexcept;


        // Capacity
        /*!
            @fn     empty() noexcept
            @brief  This function return true if the CList is empty , false otherwise
            @return bool If the CList is empty or not.
         */
        inline bool empty () const noexcept;

        /*!
            @fn     size() noexcept
            @brief  This function return the size of the CList.
            @return size_type The size of the CList.
         */
        inline size_type size () const noexcept;

        // Element access
        /*!
            @fn     front() noexcept
            @brief  This function return value of the first element in the CList.
            @return T The value of the first element in the list.
         */
        inline T front () const noexcept;

        /*!
            @fn     back() noexcept
            @brief  This function return value of the last element in the CList.
            @return T The value of the last element in the list.
         */
        inline T back () const noexcept;

        // Modifiers
        // Assign
        /*!
           @fn     assign() noexcept
           @brief  This function erase the content and replace the content of the CList with the @p n size and with the @p val value.
           @param[in] n The size of the CList we want.
           @param[in] val The value we want to affect on each element of the new CList.
        */
        void assign (unsigned n, const T &val) noexcept;

        /*!
           @fn     assign() noexcept
           @brief  This function erase the content and replace the content of the CList with the element between @p first and @p last element.
           @param[in] begin The first element we want to assign on the list.
           @param[in] last The last element we want to assign on the list.
        */
        template<class InputIterator>
        void assign (InputIterator begin, InputIterator last) noexcept;

        // Push/pop
        /*!
           @fn     push_back() noexcept
           @brief  This function construct and add @p x value at the end of the CList.
           @param[in] T The value we want to insert at the end of the CList.
        */
        void push_back (const T &x) noexcept;

        /*!
           @fn     pop_back() noexcept
           @brief  This function delete the last element of the CList.
        */
        void pop_back () noexcept;

        /*!
           @fn     push_front() noexcept
           @brief  This function construct and add @p x value at the end of the CList.
           @param[in] x The value we want to insert at the beginning of the CList.
        */
        void push_front (const T &x) noexcept;

        /*!
           @fn     pop_front() noexcept
           @brief  This function delete the first element of the CList.
        */
        void pop_front () noexcept;

        // Sort
        /*!
           @fn     sort() noexcept
           @brief  This function the CList in ascending order.
        */
        void sort() noexcept;

        /*!
           @fn     sort(Compare comp) noexcept
           @brief  This function the CList with the comparator @p comp given in parameter.
           @param[in] comp The comparator you want to use to sort the CList.
        */
        template <class Compare>
        void sort(Compare comp) noexcept;

        // Emplace
        /*!
           @fn     emplace (CIterator position, Args &&... args) noexcept
           @brief  This function constructs an element with @p args and place it before the @p position.
           @param[in] args The package of arguments you want to use to construct you element.
           @param[in] position The position where you want to insert the new element.
           @return An CIterator that points to the newly inserted elements.
        */
        template<typename... Args>
        CIterator emplace (CIterator position, Args &&... args) noexcept;

        /*!
           @fn     emplace ( Args &&... args) noexcept
           @brief  This function construct an element with @p args and place at the beginning of the CList.
           @param[in] args The package of arguments you want to use to construct you element.
           @return An CIterator that points to the newly inserted elements.
        */
        template<typename... Args>
        CIterator emplace_front (Args &&... args) noexcept;

        /*!
           @fn     emplace ( Args &&... args) noexcept
           @brief  This function construct an element with @p args and place at the end of the CList.
           @param[in] args The package of arguments you want to use to construct you element.
           @return An CIterator that points to the newly inserted elements.
        */
        template<typename... Args>
        CIterator emplace_back (Args &&... args) noexcept;

        // Insert

        /*!
           @fn     insert (CIterator position, const T &val) noexcept
           @brief  This function construct an element with @p args and place at the beginning of the CList.
           @param[in] args The package of arguments you want to use to construct you element.
           @return An CIterator that points to the newly inserted elements.
        */
        CIterator insert (CIterator position, const T &val) noexcept;

        CIterator insert (CIterator position, size_type n, const T &val) noexcept;

        template<class InputIterator>
        CIterator insert (CIterator position, InputIterator begin, InputIterator end) noexcept;

        // Erase
        /*!
           @fn     erase (CIterator del) noexcept
           @brief  This function delete the element pointed by the CIterator @p del.
           @param[in] del A CIterator who pointing to the element who want to delete .
            @return CIterator The element that followed the last element erased by the function call.
        */
        CIterator erase (CIterator del) noexcept;

        /*!
           @fn     erase (CIterator first, CIterator last) noexcept
           @brief  This function elements between the @p first and @p last CIterator .
           @param[in] first A CIterator who pointing to the first element who want to delete .
           @param[in] last A CIterator who pointing to the last element who want to delete .
           @return CIterator The element that followed the last element erased by the function call.
        */
        CIterator erase (CIterator first, CIterator last) noexcept;

        // Swap
        /*!
           @fn     swap (CList &x) noexcept
           @brief  This function swap the two CLists .
           @param[in] x The CList we want to swap with the current CList.
        */
        void swap (CList &x) noexcept;

        // Resize
        /*!
           @fn     resize (unsigned n, const T &val = T ()) noexcept
           @brief  This function resize the CList if the @p n value is under the current
                    size of the CList the function delete element at end to reduce at the @p n size.
                    If you want to expand the size the new element are construct with the @p val value.
           @param[in] n The new size we want to have with the CList.
           @param[in] val The val we want to assign to new value if you expand the size.
        */
        void resize (unsigned n, const T &val = T ()) noexcept;

        // Clear
        /*!
           @fn     clear() noexcept
           @brief  This function delete all the element of the CList.
        */
        void clear () noexcept;

        // Operations
        // Remove
        /*!
          @fn     remove (const T &val) noexcept
          @brief  This function delete @p val element of the CList.
          @param[in] val The element you want to remove of the CList.
       */
        void remove (const T &val) noexcept;

        /*!
          @fn     remove (Predicate pred) noexcept
          @brief  This function delete all element of the CList who not respect the @p pred constraint.
          @param[in] pred The predicate we want to use to remove the elements who not respect the predicate.
       */
        template<class Predicate>
        void remove_if (Predicate pred) noexcept;

        // Unique
        /*!
          @fn     unique () noexcept
          @brief  This function removes all element that are duplicated.
       */
        void unique () noexcept;

        template<class Predicate>
        void unique (Predicate pred) noexcept;

        //Splice
        void splice (CIterator position, CList &x) noexcept;

        void splice (CIterator position, CList &x, CIterator i) noexcept;

        void splice (CIterator position, CList &x, CIterator first, CIterator last) noexcept;

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
