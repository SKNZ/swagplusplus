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
        struct iterator;

        struct const_iterator;

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
            @brief This define a @p iterator. We use it to declare a CList iterator
         */
        typedef iterator iterator;

        /*!
            @typedef const_iterator
            @brief This define a @p const_iterator. We use it to declare a CList const iterator
         */
        typedef const_iterator const_iterator;

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
            @brief  This is the constructor who construct a new CList from two iterator of another CList.
            @param[in] begin This point to the first element who want to copy.
            @param[in] end This point to the last element who want to copy.
         */
        template<class InputIterator>
        explicit CList (InputIterator begin, InputIterator end) noexcept;

        // V1
        /*!
            @fn     getHead()
            @brief  This function return the head of the CList.
            @return CNodePtr A pointer to the head of the Clist.
         */
        inline CNodePtr getHead () const noexcept;

        /*!
            @fn     getTail()
            @brief  This function return the tail of the CList.
            @return CNodePtr A pointer to the tail of the Clist.
         */
        inline CNodePtr getTail () const noexcept;

        // Iterators
        /*!
            @fn     begin()
            @brief  This function construct and return an iterator to the begin of the CList.
            @return iterator A iterator who point to the begin of the CList.
         */
        iterator begin () noexcept;

        /*!
            @fn     end()
            @brief  This function construct and return an iterator to the end of the CList.
            @return iterator A iterator who point to the end of the CList.
         */
        iterator end () noexcept;

        /*!
            @fn     cbegin()
            @brief  This function construct and return a const_iterator to the begin of the CList.
            @return const_iterator A iterator who point to the begin of the CList.
         */
        const_iterator cbegin () const noexcept;

        /*!
            @fn     cend()
            @brief  This function construct and return a iterator to the end of the CList.
            @return const_iterator A iterator who point to the end of the CList.
         */
        const_iterator cend () const noexcept;

        /*!
            @fn     rbegin()
            @brief  This function construct and return an reverse_iterator to the end of the CList.
            @return reverse_iterator<iterator> A reverse_iterator who point to the end of the CList.
         */
        std::reverse_iterator<iterator> rbegin () noexcept;

        /*!
            @fn     rend()
            @brief  This function construct and return an reverse_iterator to the begin of the CList.
            @return reverse_iterator<iterator> A reverse_iterator who point to the begin of the CList.
         */
        std::reverse_iterator<iterator> rend () noexcept;

        /*!
            @fn     crbegin()
            @brief  This function construct and return an const_reverse_iterator to the end of the CList.
            @return reverse_iterator<const_iterator> A const_reverse_iterator who point to the end of the CList.
         */
        std::reverse_iterator<const_iterator> crbegin () noexcept;

        /*!
            @fn     crend()
            @brief  This function construct and return an const_reverse_iterator to the begin of the CList.
            @return reverse_iterator<const_iterator> A const_reverse_iterator who point to the begin of the CList.
         */
        std::reverse_iterator<const_iterator> crend () noexcept;


        // Capacity
        /*!
            @fn     empty()
            @brief  This function return true if the CList is empty , false otherwise
            @return bool If the CList is empty or not.
         */
        inline bool empty () const noexcept;

        /*!
            @fn     size()
            @brief  This function return the size of the CList.
            @return size_type The size of the CList.
         */
        inline size_type size () const noexcept;

        // Element access
        /*!
            @fn     front()
            @brief  This function return value of the first element in the CList.
            @return T The value of the first element in the list.
         */
        inline T front () const noexcept;

        /*!
            @fn     back()
            @brief  This function return value of the last element in the CList.
            @return T The value of the last element in the list.
         */
        inline T back () const noexcept;

        // Modifiers
        // Assign
        /*!
           @fn     asign()
           @brief  This function erase the content and replace the content of the CList with the @p n size and with the @p val value.
           @param[in] n The size of the CList we want.
           @param[in] val The value we want to affect on each element of the new CList.
        */
        void assign (unsigned n, const T &val) noexcept;

        /*!
           @fn     asign()
           @brief  This function erase the content and replace the content of the CList with the element between @p first and @p last element.
           @param[in] begin The first element we want to assign on the list.
           @param[in] last The last element we want to assign on the list.
        */
        template<class InputIterator>
        void assign (InputIterator begin, InputIterator last);

        // Push/pop
        /*!
           @fn     push_back()
           @brief  This function construct and add @p x value at the end of the CList.
           @param[in] T The value we want to insert at the end of the CList.
        */
        void push_back (const T &x) noexcept;

        /*!
           @fn     pop_back()
           @brief  This function delete the last element of the CList.
        */
        void pop_back () noexcept;

        /*!
           @fn     push_front()
           @brief  This function construct and add @p x value at the end of the CList.
           @param[in] x The value we want to insert at the beginning of the CList.
        */
        void push_front (const T &x) noexcept;

        /*!
           @fn     pop_front()
           @brief  This function delete the first element of the CList.
        */
        void pop_front () noexcept;

        // Sort
        /*!
           @fn     sort()
           @brief  This function the CList in ascending order.
        */
        void sort() noexcept;

        /*!
           @fn     sort(Compare comp)
           @brief  This function the CList with the comparator @p comp given in parameter.
           @param[in] comp The comparator you want to use to sort the CList.
        */
        template <class Compare>
        void sort(Compare comp) noexcept;

        // Emplace
        /*!
           @fn     emplace (iterator position, Args &&... args)
           @brief  This function constructs an element with @p args and place it before the @p position.
           @param[in] args The package of arguments you want to use to construct you element.
           @param[in] position The position where you want to insert the new element.
           @return An iterator that points to the newly inserted elements.
        */
        template<typename... Args>
        iterator emplace (iterator position, Args &&... args);

        /*!
           @fn     emplace ( Args &&... args)
           @brief  This function construct an element with @p args and place at the beginning of the CList.
           @param[in] args The package of arguments you want to use to construct you element.
           @return An iterator that points to the newly inserted elements.
        */
        template<typename... Args>
        iterator emplace_front (Args &&... args);

        /*!
           @fn     emplace ( Args &&... args)
           @brief  This function construct an element with @p args and place at the end of the CList.
           @param[in] args The package of arguments you want to use to construct you element.
           @return An iterator that points to the newly inserted elements.
        */
        template<typename... Args>
        iterator emplace_back (Args &&... args);

        // Insert

        /*!
           @fn     insert (C Args &&... args)
           @brief  This function construct an element with @p args and place at the beginning of the CList.
           @param[in] args The package of arguments you want to use to construct you element.
           @return An iterator that points to the newly inserted elements.
        */
        iterator insert (iterator position, const T &val) noexcept;

        iterator insert (iterator position, size_type n, const T &val) noexcept;

        template<class InputIterator>
        iterator insert (iterator position, InputIterator begin, InputIterator end) noexcept;

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
