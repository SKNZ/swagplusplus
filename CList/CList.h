/*!
@file CList.h
@author Anthony L., Loïck M., Thomas M., Floran N., Loïc P.
@date 08/12/2014
@version  1.0
@brief Header to the CList class.

@mainpage Documention for the class "CList"

The goal of this class is reproduce the behaviour of the STL container std::list.
For this reason, we chose to implement a doubly linked list and bidirectional iterators.
Doubly linked list are easier to browse and more convenient to use.
They have the disavantage of being more complex, however by using two sentinels their complexity is grealt reduced.

Since our CList is made to be "plug and play" with the std list, we chose to respect their conventions to best of our ability.

As requested, the Allocator part is not supported.
Performance tests have not been run, but we know that our implementation is sub par.

Thank you for reading this notice. We hope you find our code pleasant ;)

*/

#pragma once

#include <iterator>
#include <memory>

namespace nsSdD
{

    template<typename T>
    /*!
       @brief CList is the main class of our work, it's develop in order to be the most close to the original std::list
              In this idea we choose to make a double-linked list, in that way we can use bidirectional iterator and have
              a stl compliant CList. During the development process we choose to work in TDD (Test Driven Development) in
              order to have the least bugs possible.

    */
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
            @fn     'template < InputIterator > nsSdD::CList< T >::CList(InputIterator first, InputIterator last) noexcept'
            @brief  This is the constructor who construct a new CList from two iterator of another CList.
            @param[in] first This point to the first element who want to copy.
            @param[in] last This point to the last element who want to copy.
         */
        template<class InputIterator>
        explicit CList (InputIterator first, InputIterator last) noexcept;

        // V1
        /*!
            @fn     getHead() const noexcept
            @brief  This function return the head of the CList.
            @return CNodePtr A pointer to the head of the Clist.
         */
        inline CNodePtr getHead () const noexcept;

        /*!
            @fn     getTail() const noexcept
            @brief  This function return the tail of the CList.
            @return CNodePtr A pointer to the tail of the Clist.
         */
        inline CNodePtr getTail () const noexcept;

        // iterators
        /*!
            @fn     begin() noexcept
            @brief  This function construct and return A iterator to the begin of the CList.
            @return iterator A iterator who point to the begin of the CList.
         */
        iterator begin () noexcept;

        /*!
            @fn     end() noexcept
            @brief  This function construct and return A iterator to the end of the CList.
            @return iterator A iterator who point to the end of the CList.
         */
        iterator end () noexcept;

        /*!
            @fn     cbegin() noexcept
            @brief  This function construct and return a const_iterator to the begin of the CList.
            @return const_iterator A iterator who point to the begin of the CList.
         */
        const_iterator cbegin () const noexcept;

        /*!
            @fn     cend() noexcept
            @brief  This function construct and return a iterator to the end of the CList.
            @return const_iterator A iterator who point to the end of the CList.
         */
        const_iterator cend () const noexcept;

        /*!
            @fn     rbegin() noexcept
            @brief  This function construct and return an reverse_iterator to the end of the CList.
            @return reverse_iterator<iterator> A reverse_iterator who point to the end of the CList.
         */
        std::reverse_iterator<iterator> rbegin () noexcept;

        /*!
            @fn     rend() noexcept
            @brief  This function construct and return an reverse_iterator to the begin of the CList.
            @return reverse_iterator<iterator> A reverse_iterator who point to the begin of the CList.
         */
        std::reverse_iterator<iterator> rend () noexcept;

        /*!
            @fn     crbegin() noexcept
            @brief  This function construct and return an const_reverse_iterator to the end of the CList.
            @return reverse_iterator<const_iterator> A const_reverse_iterator who point to the end of the CList.
         */
        std::reverse_iterator<const_iterator> crbegin () noexcept;

        /*!
            @fn     crend() noexcept
            @brief  This function construct and return an const_reverse_iterator to the begin of the CList.
            @return reverse_iterator<const_iterator> A const_reverse_iterator who point to the begin of the CList.
         */
        std::reverse_iterator<const_iterator> crend () noexcept;


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
           @fn     assign(unsigned n, const T &val) noexcept
           @brief  This function erase the content of the list and replace the content of the CList with the @p n size and with the @p val value.
           @param[in] n The size of the CList we want.
           @param[in] val The value we want to affect on each element of the new CList.
        */
        void assign (unsigned n, const T &val) noexcept;

        /*!
           @fn     assign(InputIterator begin, InputIterator last) noexcept
           @brief  This function erase the content of the list and replace the content of the CList with the element between @p first and @p last element.
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
           @fn     'template<class Compare> sort(Compare comp) noexcept
           @brief  This function the CList with the comparator @p comp given in parameter.
           @param[in] comp The comparator you want to use to sort the CList.
        */
        template <class Compare>
        void sort(Compare comp) noexcept;

        // Emplace
        /*!
           @fn     emplace (iterator position, Args &&... args) noexcept
           @brief  This function constructs an element with @p args and place it before the @p position.
           @param[in] args The package of arguments you want to use to construct you element.
           @param[in] position The position where you want to insert the new element.
           @return A iterator that points to the newly inserted elements.
        */
        template<typename... Args>
        iterator emplace (iterator position, Args &&... args) noexcept;

