//
// Created by kca on 5/11/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KDATATABLEDATAFUNCTOR_H
#define KEVINARPE_KUMQUAT_QT5_KDATATABLEDATAFUNCTOR_H

#include "knamespace"
#include "KIDataTable"
#include <cassert>

namespace kumquat {

/**
 * Retrieves data from a {@link KIDataTable<>} using two indices.
 *
 * This class reorders row and column indices (as necessary) to make calling
 * {@link KIDataTable<>::data(std::size_t, std::size_t)} more generic.
 */
template<Dimension _dimension, typename TValue>
struct KDataTableDataFunctor {

    static constexpr const Dimension DIMENSION = _dimension;

    constexpr Dimension
    dimension()
    const noexcept {
        return _dimension;
    }

    /**
     * @param fixedIndex
     *        for row comparison, this is row index;
     *        for column comparison, this is column index
     * @param variableIndex
     *        for row comparison, this is column index;
     *        for column comparison, this is row index
     */
    const TValue&
    operator()(const KIDataTable<TValue>* const dataTable,
               const std::size_t fixedIndex,
               const std::size_t variableIndex)
    const {
        // Ref: http://stackoverflow.com/questions/3692954/add-custom-messages-in-assert
        assert(false && "Unreachable code");
    }
};

template<typename TValue>
struct KDataTableDataFunctor<Dimension::Row, TValue> {

    const TValue&
    operator()(const KIDataTable<TValue>* const dataTable,
               const std::size_t fixedIndex,
               const std::size_t variableIndex)
    const {
        const TValue& x = dataTable->data(fixedIndex, variableIndex);
        return x;
    }
};

template<typename TValue>
struct KDataTableDataFunctor<Dimension::Column, TValue> {

    const TValue&
    operator()(const KIDataTable<TValue>* const dataTable,
               const std::size_t fixedIndex,
               const std::size_t variableIndex)
    const {
        const TValue& x = dataTable->data(variableIndex, fixedIndex);
        return x;
    }
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KDATATABLEDATAFUNCTOR_H
