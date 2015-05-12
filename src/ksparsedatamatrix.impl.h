//
// Created by kca on 5/13/15.
//

#include "KSparseDataMatrix"

namespace kumquat {

// public
template<typename TValue>
std::size_t
KSparseDataMatrix<TValue>::
size(const Dimension dimension)
const {
    const std::size_t x = _dimension_To_Size_Map.at(dimension);
    return x;
}

// public
template<typename TValue>
std::size_t
KSparseDataMatrix<TValue>::
count()
const {
    const std::size_t x = _coord_To_Value_Map.size();
    return x;
}

// public
template<typename TValue>
typename KSparseDataMatrix<TValue>::const_iterator
KSparseDataMatrix<TValue>::
begin()
const {
    const const_iterator& x = _coord_To_Value_Map.begin();
    return x;
}

// public
template<typename TValue>
typename KSparseDataMatrix<TValue>::const_iterator
KSparseDataMatrix<TValue>::
end()
const {
    const const_iterator& x = _coord_To_Value_Map.end();
    return x;
}

// public
template<typename TValue>
typename KSparseDataMatrix<TValue>::const_iterator
KSparseDataMatrix<TValue>::
find(const std::size_t rowIndex, const std::size_t columnIndex)
const {
    const Coord c(rowIndex, columnIndex);
    const const_iterator& x = _coord_To_Value_Map.find(c);
    return x;
}

namespace {

typedef std::unordered_map<Dimension, std::size_t> _Dimension_To_Size_Map;

void
_updateSize(_Dimension_To_Size_Map* const dimension_To_Size_Map, const Dimension dimension, const std::size_t index) {
    // Use reference trick to prevent double lookup.
    std::size_t& size = (*dimension_To_Size_Map)[dimension];
    if (index >= size) {
        size = std::size_t(1) + index;
    }
}

}  // namespace (unnamed)

// public
template<typename TValue>
typename KSparseDataMatrix<TValue>::Self&
KSparseDataMatrix<TValue>::
insert(const std::size_t rowIndex, const std::size_t columnIndex, const TValue& value) {

    typedef typename _Dimension_To_Size_Map::value_type value_type;
    typedef typename _Dimension_To_Size_Map::iterator iterator;

    const Coord c(rowIndex, columnIndex);
    const std::pair<iterator, bool>& pair = _coord_To_Value_Map.insert(value_type(c, value));
    assert(pair.second && "Failed to insert value");

    _updateSize(&_dimension_To_Size_Map, Dimension::Row, rowIndex);
    _updateSize(&_dimension_To_Size_Map, Dimension::Column, columnIndex);

    return *this;
}

// public
template<typename TValue>
typename KSparseDataMatrix<TValue>::Self&
KSparseDataMatrix<TValue>::
clear() {
    _coord_To_Value_Map.clear();
    return *this;
}

}  // namespace kumquat
