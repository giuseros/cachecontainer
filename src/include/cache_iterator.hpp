#ifndef _CACHE_ITERATOR_
#define _CACHE_ITERATOR_

#include <iterator>

template <typename Type, typename UnqualifiedType = std::remove_cv_t<Type>>
class CacheIterator : public std::iterator<std::forward_iterator_tag, UnqualifiedType, std::ptrdiff_t, Type*, Type&>
{
    typedef  typename std::list<UnqualifiedType>::iterator listIterator;

    listIterator itr;

public:
    explicit CacheIterator(listIterator nd) : itr(nd) {}

    CacheIterator() : itr(listIterator()) {}

    void swap(CacheIterator& other)
    {
        using std::swap;
        swap(itr, other);
    }

    CacheIterator& operator++ () // Pre-increment
    {
        //assert(itr != nullptr && "Out-of-bounds iterator increment!");
        itr = std::next(itr);
        return *this;
    }

    CacheIterator operator++ (int) // Post-increment
    {
        //assert(itr != nullptr && "Out-of-bounds iterator increment!");
        CacheIterator tmp(*this);
        itr = std::next(itr);
        return tmp;
    }

    template <typename OtherType>
    bool operator==(const CacheIterator<OtherType>& rhs) const
    {
        return itr == rhs.itr;
    }

    template <typename OtherType>
    bool operator!= (const CacheIterator<OtherType>& rhs) const
    {
        return itr != rhs.itr;

    }

    Type& operator*() const
    {
        //assert(itr != nullptr && "Invalid iterator dereference!");
        return *itr;
    }

    listIterator operator->() const
    {
        //assert(itr != nullptr && "Invalid iterator dereference!");
        return itr;
    }

    operator CacheIterator<const Type>() const
    {
        return CacheIterator<const Type>(itr);
    }

};

#endif