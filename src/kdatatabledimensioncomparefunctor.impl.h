//
// Created by kca on 5/10/15.
//

#include "KDataTableDimensionCompareFunctor"
#include "kglobal"
#include <stdexcept>

namespace kumquat {

template<
    typename TValue,
    Dimension _dimension,
    typename TValueCompareFunctor,
    typename TDataTableDataFunctor
>
KDataTableDimensionCompareFunctor<TValue, _dimension, TValueCompareFunctor, TDataTableDataFunctor>::
KDataTableDimensionCompareFunctor(const IndexVec& indexVec)
    : _dataTableDataFunc(TDataTableDataFunctor()),
      _valueCompareFunc(TValueCompareFunctor()),
      _indexVec(
          KASSERT(indexVec,
                  indexVec.empty(),
                  "Argument 'indexVec' is empty"))
{ }

template<
    typename TValue,
    Dimension _dimension,
    typename TValueCompareFunctor,
    typename TDataTableDataFunctor
>
bool
KDataTableDimensionCompareFunctor<TValue, _dimension, TValueCompareFunctor, TDataTableDataFunctor>::
operator()(const KIDataTable<TValue>* const dataTable,
           const std::size_t indexA,
           const std::size_t indexB)
const {
    for (const std::size_t variableIndex : _indexVec) {

        const TValue& valueA = _dataTableDataFunc(dataTable, indexA, variableIndex);
        const TValue& valueB = _dataTableDataFunc(dataTable, indexB, variableIndex);

        if (valueA != valueB) {
            const bool x = _valueCompareFunc(valueA, valueB);
            return x;
        }
    }
    return false;
}

}  // namespace kumquat
