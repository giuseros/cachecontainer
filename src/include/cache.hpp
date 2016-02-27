#ifndef _CACHE_HH_
#define _CACHE_HH_


#include <unordered_map>
#include <list>

#include "cache_iterator.hpp"

template <typename K, typename T>
class Cache{
    typedef  std::pair < K, T >  nodeType;
    typedef  typename std::list<nodeType>::iterator listIteratorType;

public:
    typedef CacheIterator<nodeType> iterator;
    typedef CacheIterator<const nodeType> const_iterator;

    Cache(size_t const sz) : cacheSize(sz) {}

    void insert(K key, T element)
    {
        auto p = std::make_pair(key, element);
        auto it = elementList.insert(elementList.begin(), p);
        lookupMap[key] = it;

        if (elementList.size() > cacheSize) {
            elementList.pop_front();
        }
    }

    listIteratorType find(K key)
    {
        auto it = lookupMap[key];
        if (it != elementList.begin() && it != elementList.end()) {
            elementList.splice(elementList.begin(), elementList, it, std::next(it));
        }
        return it;
    }

    void erase(K key)
    {
        auto it = lookupMap.find(key);
        if (it != lookupMap.end()) {
            elementList.erase(it->second);
            lookupMap.erase(key);
        }
    }

    iterator begin()
    {
        return iterator(elementList.begin());
    }

    iterator end()
    {
        return iterator(elementList.end());       
    }

private:
    std::list < nodeType > elementList;
    std::unordered_map < K, listIteratorType >  lookupMap;
    size_t cacheSize;
};

#endif