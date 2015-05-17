//
// Created by kca on 5/10/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KDATATABLEDIMENSIONCOMPAREFUNCTOR_H
#define KEVINARPE_KUMQUAT_QT5_KDATATABLEDIMENSIONCOMPAREFUNCTOR_H

#include "KDataTable"
#include "KDataTableDataFunctor"
#include "knamespace"
#include "kdatatable.h"
#include <Qt>
#include <vector>
#include <stdexcept>
#include <cassert>

namespace kumquat {

typedef std::vector<std::size_t> IndexVec;

/**
 * Acts as a 'less' or 'greater' operator to compare rows or columns from a {@link KIDataTable<>}.
 *
 * @see make_dimension_compare_functor()
 */
template<
    typename TValue,
    Dimension _dimension,
    typename TValueCompareFunctor,
    typename TDataTable = KDataTable<TValue>,
    typename TDataTableDataFunctor = KDataTableDataFunctor<_dimension, TValue>
>
class KDataTableDimensionCompareFunctor {

public:
    static constexpr const Dimension DIMENSION = _dimension;

    typedef TDataTable DataTable;
    typedef const DataTable* const DataTablePtr;

    /**
     * @param indexVec
     *        one or more column indices for sort order
     *
     * @asserts indexVec is not empty
     */
    KDataTableDimensionCompareFunctor(const IndexVec& indexVec);

    constexpr Dimension
    dimension()
    const noexcept {
        return _dimension;
    }

    // TODO: Convert to const ref is possible (due to #include limitations)
    bool
    operator()(DataTablePtr dataTablePtr,
               const std::size_t indexA,
               const std::size_t indexB)
    const;

private:
    const TDataTableDataFunctor _dataTableDataFunc;
    const TValueCompareFunctor _valueCompareFunc;
    const IndexVec _indexVec;
};

template<typename TValue, Dimension dimension, typename TValueCompareFunctor>
KDataTableDimensionCompareFunctor<TValue, dimension, TValueCompareFunctor>
make_dimension_compare_functor(Qt::SortOrder sortOrder, const IndexVec& indexVec) {
    switch (sortOrder) {
        case Qt::AscendingOrder: {
            typedef KDataTableDimensionCompareFunctor<TValue, dimension, std::less<TValue>> T;
            const T& x = T(indexVec);
            return x;
        }
        case Qt::DescendingOrder: {
            typedef KDataTableDimensionCompareFunctor<TValue, dimension, std::greater<TValue>> T;
            const T& x = T(indexVec);
            return x;
        }
        default: {
            // Ref: http://stackoverflow.com/questions/3692954/add-custom-messages-in-assert
            assert(false && "Unreachable code");
        }
    }
}

}  // namespace kumquat

#include "kdatatabledimensioncomparefunctor.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KDATATABLEDIMENSIONCOMPAREFUNCTOR_H
