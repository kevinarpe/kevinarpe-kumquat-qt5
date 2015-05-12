//
// Created by kca on 5/13/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KSPARSEDATAMATRIX_H
#define KEVINARPE_KUMQUAT_QT5_KSPARSEDATAMATRIX_H

#include "KIDataMatrix"
#include <unordered_map>
#include <cstddef>
#include <cassert>

namespace kumquat {

template<typename TValue>
class KSparseDataMatrix {

public:
    struct Coord {

        const std::size_t rowIndex;
        const std::size_t columnIndex;

        Coord(const std::size_t rowIndex_, const std::size_t columnIndex_)
            : rowIndex(rowIndex_),
              columnIndex(columnIndex_)
        { }
    };

    // const_iterator->first: Coord
    // const_iterator->second: TValue
    typedef typename std::unordered_map<Coord, TValue>::const_iterator const_iterator;

    typedef KSparseDataMatrix<TValue> Self;

    KSparseDataMatrix()
        : _dimension_To_Size_Map(
              {
                  { Dimension::Row, 0 },
                  { Dimension::Column, 0 },
              })
    { }

    std::size_t
    size(const Dimension dimension)
    const;

    std::size_t
    count()
    const;

    const_iterator
    begin()
    const;

    const_iterator
    end()
    const;

    const_iterator
    find(const std::size_t rowIndex, const std::size_t columnIndex)
    const;

    Self&
    insert(const std::size_t rowIndex, const std::size_t columnIndex, const TValue& value);

    Self&
    clear();

private:
    typedef std::unordered_map<Coord, TValue> _Coord_To_Value_Map;
    _Coord_To_Value_Map _coord_To_Value_Map;

    typedef std::unordered_map<Dimension, std::size_t> _Dimension_To_Size_Map;
    _Dimension_To_Size_Map _dimension_To_Size_Map;
};

}  // namespace kumquat

#include "ksparsedatamatrix.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KSPARSEDATAMATRIX_H
