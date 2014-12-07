using namespace std;
using namespace nsSdD;

/*! @fn CList<T>::CList () noexcept
    @brief This function creates a Clist object (constructor).
    */
template<typename T>
CList<T>::CList () noexcept : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
                              m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);
}

/*!
    @fn CList<T>::CList (size_t n) noexcept
    @brief This function create a CList objet with n CNode.
    @param[in] n Is a @p size_t parameter for the amount of CNode in the CList .
    */
template<typename T>
CList<T>::CList (size_t n) noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);

    for (size_t i = 0; i < n; i++)
    {
        CNodePtr ptr = std::make_shared<CNode> (T (), nullptr, nullptr);

        ptr->setNext (m_tail);
        ptr->setPrevious (m_tail->getPrevious ());

        m_tail->getPrevious ()->setNext (ptr);
        m_tail->setPrevious (ptr);

        ++m_size;
    }
}

/*!
    @fn CList<T>::CList (size_t n, const T &val) noexcept
    @brief This function create a CList objet with n CNode.
    @param[in] n Is a @p size_t parameter for the amount of CNode in the CList .
    @param[in] val is @p T parameter is the default value for the CList
    */
template<typename T>
CList<T>::CList (size_t n, const T &val) noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);

    for (size_t i = 0; i < n; i++)
    {
        CNodePtr ptr = std::make_shared<CNode> (val, nullptr, nullptr);
        CNodePtr LastCreated = m_tail->getPrevious ();

        ptr->setNext (m_tail);
        ptr->setPrevious (LastCreated);

        LastCreated->setNext (ptr);
        m_tail->setPrevious (ptr);

        ++m_size;
    }
}

/*!
    @fn CList<T>::CList (const CList<T> &x) noexcept
    @brief This function create a CList object with the object contents in x.
    @param[in] x Is a @p CList<T> parameter which contains objects.
    */
template<typename T>
CList<T>::CList (const CList<T> &x) noexcept
        : m_head (std::make_shared<CNode> (T (), nullptr, nullptr)),
          m_tail (std::make_shared<CNode> (T (), nullptr, m_head))
{
    m_head->setNext (m_tail);

    for (auto itr = x.cbegin (); itr != x.cend (); ++itr)
        push_back (*itr);
}

/*!
    @fn CList<T>::assign (unsigned n, const T &val) noexcept
    @brief This function delete the chain at the n place and replace it by the chain val .
    @param[in] n Is a @p unsigned parameter which point the chain to remove.
    @param[in] v Is a @p T parameter which is the new chain.
    */
template<typename T>
void CList<T>::assign (unsigned n, const T &val) noexcept
{
    if (this->size () == 0)
    {
        for (size_t i = 0; i < n; i++)
        {
            CNodePtr ptr = std::make_shared<CNode> (val, nullptr, nullptr);
            CNodePtr LastCreated = m_tail->getPrevious ();

            ptr->setNext (m_tail);
            ptr->setPrevious (LastCreated);

            LastCreated->setNext (ptr);
            m_tail->setPrevious (ptr);

            ++m_size;
        }
    }
}

/*!
    @fn CList<T>::emplace_front (T val) noexcept
    @brief This function insert an element at the val in CList position which is constructed with a variadic template.
    @param[in] val Is a @p T parameter which indicates the position of the to construct.
    */
template<typename T>
void CList<T>::emplace_front (T val) noexcept
{
    CNodePtr ptr = std::make_shared<CNode> (val, nullptr, nullptr);

    ptr->setPrevious (m_head);
    ptr->setNext (m_head->getNext ());

    (m_head->getNext ())->setPrevious (ptr);

    m_head->setNext (ptr);

    ++m_size;
}

/*!
    @fn CList<T>::pop_front () noexcept
    @brief This function remove an element at the beginning of the CList  which is constructed with a variadic template.
    */
template<typename T>
void CList<T>::pop_front () noexcept
{
    CNodePtr del = m_head->getNext ();
    m_head->setNext (del->getNext ());

    (del->getNext ())->setPrevious (m_head);

    del->setPrevious (nullptr);
    del->setNext (nullptr);

    --m_size;
}

/*!
    @fn CList<T>::push_front (const T &x) noexcept
    @brief This function add an element at the beginning of the CList  which is constructed with a variadic template.
    @param[in] x Is a @p T parameter which indicates the element to add.
    */
template<typename T>
void CList<T>::push_front (const T &x) noexcept
{
    CNodePtr add = std::make_shared<CNode> (x, nullptr, nullptr);

    add->setNext (m_head->getNext ());
    add->setPrevious (m_head);
    add->getNext ()->setPrevious (add);
    m_head->setNext (add);

    ++m_size;
}

/*!
    @fn CList<T>::push_back (const T &x) noexcept
    @brief This function add an element at the end of the CList  which is constructed with a variadic template.
    @param[in] x Is a @p T parameter which indicates the element to add.
    */
template<typename T>
void CList<T>::push_back (const T &x) noexcept
{
    CNodePtr add = std::make_shared<CNode> (x, nullptr, nullptr);
    CNodePtr LastCreated = m_tail->getPrevious ();

    add->setNext (m_tail);
    add->setPrevious (LastCreated);

    LastCreated->setNext (add);
    m_tail->setPrevious (add);

    ++m_size;
}

/*!
    @fn CList<T>::pop_back () noexcept
    @brief This function remove an element at the end of the CList  which is constructed with a variadic template.
    */
