//
// Created by kca on 5/11/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KDATATABLEDATAFUNCTOR_H
#define KEVINARPE_KUMQUAT_QT5_KDATATABLEDATAFUNCTOR_H

#include "knamespace"
#include "KDataTable"
#include <cassert>

namespace kumquat {

///**
// * Retrieves data from a {@link KIDataTable<>} using two indices.
// *
// * This class reorders row and column indices (as necessary) to make calling
// * {@link KIDataTable<>::data(std::size_t, std::size_t)} more generic.
// */
//template<
//    Dimension _dimension,
//    typename TValue,
//    typename TDataTable = KDataTable<TValue>
//>
//struct KDataTableDataFunctor {
//
//    static constexpr const Dimension DIMENSION = _dimension;
//
//    typedef TDataTable DataTable;
//    typedef const DataTable* const DataTablePtr;
//
//    constexpr Dimension
//    dimension()
//    const noexcept {
//        return _dimension;
//    }
//
//    /**
//     * @param fixedIndex
//     *        for row comparison, this is row index;
//     *        for column comparison, this is column index
//     * @param variableIndex
//     *        for row comparison, this is column index;
//     *        for column comparison, this is row index
//     */
//    const TValue&
//    // TODO: Convert to const ref is possible (due to #include limitations)
//    operator()(DataTablePtr dataTablePtr,
//               const std::size_t fixedIndex,
//               const std::size_t variableIndex)
//    const {
//        // Ref: http://stackoverflow.com/questions/3692954/add-custom-messages-in-assert
//        assert(false && "Unreachable code");
//    }
//};
//
//template<
//    typename TValue,
//    typename TDataTable = KDataTable<TValue>
//>
//struct KDataTableDataFunctor<Dimension::Row, TValue, TDataTable> {
//
//    typedef TDataTable DataTable;
//    typedef const DataTable* const DataTablePtr;
//
//    const TValue&
//    operator()(DataTablePtr dataTablePtr,
//               const std::size_t fixedIndex,
//               const std::size_t variableIndex)
//    const {
//        const TValue& x = dataTablePtr->data(fixedIndex, variableIndex);
//        return x;
//    }
//};
//
//template<
//    typename TValue,
//    typename TDataTable = KDataTable<TValue>
//>
//struct KDataTableDataFunctor<Dimension::Column, TValue, TDataTable> {
//
//    typedef TDataTable DataTable;
//    typedef const DataTable* const DataTablePtr;
//
//    const TValue&
//    operator()(DataTablePtr dataTablePtr,
//               const std::size_t fixedIndex,
//               const std::size_t variableIndex)
//    const {
//        const TValue& x = dataTablePtr->data(variableIndex, fixedIndex);
//        return x;
//    }
//};

namespace {

/**
 * Retrieves data from a {@code TDataTable<>} using two indices.
 *
 * This class reorders row and column indices (as necessary) to make calling
 * {@link KIDataTable<>::data(std::size_t, std::size_t)} more generic.
 */
template<
    Dimension _dimension,
    typename TValue,
    typename TDataTable = KDataTable<TValue>
>
struct _KDataTableDataFunctorImpl {

    static constexpr const Dimension DIMENSION = _dimension;

    typedef TDataTable DataTable;
    typedef const DataTable* const DataTablePtr;

    constexpr Dimension
    dimension()
    const noexcept {
        return _dimension;
    }
};

}  // namespace (unnamed)

template<
    Dimension _dimension,
    typename TValue,
    typename TDataTable = KDataTable<TValue>
>
struct KDataTableDataFunctor { };

template<typename TValue>
class KDataTableDataFunctor<Dimension::Row, TValue>
    : public _KDataTableDataFunctorImpl<Dimension::Row, TValue> {

private:
    typedef _KDataTableDataFunctorImpl<Dimension::Row, TValue> Base;

public:
//    using Base::DIMENSION;
//    using DataTable = typename Base::DataTable;
    using DataTablePtr = typename Base::DataTablePtr;
//    using Base::dimension;

    /**
     * @param fixedIndex
     *        for row comparison, this is row index;
     *        for column comparison, this is column index
     * @param variableIndex
     *        for row comparison, this is column index;
     *        for column comparison, this is row index
     */
    const TValue&
    operator()(DataTablePtr dataTablePtr,
               const std::size_t fixedIndex,
               const std::size_t variableIndex)
    const {
        const TValue& x = dataTablePtr->data(fixedIndex, variableIndex);
        return x;
    }
};

template<typename TValue>
class KDataTableDataFunctor<Dimension::Column, TValue>
    : private _KDataTableDataFunctorImpl<Dimension::Column, TValue> {

private:
    typedef _KDataTableDataFunctorImpl<Dimension::Column, TValue> Base;

public:
//    using Base::DIMENSION;
//    using DataTable = typename Base::DataTable;
    using DataTablePtr = typename Base::DataTablePtr;
//    using Base::dimension;

    /**
     * @param fixedIndex
     *        for row comparison, this is row index;
     *        for column comparison, this is column index
     * @param variableIndex
     *        for row comparison, this is column index;
     *        for column comparison, this is row index
     */
    const TValue&
    operator()(DataTablePtr dataTablePtr,
               const std::size_t fixedIndex,
               const std::size_t variableIndex)
    const {
        const TValue& x = dataTablePtr->data(variableIndex, fixedIndex);
        return x;
    }
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KDATATABLEDATAFUNCTOR_H
