/*!
@file CConstIterator.hxx
@author Anthony L., Loïck M., Thomas M., Floran N., Loïc P.
@date 08/12/2014
@version  1.0
@brief Implementation of the const_iterator for the CList class.
*/

#pragma once

#include "CList.h"

/*!
    @brief Makes our iterators compatible with std algorithms
 */
template<typename T> using CConstIterBase = std::iterator<std::bidirectional_iterator_tag, const T, std::ptrdiff_t, const T *, const T &>;

/*!
    @brief Sister const class to CIterator
 */
template<typename T>
struct nsSdD::CList<T>::CConstIterator : public CConstIterBase<T>
{
private:
    /*!
       @var node
       @brief The current node of the iterator.
   */
    CNodePtr node;

public:
    /*!
        @fn             CConstIterator (CNodePtr p = nullptr) noexcept
        @brief          The default constructor of the const_iterator for the CList class.
        @param[in] p    The the node we want to use to construct the iterator.
    */
    CConstIterator (CNodePtr p = nullptr) noexcept : node (p)
    {
    }

    /*!
        @fn             CConstIterator (const CConstIterator &)
        @brief          The copy-constructor for the const_iterator.
    */
    CConstIterator (const CConstIterator &) = default;

    /*!
       @fn             operator= (const CConstIterator &) noexcept
       @brief          The default operator= for the iterator.
       @return CConstIterator The new value of the const_iterator.
    */
    CConstIterator &operator= (const CConstIterator &) noexcept = default;

    /*!
       @fn operator== (const CConstIterator &other) const noexcept
       @brief The  operator == who compare the two node and return true if equal and false otherwise.
       @param[in] other The value we want to compare.
       @return  bool If the two iterator are equal.
    */
    bool operator== (const CConstIterator &other) const noexcept
    {
        return node == other.node;
    }

    /*!
       @fn operator!= (const CConstIterator &other) const noexcept
       @brief The  operator != who compare the two node and return true if not equal and false otherwise.
       @param[in] other The value we want to compare.
       @return  bool If the two iterator are not equal.
    */
    bool operator!= (const CConstIterator &other) const noexcept
    {
        return node != other.node;
    }

    /*!
       @fn operator++ () noexcept
       @brief The  operator ++ who pre-increment the iterator, pass to the next node.
       @return  CConstterator The iterator with the new value.
    */
    CConstIterator &operator++ () noexcept
    {
        node = node->getNext ();
        return *this;
    }

    /*!
       @fn operator-- () noexcept
       @brief The  operator -- who pre-decrement the iterator, pass to the previous node.
       @return  CConstterator The iterator with the new value.
    */
    CConstIterator &operator-- () noexcept
    {
        node = node->getPrevious ();
        return *this;
    }

    /*!
      @fn operator++ (int) noexcept
      @brief The  operator ++ who post-increment the iterator, pass to the next node.
      @return  CConstCIterator The iterator with the old value, but iterator are increment.
    */
    CConstIterator operator++ (int) noexcept
    {
        CConstIterator temp = *this;
        node = node->getNext ();
        return temp;
    }

    /*!
       @fn operator-- (int) noexcept
       @brief The  operator -- who post-decrement the iterator, pass to the previous node.
       @return  CConstterator The iterator with the old value, but iterator are decrement.
    */
    CConstIterator operator-- (int) noexcept
    {
        CConstIterator temp = *this;
        node = node->getPrevious ();
        return temp;
    }

    /*!
       @fn operator-> () const noexcept
       @brief The dereferencement operator -> who return the a pointer to the info of the node.
       @return  CIterBase<T>::pointer The pointer to the value of the node.
    */
    typename CConstIterBase<T>::pointer operator-> () const noexcept
    {
        return &node->getInfo ();
    }

    /*!
       @fn operator* () const snoexcept
       @brief The dereferencement operator * who return the a reference to the info of the node.
       @return  CIterBase<T>::reference The reference to the value of the node.
    */
    typename CConstIterBase<T>::reference operator* () const noexcept
    {
        return node->getInfo ();
    }

    /*!
       @fn getNode () noexcept
       @brief The function return the node of the pointer.
       @return  CNodePtr The node of the pointer.
    */
    CNodePtr getNode () const noexcept
    {
        return node;
    }
};