template<typename T>
void CList<T>::pop_back () noexcept
{
    CNodePtr del = m_tail->getPrevious ();
    m_tail->setPrevious (del->getPrevious ());

    del->getPrevious ()->setNext (m_tail);

    del->setPrevious (nullptr);
    del->setNext (nullptr);

    --m_size;
}

/*!
    @fn CList<T>::emplace (CNodePtr Prec, T val) noexcept
    @brief This function add an element in the position after Prec in the CList.
    @param[in] Prec Is a @p CNodePtr parameter which indicates the position of the element before the element to add.
    @param[in] val Is a @p T parameter which is the elment to add.
    */
template<typename T>
void CList<T>::emplace (CNodePtr Prec, T val) noexcept
{
    CNodePtr add = make_shared<CNode> (val, Prec, Prec->getNext ());

    Prec->getNext ()->setPrevious (add);
    Prec->setNext (add);

    ++m_size;
}
/*!
    @fn CList<T>::erase (CNodePtr Prec) noexcept
    @brief This function erase an element in the CList
    @param[in] del is @p CNodePtr parameter which indicates the element to delete
 */
template<typename T>
void CList<T>::erase (CNodePtr del) noexcept
{
    del->getNext ()->setPrevious (del->getPrevious ());
    del->getPrevious ()->setNext (del->getNext ());

    del->setPrevious (nullptr);
    del->setNext (nullptr);

    --m_size;
}
/*!
    @fn CList<T>::resize (unsigned n, const T &val) noexcept
    @brief This function resize at n size, it add a default value (val) if n is greater than the CList size
           and delete the old values if n is smaller than the CList size
    @param[in] n is @p unsigned parameter which indicates the new size of the CList
    @param[in] val is @p T parameter which indicates the default value if n is greater than the CList size
 */
template<typename T>
void CList<T>::resize (unsigned n, const T &val /*= T()*/) noexcept
{
    if (m_size == n)
        return;

    if (m_size > n)
    {
        CNodePtr ptr = m_head;
        for (size_t i = 0; i < n; ++i)
            ptr = ptr->getNext ();

        ptr->setNext (m_tail);
        m_tail->setPrevious (ptr);

        m_size = n;

        return;
    }

    CNodePtr ptr = m_head;
    for (size_t i = 0; i < m_size; ++i)
        ptr = ptr->getNext ();

    for (size_t i = 0; i < n - m_size; ++i)
    {
        CNodePtr add = make_shared<CNode> (val, ptr, ptr->getNext ());
        ptr->setNext (add);
        m_tail->setPrevious (add);
        ptr = add;
    }

    m_size = n;
}
/*!
    @fn CList<T>::swap(nsSdD::CList <T> &x) noexcept
    @brief This function swap the head and the tail of the CList
    @param[in] x is @p nsSdD::CList <T> parameter which indicate the CList that need to be swap
 */
template<typename T>
void CList<T>::swap (nsSdD::CList <T> &x) noexcept
{
    CNodePtr ptr = m_head;
    m_head->setNext (x.getHead ()->getNext ());
    x.getHead ()->setNext (ptr->getNext ());

    ptr = m_tail;
    m_tail->setPrevious (x.getTail ()->getPrevious ());
    x.getTail ()->setPrevious (ptr->getPrevious ());

    size_t tmp = m_size;
    m_size = x.size ();

    x.m_size = tmp;
}
/*!
    @fn CList<T>::clear() noexcept
    @brief This function "clear" the CList by removing all the elements between the head and the tail
           and destroys them.
 */
template<typename T>
void CList<T>::clear () noexcept
{
    m_head->setNext (m_tail);
    m_tail->setPrevious (m_head);

    m_size = 0;
}
/*!
   @fn CList<T>::remove (const T &val) noexcept
   @brief This function delete the value in parameter on the CList
   @param[in] val is @p T parameter which indicate the value to delete on the CList
 */
template<typename T>
void CList<T>::remove (const T &val) noexcept
{
    for (CNodePtr a = m_head; a; a = a->getNext ())
    {
        if (a->getInfo () == val)
        {
            (a->getPrevious ())->setNext (a->getNext ());
            (a->getNext ())->setPrevious (a->getPrevious ());
            a->setNext (nullptr);
            a->setPrevious (nullptr);
            return;
        }
    }
}
/*!
    @fn CList<T>::remove_if (Predicate pred) noexcept
    @brief Remove all the values in the list which don't respond to the predicate in parameter
    @param[in] pref is @p Predicate parameter which indicate the condition to respect
 */
template<typename T>
template<class Predicate>
void CList<T>::remove_if (Predicate pred) noexcept
{
    for (CNodePtr a = m_head; a; a = a->getNext ())
    {
        if (!pred (a))
        {
            (a->getPrevious ())->setNext (a->getNext ());
            (a->getNext ())->setPrevious (a->getPrevious ());
            a->setNext (nullptr);
            a->setPrevious (nullptr);
        }
    }
}
/*!
    @fn CList<T>::reverse () noexcept
    @brief Reverse all the elements of the CList (the first element will be the last, etc.)
 */
template<typename T>
void CList<T>::reverse () noexcept
{
    CNodePtr tmp = m_head;
    m_head->setNext (m_tail->getPrevious ());
    m_tail->setPrevious (tmp->getNext ());

    for (size_t i = 0; i < m_size; ++i)
    {
        CNodePtr ptr = tmp->getNext ()->getPrevious ();
        tmp->getNext ()->setPrevious (tmp->getNext ()->getNext ());
        tmp->getNext ()->setNext (ptr);

        tmp = tmp->getNext ();
    }
}
