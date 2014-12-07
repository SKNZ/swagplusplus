/*!
@file CIterator.hxx
@author Anthony L., Loïck M., Thomas M., Floran N., Loïc P.
@date 08/12/2014
@version  1.0
@brief Implementation of iterator for the CList class.
*/
#pragma once

#include "CList.h"

template<typename T> using CIterBase = std::iterator<std::bidirectional_iterator_tag, T>;

/*!
    @brief This class permit CList to use iterators. Because we want to have a stl compliant CList with bidirectional
           iterators, we implement this on the CIterator class.
 */
template<typename T>
struct nsSdD::CList<T>::CIterator : public CIterBase<T>
{
private:
    /*!
        @var node
        @brief The current node of the iterator.
    */
    CNodePtr node;

public:
    /*!
        @fn             CIterator (CNodePtr p = nullptr) noexcept
        @brief          The default constructor of the iterator for the CList class.
        @param[in] p    The p node we want to use to construct the iterator.
    */
    CIterator (CNodePtr p = nullptr) noexcept : node (p)
    {
    }

    /*!
        @fn             CIterator (const CIterator &) noexcept
        @brief          The copy-constructor for the iterator.
    */
    CIterator (const CIterator &) noexcept = default;

    /*!
       @fn             operator= (const CIterator &) noexcept
       @brief          The default operator= for the iterator.
    */
    CIterator &operator= (const CIterator &) noexcept = default;

    /*!
       @fn             operator= (const T &info) noexcept
       @brief          The  operator = to assign a value to the iterator.
       @param[in]       info The value we want to affect.
       @return  CIterator The new value of the iterator.
    */
    CIterator &operator= (const T &info) noexcept
    {
        node->setInfo (info);
        return *this;
    }

    /*!
       @fn operator== (const CIterator &other) const noexcept
       @brief The operator == which compare the two node and return true if equal and false otherwise.
       @param[in] other The value we want to compare.
       @return  bool If the two iterator are equal.
    */
    bool operator== (const CIterator &other) const noexcept
    {
        return node == other.node;
    }

    /*!
       @fn operator!= (const CIterator &other) const noexcept
       @brief The  operator != which compare the two node and return true if not equal and false otherwise.
       @param[in] other The value we want to compare.
       @return  bool If the two iterator are not equal.
    */
    bool operator!= (const CIterator &other) const noexcept
    {
        return node != other.node;
    }

    /*!
       @fn operator++ () noexcept
       @brief The  operator ++ who pre-increment the iterator, gave to the next node.
       @return  CIterator The iterator with the new value.
    */
    CIterator &operator++ () noexcept
    {
        node = node->getNext ();
        return *this;
    }

    /*!
       @fn operator-- () noexcept
       @brief The  operator -- who pre-decrement the iterator, gave to the previous node.
       @return  CIterator The iterator with the new value.
    */
    CIterator &operator-- () noexcept
    {
        node = node->getPrevious ();
        return *this;
    }

    /*!
       @fn operator++ (int) noexcept
       @brief The  operator ++ who post-increment the iterator, gave to the next node.
       @return  CIterator The iterator with the old value, but iterator are incremented.
    */
    CIterator operator++ (int) noexcept
    {
        CIterator temp = *this;
        node = node->getNext ();
        return temp;
    }

    /*!
       @fn operator-- (int) noexcept
       @brief The  operator -- who post-decrement the iterator, gave to the previous node.
       @return  CIterator The iterator with the old value, but iterator are decremented.
    */
    CIterator operator-- (int) noexcept
    {
        CIterator temp = *this;
        node = node->getPrevious ();
        return temp;
    }

    /*!
       @fn operator-> () noexcept
       @brief The dereferencement operator -> who return the pointer to the info of the node.
       @return  CIterBase<T>::pointer The pointer to the value of the node.
    */
    typename CIterBase<T>::pointer operator-> () noexcept
    {
        return &node->getInfo ();
    }

    /*!
       @fn operator* () noexcept
       @brief The dereferencement operator * who return the a reference to the info of the node.
       @return  CIterBase<T>::reference The reference to the value of the node.
    */
    typename CIterBase<T>::reference operator* () noexcept
    {
        return node->getInfo ();
    }

    /*!
       @fn operator* () const noexcept
       @brief The dereferencement operator * who return the a reference to the info of the node.
       @return  CIterBase<T>::reference The reference to the value of the node.
    */
    typename CIterBase<T>::reference operator* () const noexcept
    {
        return node->getInfo ();
    }

    /*!
      @fn getNode () const noexcept
      @brief The function return the node of the pointer.
      @return  CNodePtr The node of the pointer.
   */
    CNodePtr getNode () const noexcept
    {
        return node;
    }
};