        /*!
           @fn     emplace ( Args &&... args) noexcept
           @brief  This function construct an element with @p args and place at the beginning of the CList.
           @param[in] args The package of arguments you want to use to construct you element.
           @return A iterator that points to the newly inserted elements.
        */
        template<typename... Args>
        iterator emplace_front (Args &&... args) noexcept;

        /*!
           @fn     emplace ( Args &&... args) noexcept
           @brief  This function construct an element with @p args and place at the end of the CList.
           @param[in] args The package of arguments you want to use to construct you element.
           @return A iterator that points to the newly inserted elements.
        */
        template<typename... Args>
        iterator emplace_back (Args &&... args) noexcept;

        // Insert
        /*!
           @fn     insert (iterator position, const T &val) noexcept
           @brief  Inserts element @p val before position @p position.
           @param[in] position The position where you want to insert the new element.
           @param[in] val A const reference to the element you are adding.
           @return A iterator that points to the newly inserted element.
        */
        iterator insert (iterator position, const T &val) noexcept;

        /*!
           @fn     insert (iterator position, size_type n, const T &val) noexcept
           @brief  Inserts @p n elements @p val before position @p position.
           @param[in] position The position where you want to insert the new element.
           @param[in] val A const reference to the element you are adding.
           @param[in] n The amount of times the element will be added
           @return A iterator that points to the first of newly inserted elements.
        */
        iterator insert (iterator position, size_type n, const T &val) noexcept;

        /*!
           @fn     'template<class InputIterator> insert (iterator position, InputIterator begin, InputInterator end) noexcept
           @brief  Inserts the elements in the range from @p begin to @p end starting from position @p position
           @param[in] position The position where you want to insert the new element.
           @param[in] first An iterator to the first element to insert.
           @param[in] last An iterator to the last element to insert.
           @details Any kind of InputIterator is accepted...
           @return A iterator that points to the first of newly inserted elements.
        */
        template<class InputIterator>
        iterator insert (iterator position, InputIterator first, InputIterator last) noexcept;

        // Erase
        /*!
           @fn     erase (iterator del) noexcept
           @brief  This function delete the element pointed by the iterator @p del.
           @param[in] del A iterator who pointing to the element who want to delete .
            @return iterator The element that followed the last element erased by the function call.
        */
        iterator erase (iterator del) noexcept;

        /*!
           @fn     erase (iterator first, iterator last) noexcept
           @brief  This function elements between the @p first and @p last iterator .
           @param[in] first A iterator who pointing to the first element who want to delete .
           @param[in] last A iterator who pointing to the last element who want to delete .
           @return iterator The element that followed the last element erased by the function call.
        */
        iterator erase (iterator first, iterator last) noexcept;

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

        /*!
          @fn     'template<classe Predicate> unique (Predicate pred) noexcept
          @brief  This function removes all element that are duplicated and where the @p pred are true.
          @param[in] pred The predicate we want to use on the CList.
       */
        template<class Predicate>
        void unique (Predicate pred) noexcept;

        //Splice
        /*!
          @fn     splice (iterator position, CList &x) noexcept
          @brief  This function move the CList @p x to the current CList before @p position.
          @param[in] position The position where we want to insert the other list.
          @param[in] x The CList we want to add on the current CList.
       */
        void splice (iterator position, CList &x) noexcept;

        /*!
          @fn     splice (iterator position, CList &x, iterator i) noexcept
          @brief  This function move element @p i from the CList @p x to the current CList before @p position.
          @param[in] position The position where we want to insert the other list.
          @param[in] x The CList we want to add on the current CList.
          @param[in] i The iterator who pointing the element who want to move on the current CList.
       */
        void splice (iterator position, CList &x, iterator i) noexcept;

        /*!
          @fn     splice (iterator position, CList &x,iterator first, iterator last) noexcept
          @brief  This function move elements between @p first and @p last from the CList @p x to the current CList before @p position.
          @param[in] position The position where we want to insert the other list.
          @param[in] x The CList we want to add on the current CList.
          @param[in] first The iterator who pointing the first element who want to move on the current CList.
          @param[in] last The iterator who pointing the last element who want to move on the current CList.
       */
        void splice (iterator position, CList &x, iterator first, iterator last) noexcept;

        //Merge
        /*!
          @fn     merge (CList<T>& x) noexcept
          @brief  This function merge two sorted list @p x after the current CList.
          @param[in] position The sorted list we want to merge with the current CList.
       */
        void merge (CList<T>& x) noexcept;

        // Reverse
        /*!
          @fn     reverse () noexcept
          @brief  This function reverse the head and the tail of the CList.
       */
        void reverse () noexcept;

    private:

        /*!
          @var     m_size
          @brief  The size of the CList.
       */
        size_type m_size = 0;

        /*!
          @var     m_head
          @brief  A pointer the head of the CList.
       */
        CNodePtr m_head = nullptr;

        /*!
          @var     m_tail
          @brief  A pointer the tail of the CList.
       */
        CNodePtr m_tail = nullptr;
    };
}

#include "CList.hxx"
#include "CIterator.hxx"
#include "CConstIterator.hxx"
#include "CNode.hxx"
