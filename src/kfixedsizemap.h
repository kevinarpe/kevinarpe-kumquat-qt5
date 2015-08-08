//
// Created by kca on 5/13/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KFIXEDSIZEMAP_H
#define KEVINARPE_KUMQUAT_QT5_KFIXEDSIZEMAP_H

#include "kglobal"
#include "kalgorithm"
#include "kstdlib"
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>
#include <sstream>

namespace kumquat {

template<
    typename TKey,
    typename TValue,
    typename TCompare = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>
>
class KFixedSizeMap {

public:
    typedef TKey                          key_type;
    typedef TValue                        mapped_type;
    typedef std::pair<TKey, TValue>       non_const_value_type;
    typedef std::pair<const TKey, TValue> value_type;
    typedef TCompare                      key_compare;
    typedef TAllocator                    allocator_type;

private:
    typedef std::vector<non_const_value_type, allocator_type> _InitPairVec;
    typedef std::vector<value_type, allocator_type>           _PairVec;

public:
    typedef typename _PairVec::iterator               iterator;
    typedef typename _PairVec::const_iterator         const_iterator;
    typedef typename _PairVec::size_type              size_type;
    typedef typename _PairVec::difference_type        difference_type;
    typedef typename _PairVec::reverse_iterator       reverse_iterator;
    typedef typename _PairVec::const_reverse_iterator const_reverse_iterator;

public:
    class value_compare
        : public std::binary_function<value_type, value_type, bool> {

    public:
        bool
        operator()(const value_type& pair1, const value_type& pair2)
        const {
            const bool x = _key_compare(pair1.first, pair2.first);
            return x;
        }

    protected:
        explicit value_compare(const key_compare& compare)
            : _key_compare(compare)
        { }

    private:
        friend class KFixedSizeMap<TKey, TValue, key_compare>;

        key_compare _key_compare;
    };

private:
    class _key_and_value_compare
        : public std::binary_function<key_type, value_type, bool> {

    public:
        bool
        operator()(const key_type& key, const value_type& pair)
        const {
            const TKey& pair_key = pair.first;
            const bool x = _key_compare(key, pair_key);
            return x;
        }

        bool
        operator()(const value_type& pair, const key_type& key)
        const {
            const TKey& pair_key = pair.first;
            const bool x = _key_compare(pair_key, key);
            return x;
        }

    protected:
        explicit _key_and_value_compare(const key_compare& compare)
            : _key_compare(compare)
        { }

    private:
        friend class KFixedSizeMap<TKey, TValue, key_compare>;

        key_compare _key_compare;
    };

public:
    KFixedSizeMap(const KFixedSizeMap& x)
        : _pairVec(x._pairVec),
          _value_compare(x._value_compare),
          _key_and_value_compare(x._key_and_value_compare)
    { }

public:
    KFixedSizeMap(KFixedSizeMap&& x)
        : _pairVec(std::move(x._pairVec)),
          _value_compare(std::move(x._value_compare)),
          _key_and_value_compare(std::move(x._key_and_value_compare))
    { }

public:
    KFixedSizeMap(std::initializer_list<non_const_value_type> list, const key_compare& compare = key_compare())
        : _value_compare(compare),
          _key_and_value_compare(compare)
    {
        // For initilisation, we need to sort, so keys cannot be const.
        _InitPairVec v(list);
        _init(&v, _value_compare);
        // After sort, copy to new vector with const keys.
        _pairVec = _PairVec(v.begin(), v.end());
    }

public:
    template<typename InputIterator>
    KFixedSizeMap(InputIterator first, InputIterator last, const key_compare& compare = key_compare())
        : _value_compare(compare),
          _key_and_value_compare(compare)
    {
        // For initilisation, we need to sort, so keys cannot be const.
        _InitPairVec v(first, last);
        _init(&v, _value_compare);
        // After sort, copy to new vector with const keys.
        _pairVec = _PairVec(v.begin(), v.end());
    }

public:
    KFixedSizeMap&
    operator=(const KFixedSizeMap& x) {
        if (this == &x) {
            return *this;
        }
        _staticAssertKeysEqual(*this, x);
        _pairVec = x._pairVec;
        _value_compare = x._value_compare;
        _key_and_value_compare = x._key_and_value_compare;
        return *this;
    }

public:
    KFixedSizeMap&
    operator=(const KFixedSizeMap&& x) {
        if (this == &x) {
            return *this;
        }
        _staticAssertKeysEqual(*this, x);
        _pairVec = std::move(x._pairVec);
        _value_compare = std::move(x._value_compare);
        _key_and_value_compare = std::move(x._key_and_value_compare);
        return *this;
    }

private:
    static bool
    _staticKeyEqualTo(const value_type& a, const value_type& b) {
        const bool x = (a.first == b.first);
        return x;
    }

private:
    /**
     * @param pairVecPtr
     *        user a pointer here to show we will modify the input (sort)
     * @param value_compare_
     *        by reference to save copy, but not const as that may change behavior of functor
     */
    static void
    _init(_InitPairVec* pairVecPtr, value_compare& value_compare_) {
        assert(!pairVecPtr->empty() && "Map is empty");

        // Sort vector of pairs by keys.
        std::sort(pairVecPtr->begin(), pairVecPtr->end(), value_compare_);

        auto iter = std::adjacent_find(pairVecPtr->begin(), pairVecPtr->end(), &_staticKeyEqualTo);
        assert(iter == pairVecPtr->end() && "Map has duplicate keys");
    }

private:
    static void
    _staticAssertKeysEqual(const KFixedSizeMap<TKey, TValue, TCompare, TAllocator>& self,
                           const KFixedSizeMap<TKey, TValue, TCompare, TAllocator>& other) {
        assert(std::equal(self._pairVec.begin(), self._pairVec.end(),
                          other._pairVec.begin(), other._pairVec.end(),
                          &_staticKeyEqualTo)
               && "Other map has different keys");
    }

public:
    KFixedSizeMap&
    operator=(KFixedSizeMap&& x) {
        if (this == &x) {
            return *this;
        }
        _staticAssertKeysEqual(*this, x);
        _pairVec = std::move(x._pairVec);
        _value_compare = std::move(x._value_compare);
        _key_and_value_compare = std::move(x._key_and_value_compare);
        return *this;
    }

public:
    KFixedSizeMap&
    operator=(std::initializer_list<value_type> list) {
        for (const value_type& pair : list) {
            (*this)[pair.first] = pair.second;
        }
        return *this;
    }

public:
    iterator
    begin() {
        const iterator x = _pairVec.begin();
        return x;
    }

public:
    const_iterator
    begin()
    const {
        const const_iterator x = _pairVec.begin();
        return x;
    }

public:
    iterator
    end() {
        const iterator x = _pairVec.end();
        return x;
    }

public:
    const_iterator
    end()
    const {
        const const_iterator x = _pairVec.end();
        return x;
    }

public:
    reverse_iterator
    rbegin() {
        const reverse_iterator x = _pairVec.rbegin();
        return x;
    }

public:
    const_reverse_iterator
    rbegin()
    const {
        const const_reverse_iterator x = _pairVec.rbegin();
        return x;
    }

public:
    reverse_iterator
    rend() {
        const reverse_iterator x = _pairVec.rend();
        return x;
    }

public:
    const_reverse_iterator
    rend()
    const {
        const const_reverse_iterator x = _pairVec.rend();
        return x;
    }

public:
    const_iterator
    cbegin()
    const {
        const const_iterator x = _pairVec.cbegin();
        return x;
    }

public:
    const_iterator
    cend()
    const {
        const const_iterator x = _pairVec.cend();
        return x;
    }

public:
    const_reverse_iterator
    crbegin()
    const {
        const const_reverse_iterator x = _pairVec.crbegin();
        return x;
    }

public:
    const_reverse_iterator
    crend()
    const {
        const const_reverse_iterator x = _pairVec.crend();
        return x;
    }

public:
    bool
    empty()
    const {
        const bool x = _pairVec.empty();
        return x;
    }

public:
    size_type
    size()
    const {
        const size_type x = _pairVec.size();
        return x;
    }

public:
    size_type
    max_size()
    const {
        const size_type x = _pairVec.max_size();
        return x;
    }

private:
    std::string
    _keyNotExistMessage(const key_type& key)
    const {
        std::ostringstream str;
        str << "Argument 'key' does not exist: [" << key << "]";
        const std::string& x = str.str();
        return x;
    }

public:
    mapped_type&
    operator[](const key_type& key) {
        const iterator iter = find(key);
        if (iter == _pairVec.end()) {
            KABORT(_keyNotExistMessage(key));
        }
        mapped_type& x = iter->second;
        return x;
    }

public:
    const mapped_type&
    operator[](const key_type& key)
    const {
        const const_iterator iter = find(key);
        if (iter == _pairVec.end()) {
            KABORT(_keyNotExistMessage(key));
        }
        const mapped_type& x = iter->second;
        return x;
    }

public:
    mapped_type&
    at(const key_type& key) {
        const iterator iter = find(key);
        if (iter == _pairVec.end()) {
            throw std::out_of_range(_keyNotExistMessage(key));
        }
        mapped_type& x = iter->second;
        return x;
    }

public:
    const mapped_type&
    at(const key_type& key)
    const {
        const iterator iter = find(key);
        if (iter == _pairVec.end()) {
            throw std::out_of_range(_keyNotExistMessage(key));
        }
        const mapped_type& x = iter->second;
        return x;
    }

public:
    void
    swap(KFixedSizeMap& x) {
        _staticAssertKeysEqual(*this, x);
        _pairVec.swap(x._pairVec);
        std::swap(_value_compare, x._value_compare);
    }

public:
    key_compare
    key_comp()
    const {
        return _value_compare._key_compare;
    }

public:
    value_compare
    value_comp()
    const {
        const value_compare& x = value_compare(_value_compare._key_compare);
        return x;
    }

public:
    iterator
    find(const key_type& key) {
        const iterator x = kbinary_search(_pairVec.begin(), _pairVec.end(), key, _key_and_value_compare);
        return x;
    }

public:
    const_iterator
    find(const key_type& key)
    const {
        const const_iterator begin = _pairVec.begin();
        const const_iterator end = _pairVec.end();
        const const_iterator x = kbinary_search(begin, end, key, _key_and_value_compare);
        return x;
    }

public:
    size_type
    count(const key_type& key)
    const {
        const const_iterator iter = find(key);
        const size_type x = (iter == _pairVec.end()) ? 0 : 1;
        return x;
    }

public:
    iterator
    lower_bound(const key_type& key) {
        const iterator x = std::lower_bound(_pairVec.begin(), _pairVec.end(), key, _key_and_value_compare);
        return x;
    }

public:
    const_iterator
    lower_bound(const key_type& key)
    const {
        const const_iterator x = std::lower_bound(_pairVec.begin(), _pairVec.end(), key, _key_and_value_compare);
        return x;
    }

public:
    iterator
    upper_bound(const key_type& key) {
        const iterator x = std::upper_bound(_pairVec.begin(), _pairVec.end(), key, _key_and_value_compare);
        return x;
    }

public:
    const_iterator
    upper_bound(const key_type& key)
    const {
        const const_iterator x = std::upper_bound(_pairVec.begin(), _pairVec.end(), key, _key_and_value_compare);
        return x;
    }

public:
    std::pair<iterator, iterator>
    equal_range(const key_type& key) {
        const std::pair<iterator, iterator>& x =
            std::equal_range(_pairVec.begin(), _pairVec.end(), key, _key_and_value_compare);
        return x;
    }

public:
    std::pair<const_iterator, const_iterator>
    equal_range(const key_type& key)
    const {
        const std::pair<const_iterator, const_iterator>& x =
            std::equal_range(_pairVec.begin(), _pairVec.end(), key, _key_and_value_compare);
        return x;
    }

public:
    template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
    friend bool
    operator==(const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
               const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b);

    template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
    friend bool
    operator<(const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
              const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b);

private:
    _PairVec _pairVec;
    value_compare _value_compare;
    _key_and_value_compare _key_and_value_compare;

    KFixedSizeMap() = delete;
};

template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
/*friend*/ inline bool
operator==(const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
           const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b) {
    const bool x = (a._pairVec == b._pairVec);
    return x;
}

template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
/*friend*/ inline bool
operator<(const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
          const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b) {
    const bool x = (a._pairVec < b._pairVec);
    return x;
}

template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
inline bool
operator!=(const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
           const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b) {
    const bool x = !(a == b);
    return x;
}

template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
inline bool
operator>(const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
          const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b) {
    const bool x = (b < a);
    return x;
}

template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
inline bool
operator<=(const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
           const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b) {
    const bool x = !(b < a);
    return x;
}

template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
inline bool
operator>=(const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
           const KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b) {
    const bool x = !(a < b);
    return x;
}

template<typename TKey1, typename TValue1, typename TCompare1, typename TAllocator1>
inline void
swap(KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& a,
     KFixedSizeMap<TKey1, TValue1, TCompare1, TAllocator1>& b) {
    a.swap(b);
}

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KFIXEDSIZEMAP_H
